#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];

            if (sum == target) {
                return {left + 1, right + 1};
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }

        return {};
    }
};


int main() {
    Solution solution;

    // Test case 1: Normal case
    vector<int> numbers1 = {2, 7, 11, 15};
    int target1 = 9;
    vector<int> result1 = solution.twoSum(numbers1, target1);
    assert(result1 == vector<int>({1, 2}) && "Test 1 Failed");

    // Test case 2: Larger numbers
    vector<int> numbers2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int target2 = 11;
    vector<int> result2 = solution.twoSum(numbers2, target2);
    assert(result2 == vector<int>({1, 10}) && "Test 2 Failed");

    // Test case 3: Negative numbers
    vector<int> numbers3 = {-10, -3, 0, 5, 9};
    int target3 = 6;
    vector<int> result3 = solution.twoSum(numbers3, target3);
    assert(result3 == vector<int>({2, 5}) && "Test 3 Failed");

    // Test case 4: Multiple solutions but single valid one
    vector<int> numbers4 = {1, 3, 4, 5, 7, 10, 11};
    int target4 = 9;
    vector<int> result4 = solution.twoSum(numbers4, target4);
    assert(result4 == vector<int>({3, 4}) && "Test 4 Failed");

    // Test case 5: Two identical elements that sum up to the target
    vector<int> numbers5 = {1, 3, 4, 4};
    int target5 = 8;
    vector<int> result5 = solution.twoSum(numbers5, target5);
    assert(result5 == vector<int>({3, 4}) && "Test 5 Failed");

    cout << "All tests passed successfully!" << endl;    return 0;
}
