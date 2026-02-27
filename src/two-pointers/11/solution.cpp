#include <iostream>
#include <vector>
#include <cassert>

using namespace std;;

class Solution {
public:
    int maxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int maxValue = 0;
    while (left < right) {
        maxValue = max((right - left) * min(height[left], height[right]), maxValue);
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }

    }
    return maxValue;
    }
};

int main() {
    Solution solution;

    // Test 1: Basic test case
    vector<int> heights1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int result1 = solution.maxArea(heights1);
    assert(result1 == 49 && "Test 1 Failed");

    // Test 2: All heights are the same
    vector<int> heights2 = {1, 1, 1, 1, 1};
    int result2 = solution.maxArea(heights2);
    assert(result2 == 4 && "Test 2 Failed");

    // Test 3: Increasing heights
    vector<int> heights3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int result3 = solution.maxArea(heights3);
    assert(result3 == 25 && "Test 3 Failed");

    // Test 4: Decreasing heights
    vector<int> heights4 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int result4 = solution.maxArea(heights4);
    assert(result4 == 25 && "Test 4 Failed");

    // Test 5: Single element
    vector<int> heights5 = {10};
    int result5 = solution.maxArea(heights5);
    assert(result5 == 0 && "Test 5 Failed");

    // Test 6: Two elements
    vector<int> heights6 = {1, 2};
    int result6 = solution.maxArea(heights6);
    assert(result6 == 1 && "Test 6 Failed");

    cout << "All tests passed successfully!" << endl;
    return 0;
}