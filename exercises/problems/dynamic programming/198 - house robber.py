class Solution:
    def rob(self, nums: list[int]) -> int:
        n = len(nums)
        
        if n == 0:
            return
        elif n == 1:
            return nums[0]
    
        dp = [0] * n
        dp[0] = nums[0]
        dp[1] = max(nums[0], nums[1])
        
        
        for i in range(2, n):
            dp[i] = max(dp[i-2] + nums[i], dp[i-1])
                
        return dp[-1]    
        
s = Solution()

assert s.rob([1,2,3,1]) == 4
assert s.rob([2,7,9,3,1]) == 12

