class Solution:
    def findDuplicate(self, nums: list[int]) -> int:
        # Step 1: Find the intersection point
        slow = nums[0]
        fast = nums[0]
        
        # Move slow by 1 step and fast by 2 steps to find intersection
        while True:
            slow = nums[slow]
            fast = nums[nums[fast]]
            if slow == fast:
                break  # Intersection found
        
        # Step 2: Find the entrance to the cycle (duplicate number)
        slow = nums[0]  # Reset slow to start
        while slow != fast:
            slow = nums[slow]
            fast = nums[fast]
        
        return slow  # The duplicate number