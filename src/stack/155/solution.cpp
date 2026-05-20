#include <algorithm>
#include <cassert>
#include <stack>

class MinStack {
  public:
	MinStack() {}

	void push(int val) {
		st.push(val);
		if (!min_st.empty()) {
			min_st.push(std::min(st.top(), min_st.top()));
		} else {
			min_st.push(val);
		}
	}

	void pop() {
		st.pop();
		min_st.pop();
	}

	int top() { return this->st.top(); }

	int getMin() { return this->min_st.top(); }

  private:
	std::stack<int> st;
	std::stack<int> min_st;
};

int main() {
	MinStack ms;
	ms.push(-2);
	ms.push(0);
	ms.push(-3);
	assert(ms.getMin() == -3);
	ms.pop();
	assert(ms.top() == 0);
	assert(ms.getMin() == -2);

	MinStack ms2;
	ms2.push(5);
	assert(ms2.top() == 5);
	assert(ms2.getMin() == 5);
	ms2.push(3);
	assert(ms2.getMin() == 3);
	ms2.push(7);
	assert(ms2.getMin() == 3);
	ms2.pop();
	assert(ms2.getMin() == 3);
	ms2.pop();
	assert(ms2.getMin() == 5);

	MinStack ms3;
	ms3.push(2);
	ms3.push(2);
	ms3.push(2);
	assert(ms3.getMin() == 2);
	ms3.pop();
	assert(ms3.getMin() == 2);
	ms3.pop();
	assert(ms3.getMin() == 2);

	MinStack ms4;
	ms4.push(1);
	ms4.push(-1);
	ms4.push(-1);
	assert(ms4.getMin() == -1);
	ms4.pop();
	assert(ms4.getMin() == -1);
	ms4.pop();
	assert(ms4.getMin() == 1);

	return 0;
}
