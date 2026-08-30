#include <atomic>
#include <cassert>
#include <cstddef>
#include <thread>
#include <utility>
#include <vector>

struct ControlBlock {
	std::atomic<std::size_t> strong{1};
	std::atomic<std::size_t> weak{1};
};

template <typename T> class WeakPtr;

template <typename T> class SharedPtr {
  public:
	friend class WeakPtr<T>; // lets to access WeakPtr this class

	// explicit wrappes SharedPtr<int> p(raw) blocking wrapping a raw pointer
	explicit SharedPtr(T *p = nullptr)
		: ptr_(p), cb_(p ? new ControlBlock() : nullptr) {}

	// copy constructor
	SharedPtr(const SharedPtr &other) noexcept
		: ptr_(other.ptr_), cb_(other.cb_) {
		if (cb_)
			cb_->strong.fetch_add(1, std::memory_order_relaxed);
	}

	// move constructor
	SharedPtr(SharedPtr &&other) noexcept : ptr_(other.ptr_), cb_(other.cb_) {
		other.ptr_ = nullptr;
		other.cb_ = nullptr;
	}

	// copy + move assignment
	SharedPtr &operator=(SharedPtr other) noexcept {
		swap(other);
		return *this;
	}

	// owner left
	~SharedPtr() { release(); }

	void swap(SharedPtr &other) noexcept {
		std::swap(ptr_, other.ptr_);
		std::swap(cb_, other.cb_);
	}

	void reset(T *p = nullptr) { SharedPtr(p).swap(*this); }

	// access like for the usual poitner
	T *get() const noexcept { return ptr_; }
	T &operator*() const noexcept { return *ptr_; }
	T *operator->() const noexcept { return ptr_; }
	
	// allows to write `if (p)`
	explicit operator bool() const noexcept { return ptr_ != nullptr; }
	std::size_t use_count() const noexcept {
		return cb_ ? cb_->strong.load(std::memory_order_relaxed) : 0;
	}

  private:
	T *ptr_;
	ControlBlock *cb_;

	// records two pointers
	SharedPtr(T *p, ControlBlock *cb) noexcept : ptr_(p), cb_(cb) {}

	void release() noexcept {
		if (cb_ && cb_->strong.fetch_sub(1, std::memory_order_acq_rel) == 1) {
			delete ptr_;
			if (cb_->weak.fetch_sub(1, std::memory_order_acq_rel) == 1) {
				delete cb_;
			}
		}
		ptr_ = nullptr;
		cb_ = nullptr;
	}
};

template <typename T> class WeakPtr {
  public:
	// empty observer
	WeakPtr() noexcept : ptr_(nullptr), cb_(nullptr) {}

	// start observing: weak + 1, strong untouched (no ownership)
	WeakPtr(const SharedPtr<T> &sp) noexcept : ptr_(sp.ptr_), cb_(sp.cb_) {
		if (cb_)
			cb_->weak.fetch_add(1, std::memory_order_relaxed);
	}

	// copy constructor
	WeakPtr(const WeakPtr &other) noexcept : ptr_(other.ptr_), cb_(other.cb_) {
		if (cb_)
			cb_->weak.fetch_add(1, std::memory_order_relaxed);
	}

	// move constructor
	WeakPtr(WeakPtr &&other) noexcept : ptr_(other.ptr_), cb_(other.cb_) {
		other.ptr_ = nullptr;
		other.cb_ = nullptr;
	}

	// copy + move assignment (copy-and-swap)
	WeakPtr &operator=(WeakPtr other) noexcept {
		swap(other);
		return *this;
	}

	// destructor - observer left
	~WeakPtr() { release(); }

	void swap(WeakPtr &other) noexcept {
		std::swap(ptr_, other.ptr_);
		std::swap(cb_, other.cb_);
	}

	// observe -> temporarily own: CAS so we never bump a zero strong
	SharedPtr<T> lock() const noexcept {
		if (!cb_)
			return SharedPtr<T>();
		std::size_t s = cb_->strong.load(std::memory_order_relaxed);
		while (s != 0) {
			if (cb_->strong.compare_exchange_weak(s, s + 1,
												  std::memory_order_acq_rel,
												  std::memory_order_relaxed)) {
				return SharedPtr<T>(ptr_, cb_);
			}
		}
		return SharedPtr<T>();
	}

	// object already destroyed? (block may still be alive)
	bool expired() const noexcept {
		return !cb_ || cb_->strong.load(std::memory_order_acquire) == 0;
	}
	// how many owners are left
	std::size_t use_count() const noexcept {
		return cb_ ? cb_->strong.load(std::memory_order_relaxed) : 0;
	}

  // no get()/operator*/->: an observer never touches the object directly
  private:
	// may dangle after the object dies - never dereferenced
	T *ptr_;
	ControlBlock *cb_;

	// only the block is ours: delete it when we are the last weak
	void release() noexcept {
		if (cb_ && cb_->weak.fetch_sub(1, std::memory_order_acq_rel) == 1) {
			delete cb_;
		}
		ptr_ = nullptr;
		cb_ = nullptr;
	}
};

