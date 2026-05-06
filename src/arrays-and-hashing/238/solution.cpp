#include <vector>
#include <cassert>

class Solution {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums) {
        std::vector<int> product(nums.size());
        product[0] = 1;
        for (int i = 1; i < nums.size(); ++i) {
            product[i] = nums[i-1] * product[i-1];
        }

        int suffix = 1;
        for (int i = nums.size() - 1; i >= 0; --i) {
            product[i] *= suffix;
            suffix *= nums[i];
        }
        return product;
    }
};

int main() {
    Solution s;

    // std::vector<int> input1 = {1, 2, 3, 4};
    // assert(s.productExceptSelf(input1) == (std::vector<int>{24, 12, 8, 6}));

    std::vector<int> input2 = {-1, 1, 0, -3, 3};
    assert(s.productExceptSelf(input2) == (std::vector<int>{0, 0, 9, 0, 0}));

    std::vector<int> input3 = {2, 3};
    assert(s.productExceptSelf(input3) == (std::vector<int>{3, 2}));

    std::vector<int> input4 = {1, 1, 1, 1};
    assert(s.productExceptSelf(input4) == (std::vector<int>{1, 1, 1, 1}));

    std::vector<int> input5 = {0, 0};
    assert(s.productExceptSelf(input5) == (std::vector<int>{0, 0}));

    std::vector<int> input6 = {5, 0, 2};
    assert(s.productExceptSelf(input6) == (std::vector<int>{0, 10, 0}));

    std::vector<int> input7 = {-2, -3, -4};
    assert(s.productExceptSelf(input7) == (std::vector<int>{12, 8, 6}));

    return 0;
}
