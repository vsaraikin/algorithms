nums1 = [1,2,3]
target1 = 4

nums2 = [9]
target2 = 3


class Solution:
    def combinationSum4(self, nums: list[int], target: int) -> int:
        dp = [0] * (target + 1)
        dp[0] = 1

        for i in range(1, target + 1):
            for num in nums:
                if i >= num:
                    dp[i] += dp[i - num]
        
        return dp[target]
        
s = Solution()
assert s.combinationSum4(nums1, target1) == 7
assert s.combinationSum4(nums2, target2) == 0
