#include <cmath>
#include <vector>
#include <cassert>

class Solution {
public:
    std::vector<int> sortedSquares(std::vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        int i = nums.size() - 1;
        std::vector<int> res(nums.size());
        while (l <= r) {
            int sqL = pow(nums[l], 2), tmpR = pow(nums[r], 2);
            if (sqL > tmpR) {
                res[i--] = sqL;
                l++;
            } else {
                res[i--] = tmpR;
                r--;
            }
        }
        return res;
    }
};

int main() {
    Solution s;

    std::vector<int> v1 = {-4, -1, 0, 3, 10};
    assert(s.sortedSquares(v1) == (std::vector<int>{0, 1, 9, 16, 100}));

    std::vector<int> v2 = {-7, -3, 2, 3, 11};
    assert(s.sortedSquares(v2) == (std::vector<int>{4, 9, 9, 49, 121}));

    std::vector<int> v3 = {-1};
    assert(s.sortedSquares(v3) == (std::vector<int>{1}));

    std::vector<int> v4 = {0};
    assert(s.sortedSquares(v4) == (std::vector<int>{0}));

    std::vector<int> v5 = {-5, -3, -1};
    assert(s.sortedSquares(v5) == (std::vector<int>{1, 9, 25}));

    std::vector<int> v6 = {1, 2, 3};
    assert(s.sortedSquares(v6) == (std::vector<int>{1, 4, 9}));

    return 0;
}
