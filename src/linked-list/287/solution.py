class Solution:
    # принцип Дирихле, pigeonhole principle
    # there will be a repeat
    def findDuplicate(self, nums: list[int]) -> int:
        slow = nums[0]
        fast = nums[0]
        
        while True:
            slow = nums[slow]
            fast = nums[nums[fast]]
            if slow == fast:
                break
        
        slow = nums[0]
        while slow != fast:
            slow = nums[slow]
            fast = nums[fast]
        
        return slow

s = Solution()
assert s.findDuplicate([1, 3, 4, 2, 2]) == 2
assert s.findDuplicate([3, 1, 3, 4, 2]) == 3
print('Passed!')