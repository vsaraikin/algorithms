class Solution:
    # def rob_h(self, nums: list[int]) -> int:
    #     n = len(nums)
        
    #     if n == 0:
    #         return
    #     elif n == 1:
    #         return nums[0]
    
    #     dp = [0] * n
    #     dp[0] = nums[0]
    #     dp[1] = max(nums[0], nums[1])
        
        
    #     for i in range(2, n):
    #         dp[i] = max(dp[i-2] + nums[i], dp[i-1])
                
    #     return dp[-1]   
    
    # def rob(self, nums: list[int]) -> int:
    #     n = len(nums)

    #     if n == 0:
    #         return
    #     elif n == 1:
    #         return nums[0]
        
    #     return max(self.rob_h(nums[1:]), self.rob_h(nums[:-1]))
    
    def rob(self, nums: list[int]) -> int:
        if not nums:
            return 0
        elif len(nums) == 1:
            return nums[0]
        
        def helper(arr: list[int]) -> int:
            prev = curr = 0
            for a in arr:
                curr, prev = max(curr, a + prev), curr
            print(curr)
            return curr
                
        return max(helper(nums[1:]), helper(nums[:-1]))
    
        
s = Solution()

assert s.rob([1,2,3,1]) == 4
assert s.rob([1,2,3]) == 3
assert s.rob([1,2,3,4,5]) == 8
assert s.rob([1,2,3,7,5]) == 9

