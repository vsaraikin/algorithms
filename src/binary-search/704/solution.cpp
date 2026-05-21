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
            } else if (nums[i] > target) {
                end = i - 1;
            } else {
                start = i + 1;
            }
        }
        return -1;
    };
};


int main() {
	Solution s;

	std::vector<int> input1 = {-1, 0, 3, 5, 9, 12};
	assert(s.search(input1, 9) == 4);

	std::vector<int> input2 = {-1, 0, 3, 5, 9, 12};
	assert(s.search(input2, 2) == -1);

	std::vector<int> input3 = {5};
	assert(s.search(input3, 5) == 0);

	std::vector<int> input4 = {5};
	assert(s.search(input4, -1) == -1);

	std::vector<int> input5 = {2, 5};
	assert(s.search(input5, 2) == 0);

	std::vector<int> input6 = {2, 5};
	assert(s.search(input6, 5) == 1);

	std::vector<int> input7 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	assert(s.search(input7, 1) == 0);

	std::vector<int> input8 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	assert(s.search(input8, 10) == 9);

	std::vector<int> input9 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	assert(s.search(input9, 11) == -1);

	std::vector<int> input10 = {-10, -5, -1, 0, 3};
	assert(s.search(input10, -5) == 1);

	return 0;
}
