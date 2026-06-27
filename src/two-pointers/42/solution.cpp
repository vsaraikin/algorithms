#include <algorithm>
#include <vector>
#include <cassert>

class Solution {
public:
	int trap(std::vector<int>& height) {
		if (height.empty()) return 0;

		int l = 0, r = (int)height.size() - 1;
		int leftMax = height[l], rightMax = height[r];
		int water = 0;

		while (l < r) {
			if (leftMax < rightMax) {
				l++;
				leftMax = std::max(leftMax, height[l]);
				water += leftMax - height[l];
			} else {
				r--;
				rightMax = std::max(rightMax, height[r]);
				water += rightMax - height[r];
			}
		}
		return water;
	}
};

int main() {
	Solution s;

	std::vector<int> input1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
	assert(s.trap(input1) == 6);

	std::vector<int> input2 = {4, 2, 0, 3, 2, 5};
	assert(s.trap(input2) == 9);

	std::vector<int> input3 = {1, 1, 1, 1};
	assert(s.trap(input3) == 0);

	std::vector<int> input4 = {5};
	assert(s.trap(input4) == 0);

	std::vector<int> input5 = {};
	assert(s.trap(input5) == 0);

	std::vector<int> input6 = {3, 0, 2, 0, 4};
	assert(s.trap(input6) == 7);

	std::vector<int> input7 = {0, 0, 0};
	assert(s.trap(input7) == 0);

	std::vector<int> input8 = {2, 1, 0, 1, 3};
	assert(s.trap(input8) == 4);

	return 0;
}
