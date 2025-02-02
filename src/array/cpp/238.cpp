#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);

        int leftProduct = 1;
        for (int i = 0; i < n; ++i) {
            result[i] = leftProduct;
            leftProduct *= nums[i];
        }

        int rightProduct = 1;
        for (int i = n - 1; i >= 0; --i) {
            result[i] *= rightProduct;
            rightProduct *= nums[i];
        }

        return result;
    }
};

int main() {
    Solution solution;

    vector<int> test1 = {1, 2, 3, 4};
    vector<int> result1 = solution.productExceptSelf(test1);
    assert(result1 == vector<int>({24, 12, 8, 6}) && "Test 1 Failed");

    vector<int> test2 = {-1, 1, 0, -3, 3};
    vector<int> result2 = solution.productExceptSelf(test2);
    assert(result2 == vector<int>({0, 0, 9, 0, 0}) && "Test 2 Failed");

    vector<int> test3 = {2, 3, 4, 5};
    vector<int> result3 = solution.productExceptSelf(test3);
    assert(result3 == vector<int>({60, 40, 30, 24}) && "Test 3 Failed");

    vector<int> test4 = {1, 1, 1, 1};
    vector<int> result4 = solution.productExceptSelf(test4);
    assert(result4 == vector<int>({1, 1, 1, 1}) && "Test 4 Failed");

    vector<int> test5 = {9, 0, -2};
    vector<int> result5 = solution.productExceptSelf(test5);
    assert(result5 == vector<int>({0, -18, 0}) && "Test 5 Failed");

    cout << "All tests passed successfully!" << endl;
    return 0;
}