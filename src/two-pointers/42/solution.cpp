#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int totalValue = 0, leftMax = 0, rightMax = 0;
        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    totalValue += leftMax - height[left];
                }
                left++;
            } else {
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    totalValue += rightMax - height[right];
                }
                right--;

        }
    }
        return totalValue;
    }
};


int main() {
    Solution solution;

    // Test 1: Standard case
    vector<int> heights1 = {0,1,0,2,1,0,1,3,2,1,2,1};
    int result1 = solution.trap(heights1);
    assert(result1 == 6 && "Test 1 Failed"); // Explanation: 6 units of water trapped.

    // Test 2: Another standard case
    vector<int> heights2 = {4,2,0,3,2,5};
    int result2 = solution.trap(heights2);
    assert(result2 == 9 && "Test 2 Failed"); // Explanation: 9 units of water trapped.

    // Test 3: All flat (no trapping)
    vector<int> heights3 = {1,1,1,1,1};
    int result3 = solution.trap(heights3);
    assert(result3 == 0 && "Test 3 Failed"); // Explanation: No water is trapped.

    // Test 4: Decreasing heights (no trapping)
    vector<int> heights4 = {5,4,3,2,1};
    int result4 = solution.trap(heights4);
    assert(result4 == 0 && "Test 4 Failed"); // Explanation: No water is trapped.

    // Test 5: All zeros (no trapping)
    vector<int> heights5 = {0, 0, 0, 0};
    int result5 = solution.trap(heights5);
    assert(result5 == 0 && "Test 5 Failed"); // Explanation: No water is trapped.

    // Test 6: Single element
    vector<int> heights6 = {4};
    int result6 = solution.trap(heights6);
    assert(result6 == 0 && "Test 6 Failed"); // Explanation: No water is trapped with a single element.

    // Test 7: Only two elements
    vector<int> heights7 = {4, 2};
    int result7 = solution.trap(heights7);
    assert(result7 == 0 && "Test 7 Failed"); // Explanation: No water is trapped with only two elements.

    // Test 8: Heights with multiple trapped areas
    vector<int> heights8 = {0, 3, 0, 1, 0, 2, 1, 0, 2};
    int result8 = solution.trap(heights8);
    assert(result8 == 8 && "Test 8 Failed"); // Explanation: Multiple areas trap a total of 8 units.

    cout << "All tests passed successfully!" << endl;
    return 0;
}