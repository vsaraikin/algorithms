#include <algorithm>
#include <cassert>
#include <vector>

class Solution {
  public:
	// Greedy BFS by "levels": each level is the range reachable with one more
	// jump. We never need to look backwards — track the farthest reach within
	// the current level and bump the jump count when we exhaust it.
	int jump(std::vector<int>& nums) {
		int jumps = 0, curEnd = 0, farthest = 0;
		for (int i = 0; i < (int)nums.size() - 1; ++i) {
			farthest = std::max(farthest, i + nums[i]);
			if (i == curEnd) {     // consumed everything reachable so far
				++jumps;
				curEnd = farthest; // next level reaches up to `farthest`
			}
		}
		return jumps;
	}
};

int main() {
	Solution s;

	std::vector<int> input1 = {2, 3, 1, 1, 4};
	assert(s.jump(input1) == 2); // 2->3->4 or 2->1->4

	std::vector<int> input2 = {2, 3, 0, 1, 4};
	assert(s.jump(input2) == 2);

	std::vector<int> input3 = {0};
	assert(s.jump(input3) == 0); // already at last index

	std::vector<int> input4 = {1, 2};
	assert(s.jump(input4) == 1);

	std::vector<int> input5 = {1, 1, 1, 1};
	assert(s.jump(input5) == 3);

	std::vector<int> input6 = {5, 1, 1, 1, 1};
	assert(s.jump(input6) == 1); // one jump clears the array

	std::vector<int> input7 = {1, 2, 1, 1, 1};
	assert(s.jump(input7) == 3);

	return 0;
}
