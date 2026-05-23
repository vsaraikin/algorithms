#include <cassert>
#include <vector>


class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        int start = 0;
        int end = nums.size() - 1;
        while (start <= end) {
			int i = (end + start) / 2;
            if (nums[i] == target) {
                return i;
            } else if (nums[i] < nums[end]) {
                if (nums[i] < target && target <= nums[end]) {
                    start = i + 1;
                } else {                
                    end = i - 1;
                }
            } else {
                if (nums[start] <= target && target < nums[i]) {
                    end = i - 1;
                } else {                
                    start = i + 1;
                }
            }
        }
        return -1;
    };
};


int main() {
	Solution s;

	std::vector<int> input1 = {4, 5, 6, 7, 0, 1, 2};
	assert(s.search(input1, 0) == 4);

	std::vector<int> input2 = {4, 5, 6, 7, 0, 1, 2};
	assert(s.search(input2, 3) == -1);

	std::vector<int> input3 = {1};
	assert(s.search(input3, 0) == -1);

	std::vector<int> input4 = {1};
	assert(s.search(input4, 1) == 0);

	std::vector<int> input5 = {1, 3};
	assert(s.search(input5, 3) == 1);

	std::vector<int> input6 = {3, 1};
	assert(s.search(input6, 1) == 1);

	std::vector<int> input7 = {5, 1, 3};
	assert(s.search(input7, 3) == 2);

	std::vector<int> input8 = {4, 5, 6, 7, 8, 1, 2, 3};
	assert(s.search(input8, 8) == 4);

	std::vector<int> input9 = {1, 2, 3, 4, 5};
	assert(s.search(input9, 3) == 2);

	std::vector<int> input10 = {6, 7, 1, 2, 3, 4, 5};
	assert(s.search(input10, 6) == 0);

	std::vector<int> input11 = {6, 7, 1, 2, 3, 4, 5};
	assert(s.search(input11, 5) == 6);

	return 0;
}
