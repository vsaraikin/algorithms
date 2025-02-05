class Solution:
    def minSubArrayLen(self, target: int, nums: list[int]) -> int:
        min_length = float('inf')
        left = 0
        current_sum = 0
        
        for right in range(len(nums)):
            current_sum += nums[right]
            
            while current_sum >= target:
                min_length = min(min_length, right - left + 1)
                current_sum -= nums[left]
                left += 1
                
        return 0 if min_length == float('inf') else min_length
        
s = Solution()
assert s.minSubArrayLen(7, [2,3,1,2,4,3]) == 2
assert s.minSubArrayLen(4, [1,4,4]) == 1
assert s.minSubArrayLen(11, [1,1,1,1,1,1,1,1]) == 0
assert s.minSubArrayLen(11, [1,2,3,4,5]) == 3
assert s.minSubArrayLen(15, [1,2,3,4,5]) == 5
