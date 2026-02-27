import heapq
from heapq import heappop, heappush

class Solution:
    # recursion
    def lastStoneWeight(self, stones: list[int]) -> int:
        l = [-s for s in stones]
        heapq.heapify(l)

        def helper(l: list[int]):
            if len(l) == 0:
                return 0
            if len(l) == 1:
                return -l[0]

            x, y = heappop(l), heappop(l)
            diff = abs(x - y)
            if diff == 0:
                return helper(l)
            else:
                heappush(l, -diff)
                return helper(l)
        
        return helper(l)
    
    # iteration
    def lastStoneWeight(self, stones: list[int]) -> int:
        stones = [-s for s in stones]
        heapq.heapify(stones)

        while len(stones) > 1:
            x, y = heappop(stones), heappop(stones)
            diff = abs(x - y)
            if diff != 0:
               heappush(stones, -diff)

        return -stones[0] if len(stones) == 1 else 0
    