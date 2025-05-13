from heapq import heappush, heappop


class KthLargest:

    def __init__(self, k: int, nums: list[int]):
        self.nums = []
        self.k = k
        for n in nums:
            self.add(n)
        

    def add(self, val: int) -> int:
        heappush(self.nums, val)
        if len(self.nums) > self.k:
            heappop(self.nums)
        return self.nums[0]