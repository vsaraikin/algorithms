from heapq import heappop, heappush

class Solution:
    def kClosest(self, points: list[list[int]], k: int) -> list[list[int]]:
        heap = []
        for el in points:
            res = el[0] ** 2 + el[1] ** 2
            heappush(heap, (-res, el[0], el[1]))
            if len(heap) > k:
                heappop(heap)
        
        return [[x, y] for (_, x, y) in heap]
        