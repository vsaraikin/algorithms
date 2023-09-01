class Solution:
    def minSubArrayLen(self, target: int, nums: list[int]) -> int:
        left = 0
        
        min_len = float('inf')
        
        curr_sum = 0
        
        for right in range(len(nums)):
            curr_sum += nums[right]
            
            while curr_sum >= target:
                min_len = min(min_len, right - left + 1)
                curr_sum -= nums[left]
                left += 1   
        
        return min_len if min_len != float('inf') else 0
        
s = Solution()
assert s.minSubArrayLen(7, [2,3,1,2,4,3]) == 2
assert s.minSubArrayLen(4, [1,4,4]) == 1
assert s.minSubArrayLen(11, [1,1,1,1,1,1,1,1]) == 0
assert s.minSubArrayLen(11, [1,2,3,4,5]) == 3
assert s.minSubArrayLen(15, [1,2,3,4,5]) == 5
