#include <vector>

// cost = [1,100,1,1,1,100,1,1,100,1]  6
// cost = [10,15,20]  15


class Solution {
public:
    int minCostClimbingStairs(std::vector<int>& cost) {
		int n = cost.size();
        std::vector<int> dp(n + 1, 0);
		dp[0] = 0;
		dp[1] = 0;
		for (int i = 2; i <= n; ++i) {
			dp[i] = std::min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2]);
		}
		return dp[n];
    }
};