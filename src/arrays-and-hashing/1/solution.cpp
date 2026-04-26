#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> seen;
        for (int i = 0; i < nums.size(); i++)
        {
            int comp = target - nums[i];
            if (seen.count(comp))
            {
                return {seen[comp], i};
            }
            seen[nums[i]] = i;
        }
        return {};
    }
};

int main()
{
    Solution s = Solution();

    vector<int> input1 = {2, 7, 11, 15};
    assert(s.twoSum(input1, 9) == (vector<int>{0, 1}));

    vector<int> input2 = {3, 2, 4};
    assert(s.twoSum(input2, 6) == (vector<int>{1, 2}));

    vector<int> input3 = {3, 3};
    assert(s.twoSum(input3, 6) == (vector<int>{0, 1}));

    vector<int> input4 = {0, 4, 3, 0};
    assert(s.twoSum(input4, 0) == (vector<int>{0, 3}));

    vector<int> input5 = {-3, 4, 3, 90};
    assert(s.twoSum(input5, 0) == (vector<int>{0, 2}));

    return 0;
}