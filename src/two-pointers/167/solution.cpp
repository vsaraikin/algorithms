#include <cassert>
#include <vector>

class Solution {
  public:
	std::vector<int> twoSum(std::vector<int> &nums, int target) {
		int l = 0;
		int r = nums.size() - 1;

		while (l < r) {
			int s = nums[l] + nums[r];
			if (s == target) {
				return std::vector<int>{l + 1, r + 1};
			} else if (s < target) {
				++l;
			} else {
				--r;
			}
		}
		return {};
	}
};

int main() {
	Solution s;

	std::vector<int> input1 = {2, 7, 11, 15};
	assert(s.twoSum(input1, 9) == (std::vector<int>{1, 2}));

	std::vector<int> input2 = {2, 3, 4};
	assert(s.twoSum(input2, 6) == (std::vector<int>{1, 3}));

	std::vector<int> input3 = {-1, 0};
	assert(s.twoSum(input3, -1) == (std::vector<int>{1, 2}));

	std::vector<int> input4 = {1, 2, 3, 4, 4, 9, 56, 90};
	assert(s.twoSum(input4, 8) == (std::vector<int>{4, 5}));

	std::vector<int> input5 = {-3, -1, 0, 2, 4, 6};
	assert(s.twoSum(input5, 3) == (std::vector<int>{1, 6})); // -3 + 6

	std::vector<int> input6 = {5, 25, 75};
	assert(s.twoSum(input6, 100) == (std::vector<int>{2, 3}));

	return 0;
}
