#include <atomic>
#include <cassert>
#include <cstddef>
#include <utility>

// =============================================================================
// Базовая версия — то, что пишут на собеседовании.
//
// Идея:
//   • Хранить два указателя: на объект и на счётчик ссылок (int*).
//   • При копировании — инкремент счётчика, при удалении — декремент.
//   • Когда счётчик дошёл до 0 — удалить и объект, и счётчик.
//   • Rule of Five: dtor, copy ctor, copy assign, move ctor, move assign.
//
// Что НЕ покрывает (намеренно, для краткости):
//   • Thread-safety (нужен std::atomic<int>)
//   • weak_ptr
//   • Custom deleter
//   • make_shared single-allocation оптимизация
// =============================================================================

template <typename T> class SharedPtr {
  public:
	SharedPtr() noexcept : ptr_(nullptr), count_(nullptr) {}

	explicit SharedPtr(T* p)
	    : ptr_(p), count_(p ? new int(1) : nullptr) {}

	SharedPtr(const SharedPtr& other) noexcept
	    : ptr_(other.ptr_), count_(other.count_) {
		if (count_) ++*count_;
	}

	SharedPtr(SharedPtr&& other) noexcept
	    : ptr_(other.ptr_), count_(other.count_) {
		other.ptr_ = nullptr;
		other.count_ = nullptr;
	}

	~SharedPtr() { release(); }

	// Copy-and-swap покрывает и copy assign, и move assign.
	// Параметр по значению → компилятор сам выбирает copy/move ctor.
	SharedPtr& operator=(SharedPtr other) noexcept {
		swap(other);
		return *this;
	}

	T& operator*() const noexcept { return *ptr_; }
	T* operator->() const noexcept { return ptr_; }
	T* get() const noexcept { return ptr_; }
	int use_count() const noexcept { return count_ ? *count_ : 0; }
	explicit operator bool() const noexcept { return ptr_ != nullptr; }

	void swap(SharedPtr& other) noexcept {
		std::swap(ptr_, other.ptr_);
		std::swap(count_, other.count_);
	}

  private:
	T* ptr_;
	int* count_;

	void release() noexcept {
		if (count_ && --*count_ == 0) {
			delete ptr_;
			delete count_;
		}
	}
};

