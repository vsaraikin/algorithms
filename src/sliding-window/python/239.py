from collections import deque

class Solution:
    def maxSlidingWindow(self, nums: list[int], k: int) -> list[int]:
        if not nums:
            return []

        max_values = []
        window = deque()

        for right, num in enumerate(nums):
            # delete old elemets
            while window and window[0] < right - k + 1: 
                window.popleft()

            while window and nums[window[-1]] < num:
                window.pop()

            window.append(right)

            if right >= k - 1:
                max_values.append(nums[window[0]])

        return max_values

s = Solution()
assert s.maxSlidingWindow([1,3,-1,-3,5,3,6,7], 3) == [3,3,5,5,6,7]
assert s.maxSlidingWindow([1,3,1,2,0,5], 3) == [3, 3, 2, 5]