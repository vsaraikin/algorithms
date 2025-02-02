#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0, sum = 0, minLen = INT32_MAX;
        for (int right = 0; right < nums.size(); right++) {
            sum += nums[right];
            while (sum >= target) {
                minLen = min(minLen, right - left + 1);
                sum -= nums[left++];
            }
        }
        return minLen == INT32_MAX ? 0 : minLen;
    }
};

int main() {
    Solution solution;

    // Test Case 1
    int target1 = 7;
    vector<int> nums1 = {2,3,1,2,4,3};
    int expected1 = 2;
    assert(solution.minSubArrayLen(target1, nums1) == expected1);

    // Test Case 2
    int target2 = 4;
    vector<int> nums2 = {1,4,4};
    int expected2 = 1;
    assert(solution.minSubArrayLen(target2, nums2) == expected2);

    // Test Case 3
    int target3 = 11;
    vector<int> nums3 = {1,1,1,1,1,1,1,1};
    int expected3 = 0;
    assert(solution.minSubArrayLen(target3, nums3) == expected3);

    // Test Case 5
    int target5 = 15;
    vector<int> nums5 = {5,1,3,5,10,7,4,9,2,8};
    int expected5 = 2;
    assert(solution.minSubArrayLen(target5, nums5) == expected5);

    // Test Case 6
    int target6 = 8;
    vector<int> nums6 = {1,2,3,4,5};
    int expected6 = 2;
    assert(solution.minSubArrayLen(target6, nums6) == expected6);

    // Test Case 7
    int target7 = 1;
    vector<int> nums7 = {1};
    int expected7 = 1;
    assert(solution.minSubArrayLen(target7, nums7) == expected7);

    // Test Case 8
    int target8 = 100;
    vector<int> nums8 = {10,10,10,10,10};
    int expected8 = 0;
    assert(solution.minSubArrayLen(target8, nums8) == expected8);

    // Test Case 9
    int target9 = 5;
    vector<int> nums9 = {2,3,1,1,1,1,1};
    int expected9 = 2;
    assert(solution.minSubArrayLen(target9, nums9) == expected9);

    // Test Case 10
    int target10 = 6;
    vector<int> nums10 = {1,2,3,4,5};
    int expected10 = 2;
    assert(solution.minSubArrayLen(target10, nums10) == expected10);

    cout << "All tests passed successfully!\n";

    return 0;
}