struct Tracked {
	static int alive;
	int value;
	explicit Tracked(int v) : value(v) { ++alive; }
	~Tracked() { --alive; }
};
int Tracked::alive = 0;

struct Node {
	static int alive;
	SharedPtr<Node> next;
	WeakPtr<Node> prev;
	Node() { ++alive; }
	~Node() { --alive; }
};
int Node::alive = 0;

int main() {
	{
		SharedPtr<Tracked> a(new Tracked(7));
		assert(a.use_count() == 1);
		{
			SharedPtr<Tracked> b = a;
			assert(a.use_count() == 2 && b.use_count() == 2);
			assert(b->value == 7 && (*b).value == 7);
		}
		assert(a.use_count() == 1);
		assert(Tracked::alive == 1);
	}
	assert(Tracked::alive == 0);

	{
		SharedPtr<Tracked> a(new Tracked(1));
		SharedPtr<Tracked> b = std::move(a);
		assert(!a && a.use_count() == 0);
		assert(b && b.use_count() == 1);
	}
	assert(Tracked::alive == 0);

	{
		SharedPtr<Tracked> a(new Tracked(1));
		SharedPtr<Tracked> b(new Tracked(2));
		a = b;
		assert(Tracked::alive == 1 && a.use_count() == 2 && a->value == 2);
		a = a;
		assert(a.use_count() == 2);
		a.reset();
		assert(!a && b.use_count() == 1);
	}
	assert(Tracked::alive == 0);

	{
		WeakPtr<Tracked> w;
		{
			SharedPtr<Tracked> a(new Tracked(5));
			w = WeakPtr<Tracked>(a);
			assert(!w.expired() && w.use_count() == 1);
			assert(a.use_count() == 1);
			WeakPtr<Tracked> w2 = w;
			assert(w2.use_count() == 1);
		}
		assert(Tracked::alive == 0);
		assert(w.expired() && w.use_count() == 0);
	}

	{
		SharedPtr<Tracked> a(new Tracked(6));
		{
			WeakPtr<Tracked> w(a);
		}
		assert(a.use_count() == 1 && a->value == 6 && Tracked::alive == 1);
	}
	assert(Tracked::alive == 0);

	{
		WeakPtr<Tracked> w;
		{
			SharedPtr<Tracked> a(new Tracked(8));
			w = a;
			SharedPtr<Tracked> l = w.lock();
			assert(l && l->value == 8 && a.use_count() == 2);
		}
		assert(Tracked::alive == 0);
		SharedPtr<Tracked> l = w.lock();
		assert(!l && l.use_count() == 0);
	}

	{
		SharedPtr<Tracked> a(new Tracked(9));
		WeakPtr<Tracked> w(a);
		SharedPtr<Tracked> keep = w.lock();
		a.reset();
		assert(Tracked::alive == 1 && keep.use_count() == 1 && !w.expired());
	}
	assert(Tracked::alive == 0);

	{
		SharedPtr<Node> a(new Node());
		SharedPtr<Node> b(new Node());
		a->next = b;
		b->prev = a;
		assert(a.use_count() == 1 && b.use_count() == 2);
		assert(b->prev.lock().get() == a.get());
	}
	assert(Node::alive == 0);

	{
		SharedPtr<Tracked> root(new Tracked(1));
		WeakPtr<Tracked> w(root);
		std::vector<std::thread> ts;
		for (int t = 0; t < 8; ++t) {
			ts.emplace_back([&] {
				for (int i = 0; i < 20000; ++i) {
					SharedPtr<Tracked> c = root;
					SharedPtr<Tracked> l = w.lock();
					assert(l && l->value == 1);
				}
			});
		}
		for (auto &t : ts)
			t.join();
		assert(root.use_count() == 1 && Tracked::alive == 1);
	}
	assert(Tracked::alive == 0);

	{
		auto *holder = new SharedPtr<Tracked>(new Tracked(2));
		WeakPtr<Tracked> w(*holder);
		std::vector<std::thread> ts;
		for (int t = 0; t < 4; ++t) {
			ts.emplace_back([&] {
				for (int i = 0; i < 20000; ++i) {
					if (SharedPtr<Tracked> l = w.lock()) {
						assert(l->value == 2);
					}
				}
			});
		}
		std::this_thread::yield();
		delete holder;
		for (auto &t : ts)
			t.join();
		assert(w.expired() && Tracked::alive == 0);
	}

	return 0;
}
