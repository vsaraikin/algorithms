nums1 = [10,9,2,5,3,7,101,18]
nums2 = [0,1,0,3,2,3]
nums3 = [7,7,7,7,7,7,7]
nums4 = [4,10,4,3,8,9]

import bisect


class Solution:
    # Dynamic programming, O(N^2)
    def lengthOfLIS(self, nums: list[int]) -> int:
        if not nums:
            return 0
        
        n = len(nums)
        dp = [1] * n
        for i in range(n):
            for j in range(i):
                if nums[i] > nums[j]:
                    dp[i] = max(dp[j] + 1, dp[i])
        
        return max(dp)
    
    # Binary search, O(nlogn)
    def lengthOfLIS_2(self, nums: list[int]) -> int:
        seq = [nums[0]]

        for num in nums:
            if seq[-1] < num:
                seq.append(num)
            else:
                el_index = bisect.bisect_left(seq, num)
                seq[el_index] = num

        return len(seq)
                

s = Solution()
assert 4 == s.lengthOfLIS(nums1)
assert 4 == s.lengthOfLIS(nums2)
assert 1 == s.lengthOfLIS(nums3)
assert 3 == s.lengthOfLIS(nums4)        
