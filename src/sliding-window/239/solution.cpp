#include <algorithm>
#include <cassert>
#include <deque>
#include <vector>

class Solution {
  public:
	std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
		std::vector<int> res;
		std::deque<int> dq;
		for (int r = 0; r < (int)nums.size(); ++r) {
			while (!dq.empty() && nums[r] >= nums[dq.back()]) {
				dq.pop_back();
			}
			dq.push_back(r);

			if (dq.front() <= r - k) {
				dq.pop_front();
			}

			if (r >= k - 1) {
				res.push_back(nums[dq.front()]);
			}
		}
		
		return res;
	}
};


int main() {
	Solution s;

	std::vector<int> input1 = {1, 3, -1, -3, 5, 3, 6, 7};
	assert(s.maxSlidingWindow(input1, 3) ==
	       (std::vector<int>{3, 3, 5, 5, 6, 7}));

	std::vector<int> input2 = {1};
	assert(s.maxSlidingWindow(input2, 1) == (std::vector<int>{1}));

	std::vector<int> input3 = {1, -1};
	assert(s.maxSlidingWindow(input3, 1) == (std::vector<int>{1, -1}));

	std::vector<int> input4 = {9, 11};
	assert(s.maxSlidingWindow(input4, 2) == (std::vector<int>{11}));

	std::vector<int> input5 = {4, -2};
	assert(s.maxSlidingWindow(input5, 2) == (std::vector<int>{4}));

	std::vector<int> input6 = {1, 3, 1, 2, 0, 5};
	assert(s.maxSlidingWindow(input6, 3) == (std::vector<int>{3, 3, 2, 5}));

	std::vector<int> input7 = {7, 2, 4};
	assert(s.maxSlidingWindow(input7, 2) == (std::vector<int>{7, 4}));

	std::vector<int> input8 = {-7, -8, 7, 5, 7, 1, 6, 0};
	assert(s.maxSlidingWindow(input8, 4) ==
	       (std::vector<int>{7, 7, 7, 7, 7}));

	return 0;
}
