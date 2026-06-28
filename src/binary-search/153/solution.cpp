#include <vector>
#include <cassert>

class Solution {
public:
    int findMin(std::vector<int>& nums) {
        int l = 0, r = (int)nums.size() - 1;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] > nums[r]) {
                l = mid + 1;       // min is strictly right of mid
            } else {
                r = mid;           // min is at mid or left of it
            }
        }
        return nums[l];
    }
};

int main() {
    Solution s;

    std::vector<int> input1 = {3, 4, 5, 1, 2};
    assert(s.findMin(input1) == 1);

    std::vector<int> input2 = {4, 5, 6, 7, 0, 1, 2};
    assert(s.findMin(input2) == 0);

    std::vector<int> input3 = {11, 13, 15, 17};
    assert(s.findMin(input3) == 11);  // not rotated

    std::vector<int> input4 = {1};
    assert(s.findMin(input4) == 1);

    std::vector<int> input5 = {2, 1};
    assert(s.findMin(input5) == 1);

    std::vector<int> input6 = {1, 2};
    assert(s.findMin(input6) == 1);

    std::vector<int> input7 = {5, 1, 2, 3, 4};
    assert(s.findMin(input7) == 1);  // rotated by 1

    std::vector<int> input8 = {-5, -3, 0, 2, 7};
    assert(s.findMin(input8) == -5);  // negatives, not rotated

    std::vector<int> input9 = {3, 4, 5, -2, -1, 0, 1, 2};
    assert(s.findMin(input9) == -2);  // negatives, rotated

    return 0;
}
