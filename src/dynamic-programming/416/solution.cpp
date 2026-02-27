#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <numeric>

using namespace std;

class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0)
            return false;
        int target = sum / 2;
        vector<bool> dp(nums.size() + 1, false);
        dp[0] = true;
        for (const int el : nums)
        {
            for (int i = target; i >= el; i--)
            {
                dp[i] = dp[i] || dp[i - el];
                cout << i << " " << el << " " << dp[i] << "\n";
            }
        }
        return dp[target];
    }
};

int main()
{
    Solution s;
    {
        vector<int> nums = {1, 5, 11, 5};
        cout << s.canPartition(nums);
    }
    return 0;
}