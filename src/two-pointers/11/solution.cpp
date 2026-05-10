#include <algorithm>
#include <vector>
#include <cassert>

class Solution {
public:
    int maxArea(std::vector<int>& height) {
        int maxArea = 0;
        int l = 0, r = height.size() - 1;
        while (l <= r) {
            int sq = (r - l) * std::min(height[l], height[r]);
            maxArea = std::max(sq, maxArea);
            if (height[l] > height[r]) {
                r--;
            } else {
                l++;
            }
        }
        return maxArea;
    }
};

int main() {
    Solution s;

    std::vector<int> input1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    assert(s.maxArea(input1) == 49);

    std::vector<int> input2 = {1, 1};
    assert(s.maxArea(input2) == 1);

    std::vector<int> input3 = {4, 3, 2, 1, 4};
    assert(s.maxArea(input3) == 16);  // walls at index 0 and 4

    std::vector<int> input4 = {1, 2, 1};
    assert(s.maxArea(input4) == 2);

    std::vector<int> input5 = {2, 3, 4, 5, 18, 17, 6};
    assert(s.maxArea(input5) == 17);

    std::vector<int> input6 = {1, 2, 4, 3};
    assert(s.maxArea(input6) == 4);

    return 0;
}
