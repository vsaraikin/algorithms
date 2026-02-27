#include <vector>
#include <cassert>
#include <iostream>
using namespace std;

class Solution
{
public:
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> res;
        vector<int> subset;
        dfs(0, nums, subset, res);
        return res;
    }

private:
    void dfs(int idx,
             vector<int> &nums,
             vector<int> &subset,
             vector<vector<int>> &res)
    {
        res.push_back(subset);
        for (int j = idx; j < nums.size(); ++j)
        {
            subset.push_back(nums[j]);
            dfs(j + 1, nums, subset, res);
            subset.pop_back();
        }
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {1, 2};
    auto res = sol.subsets(nums);

    // should produce 4 subsets: [], [1], [1,2], [2]
    assert(res.size() == 4);
    assert(res[0].empty());
    assert(res[1] == vector<int>{1});
    assert((res[2] == vector<int>{1, 2}));
    assert(res[3] == vector<int>{2});

    cout << "All tests passed!" << endl;
    return 0;
}