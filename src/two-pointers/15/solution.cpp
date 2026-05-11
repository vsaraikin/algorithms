#include <vector>
#include <algorithm>
#include <cassert>

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> res;
        for (int i = 0; i < nums.size() - 2; ++i) {
            if (nums[i] > 0) {
                break;
            }
            if (i > 0 && nums[i] == nums[i-1]) {
                continue;
            }

            int l = i + 1; int r = nums.size() - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum == 0) {
                    res.push_back({
                        nums[i], nums[l], nums[r]
                    });
                    while (l < r && nums[l] == nums[l+1]) {
                        l++;
                    }
                    while (l < r && nums[r] == nums[r-1]) {
                        r--;
                    }
                    l++; r--;
                } else if (sum < 0) {
                    l++;
                } else {
                    r--;
                }
            }
        }
        return res;
    }
};

static std::vector<std::vector<int>> normalize(
    std::vector<std::vector<int>> triplets) {
    for (auto& t : triplets) std::sort(t.begin(), t.end());
    std::sort(triplets.begin(), triplets.end());
    return triplets;
}

int main() {
    Solution s;

    std::vector<int> input1 = {-1, 0, 1, 2, -1, -4};
    assert(normalize(s.threeSum(input1)) == normalize(
        std::vector<std::vector<int>>{{-1, -1, 2}, {-1, 0, 1}}));

    std::vector<int> input2 = {0, 1, 1};
    assert(normalize(s.threeSum(input2)) == normalize(
        std::vector<std::vector<int>>{}));

    std::vector<int> input3 = {0, 0, 0};
    assert(normalize(s.threeSum(input3)) == normalize(
        std::vector<std::vector<int>>{{0, 0, 0}}));

    std::vector<int> input4 = {0, 0, 0, 0};
    assert(normalize(s.threeSum(input4)) == normalize(
        std::vector<std::vector<int>>{{0, 0, 0}}));  // no duplicates

    std::vector<int> input5 = {-2, 0, 1, 1, 2};
    assert(normalize(s.threeSum(input5)) == normalize(
        std::vector<std::vector<int>>{{-2, 0, 2}, {-2, 1, 1}}));

    std::vector<int> input6 = {1, 2, -2, -1};
    assert(normalize(s.threeSum(input6)) == normalize(
        std::vector<std::vector<int>>{}));

    std::vector<int> input7 = {-1, 0, 1, 0};
    assert(normalize(s.threeSum(input7)) == normalize(
        std::vector<std::vector<int>>{{-1, 0, 1}}));

    return 0;
}
