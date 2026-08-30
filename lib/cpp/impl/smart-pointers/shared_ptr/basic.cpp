#include <cassert>
#include <cstddef>
#include <utility>

template <typename T> class SharedPtr {
  public:
	explicit SharedPtr(T *p = nullptr)
		: ptr_(p), cb_(p ? new std::size_t(1) : nullptr) {}

	SharedPtr(const SharedPtr &other) noexcept
		: ptr_(other.ptr_), cb_((other.cb_)) {
		if (cb_)
			++*cb_;
	}

	SharedPtr(SharedPtr &&other) noexcept
		: ptr_(other.ptr_), cb_(other.cb_) {
		other.ptr_ = nullptr;
		other.cb_ = nullptr;
	}

	SharedPtr &operator=(SharedPtr other) noexcept {
		swap(other);
		return *this;
	}

	~SharedPtr() { release(); }

	void swap(SharedPtr &other) noexcept {
		std::swap(ptr_, other.ptr_);
		std::swap(cb_, other.cb_);
	}

	void reset(T *p = nullptr) { SharedPtr(p).swap(*this); }

	T *get() const noexcept { return ptr_; }
	T &operator*() const noexcept { return *ptr_; }
	T *operator->() const noexcept { return ptr_; }
	explicit operator bool() const noexcept {return ptr_ != nullptr;}
	std::size_t use_count() const noexcept {return cb_ ? *cb_ : 0;}


  private:
	T *ptr_;
	std::size_t *cb_;

	void release() noexcept {
		if (cb_ && --*cb_ == 0) {
			delete ptr_;
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

	return 0;
}
