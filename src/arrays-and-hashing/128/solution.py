class Solution:
    def longestConsecutive(self, nums: list[int]) -> int:
        if not nums:
            return 0

        nums = sorted(set(nums))  # Remove duplicates and sort the list in ascending order.
        max_length = 1
        current_length = 1

        for i in range(1, len(nums)):
            if nums[i] == nums[i - 1] + 1:
                current_length += 1
            else:
                max_length = max(max_length, current_length)
                current_length = 1

        return max(max_length, current_length)
    
s = Solution()
assert s.longestConsecutive([100,4,200,1,3,2]) == 4
assert s.longestConsecutive([0,3,7,2,5,8,4,6,0,1]) == 9
assert s.longestConsecutive([0]) == 1
assert s.longestConsecutive([-8,-4,9,9,4,6,1,-4,-1,6,8]) == 2