template <typename T, typename... Args>
SharedPtr<T> make_shared(Args&&... args) {
	return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

// =============================================================================
// Расширенная версия (с control block и atomic) — для следующего шага.
//
// Что добавляется:
//   • ControlBlock как отдельный объект (готова почва для weak_ptr)
//   • std::atomic для thread-safety
//   • Виртуальный destroy() — type erasure под кастомные делитеры
//   • Aliasing constructor для sub-objects
//
// Идея: control block переживает объект, пока живы weak_ptr на него.
// =============================================================================

// class ControlBlockBase {
//   public:
// 	std::atomic<std::size_t> strong{1};
// 	std::atomic<std::size_t> weak{0};

// 	virtual ~ControlBlockBase() = default;
// 	virtual void destroy() noexcept = 0;
// };

// template <typename T> class ControlBlockPtr : public ControlBlockBase {
//   public:
// 	T* ptr_;
// 	explicit ControlBlockPtr(T* p) : ptr_(p) {}
// 	void destroy() noexcept override {
// 		delete ptr_;
// 		ptr_ = nullptr;
// 	}
// };

// template <typename T> class SharedPtr2 {
// 	template <typename U> friend class SharedPtr2;

//   public:
// 	constexpr SharedPtr2() noexcept : ptr_(nullptr), ctrl_(nullptr) {}

// 	explicit SharedPtr2(T* p) : ptr_(p), ctrl_(nullptr) {
// 		if (p) {
// 			try {
// 				ctrl_ = new ControlBlockPtr<T>(p);
// 			} catch (...) {
// 				delete p;
// 				throw;
// 			}
// 		}
// 	}

// 	// Aliasing: общий control block, но другой raw pointer.
// 	template <typename U>
// 	SharedPtr2(const SharedPtr2<U>& other, T* ptr) noexcept
// 	    : ptr_(ptr), ctrl_(other.ctrl_) {
// 		if (ctrl_) ctrl_->strong.fetch_add(1, std::memory_order_relaxed);
// 	}

// 	SharedPtr2(const SharedPtr2& other) noexcept
// 	    : ptr_(other.ptr_), ctrl_(other.ctrl_) {
// 		if (ctrl_) ctrl_->strong.fetch_add(1, std::memory_order_relaxed);
// 	}

// 	SharedPtr2(SharedPtr2&& other) noexcept
// 	    : ptr_(other.ptr_), ctrl_(other.ctrl_) {
// 		other.ptr_ = nullptr;
// 		other.ctrl_ = nullptr;
// 	}

// 	~SharedPtr2() { release(); }

// 	SharedPtr2& operator=(SharedPtr2 other) noexcept {
// 		swap(other);
// 		return *this;
// 	}

// 	T* get() const noexcept { return ptr_; }
// 	T& operator*() const noexcept { return *ptr_; }
// 	T* operator->() const noexcept { return ptr_; }
// 	explicit operator bool() const noexcept { return ptr_ != nullptr; }

// 	std::size_t use_count() const noexcept {
// 		return ctrl_ ? ctrl_->strong.load(std::memory_order_relaxed) : 0;
// 	}

// 	void swap(SharedPtr2& other) noexcept {
// 		std::swap(ptr_, other.ptr_);
// 		std::swap(ctrl_, other.ctrl_);
// 	}

//   private:
// 	T* ptr_;
// 	ControlBlockBase* ctrl_;

// 	void release() noexcept {
// 		if (!ctrl_) return;
// 		// acq_rel: синхронизирует записи в объект до уничтожения.
// 		if (ctrl_->strong.fetch_sub(1, std::memory_order_acq_rel) == 1) {
// 			ctrl_->destroy();
// 			if (ctrl_->weak.load(std::memory_order_acquire) == 0) {
// 				delete ctrl_;
// 			}
// 		}
// 	}
// };

// =============================================================================
// Tests
// =============================================================================

struct Counter {
	static int alive;
	int value;
	Counter(int v) : value(v) { ++alive; }
	~Counter() { --alive; }
};
int Counter::alive = 0;

int main() {
	// ===== Базовая версия =====

	// default
	{
		SharedPtr<int> p;
		assert(!p);
		assert(p.use_count() == 0);
	}

	// ptr ctor + dtor
	{
		assert(Counter::alive == 0);
		{
			SharedPtr<Counter> p(new Counter(42));
			assert(p->value == 42);
			assert(p.use_count() == 1);
			assert(Counter::alive == 1);
		}
		assert(Counter::alive == 0);
	}

	// copy
	{
		SharedPtr<Counter> a(new Counter(7));
		{
			SharedPtr<Counter> b = a;
			assert(a.use_count() == 2);
			assert(b->value == 7);
		}
		assert(a.use_count() == 1);
	}
	assert(Counter::alive == 0);

	// move
	{
		SharedPtr<Counter> a(new Counter(1));
		SharedPtr<Counter> b = std::move(a);
		assert(!a);
		assert(b.use_count() == 1);
	}

	// self-assignment
	{
		SharedPtr<Counter> a(new Counter(5));
		a = a;
		assert(a.use_count() == 1);
		assert(a->value == 5);
	}
	assert(Counter::alive == 0);

	// make_shared
	{
		auto p = make_shared<Counter>(99);
		assert(p->value == 99);
		assert(p.use_count() == 1);
	}
	assert(Counter::alive == 0);

	// ===== Расширенная версия =====

	// {
	// 	SharedPtr2<Counter> p(new Counter(11));
	// 	SharedPtr2<Counter> q = p;
	// 	assert(p.use_count() == 2);
	// 	assert(q->value == 11);
	// }
	// assert(Counter::alive == 0);

	// // aliasing
	// {
	// 	struct Pair { int a; int b; };
	// 	SharedPtr2<Pair> p(new Pair{10, 20});
	// 	SharedPtr2<int> alias(p, &p->b);
	// 	assert(*alias == 20);
	// 	assert(p.use_count() == 2);
	// }

	return 0;
}
