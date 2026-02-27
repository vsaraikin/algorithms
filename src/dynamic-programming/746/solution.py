class Solution:
    def minCostClimbingStairs(self, cost: list[int]) -> int:
        n = len(cost)
        dp = [0] * (n)
        dp[0] = cost[0]
        dp[1] = cost[1]
        for i in range(2, n):
            dp[i] = min(dp[i-2], dp[i-1]) + cost[i]
        return min(dp[i-1], dp[i])
            
    def minCostClimbingStairs(self, cost: list[int]) -> int:
        n = len(cost)
        a = cost[0]
        b = cost[1]
        for i in range(2, n):
            a, b = b, min(a, b) + cost[i]
        return min([a, b])
            
        
        
s = Solution()
assert s.minCostClimbingStairs([10,15,20]) == 15
assert s.minCostClimbingStairs([1,100,1,1,1,100,1,1,100,1]) == 6
