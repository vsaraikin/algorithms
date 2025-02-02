#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    result.push_back(i);
                    result.push_back(j);
                    return result;
                }
            }
        }
        return result;
    }
};


int main() {
    Solution s;
    vector<int> test1 = {2, 7, 11, 15};
    vector<int> result1 = s.twoSum(test1, 9);
    assert(result1[0] == 0 && result1[1] == 1 && "Test 1 Failed");

    vector<int> test2 = {3, 2, 4};
    vector<int> result2 = s.twoSum(test2, 6);
    assert(result2[0] == 1 && result2[1] == 2 && "Test 2 Failed");

    vector<int> test3 = {3, 3};
    vector<int> result3 = s.twoSum(test3, 6);
    assert(result3[0] == 0 && result3[1] == 1 && "Test 3 Failed");

    cout << "All tests passed!" << endl;
}