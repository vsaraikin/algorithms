#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        std::sort(nums.begin(), nums.end());
        int n = nums.size();

        for (int i = 0; i < n - 2; i++) {
            if (i > 0 && nums[i] == nums[i-1]) {
                continue;
            }
            int left = i + 1, right = n - 1;
            int target = -nums[i];
            while (left < right) {
                int sum = nums[left] + nums[right];
                if (sum == target) {
                    result.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left+1]) {
                        left++;
                    }
                    while (left < right && nums[right] == nums[right-1]) {
                        right--;
                    }
                    ++left;
                    --right;
                } else if (sum < target) {
                    ++left;
                } else {
                    --right;
                }
            }

        }
        return result;
    }

};

// Test cases to validate the solution
void testThreeSum() {
    Solution solution;

    // Test case 1
    vector<int> nums1 = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> expected1 = {{-1, -1, 2}, {-1, 0, 1}};
    vector<vector<int>> result1 = solution.threeSum(nums1);
    sort(result1.begin(), result1.end());
    sort(expected1.begin(), expected1.end());
    assert(result1 == expected1 && "Test Case 1 Failed");

    // Test case 2: No valid triplet
    vector<int> nums2 = {0, 1, 1};
    vector<vector<int>> expected2 = {};
    vector<vector<int>> result2 = solution.threeSum(nums2);
    assert(result2 == expected2 && "Test Case 2 Failed");

    // Test case 3: All zeros
    vector<int> nums3 = {0, 0, 0};
    vector<vector<int>> expected3 = {{0, 0, 0}};
    vector<vector<int>> result3 = solution.threeSum(nums3);
    assert(result3 == expected3 && "Test Case 3 Failed");

    // Test case 4: No triplet with sum zero
    vector<int> nums4 = {1, 2, -2, -1};
    vector<vector<int>> expected4 = {};
    vector<vector<int>> result4 = solution.threeSum(nums4);
    assert(result4 == expected4 && "Test Case 4 Failed");

    cout << "All test cases passed!" << endl;
}

int main() {
    testThreeSum();
    return 0;
}