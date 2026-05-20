#include <cassert>
#include <stack>
#include <vector>

class Solution {
  public:
	std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
		std::stack<int> st;
		std::vector<int> res(temperatures.size(), 0);
		for (int i = 0; i < temperatures.size(); ++i) {
			while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
				res[st.top()] = i - st.top(); 
				st.pop();
			}
			st.push(i);
		}
		return res;
	}
};

int main() {
	Solution s;

	std::vector<int> input1 = {73, 74, 75, 71, 69, 72, 76, 73};
	assert(s.dailyTemperatures(input1) ==
	       (std::vector<int>{1, 1, 4, 2, 1, 1, 0, 0}));

	std::vector<int> input2 = {30, 40, 50, 60};
	assert(s.dailyTemperatures(input2) == (std::vector<int>{1, 1, 1, 0}));

	std::vector<int> input3 = {30, 60, 90};
	assert(s.dailyTemperatures(input3) == (std::vector<int>{1, 1, 0}));

	std::vector<int> input4 = {90, 80, 70};
	assert(s.dailyTemperatures(input4) == (std::vector<int>{0, 0, 0}));

	std::vector<int> input5 = {50};
	assert(s.dailyTemperatures(input5) == (std::vector<int>{0}));

	std::vector<int> input6 = {50, 50, 50};
	assert(s.dailyTemperatures(input6) == (std::vector<int>{0, 0, 0}));

	std::vector<int> input7 = {89, 62, 70, 58, 47, 47, 46, 76, 100, 70};
	assert(s.dailyTemperatures(input7) ==
	       (std::vector<int>{8, 1, 5, 4, 3, 2, 1, 1, 0, 0}));

	return 0;
}
