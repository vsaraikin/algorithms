import math

class Solution:
    def minEatingSpeed(self, piles: list[int], h: int) -> int:
        left, right = 1, max(piles)
        res = right
        
        
        while left <= right:
            k = (left + right) // 2
            
            hours = 0
            for p in piles:
                hours += math.ceil(p / k)
            
            if hours <= h:
                right = k - 1
                res = min(res, k)
            else:
                left = k + 1
        
        return res
                
            
        
s = Solution()
assert s.minEatingSpeed([3,6,7,11], 8) == 4
assert s.minEatingSpeed([30,11,23,4,20], 5) == 30
assert s.minEatingSpeed([30,11,23,4,20], 6) == 23
