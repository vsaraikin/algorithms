class Solution:
    def countBits(self, n: int) -> list[int]:
        l = [*range(0, n + 1)]
        result = []
        for i in l:
            result.append(bin(i).count('1'))
        
        return result
    
s = Solution()
assert s.countBits(2) == [0, 1, 1]
assert s.countBits(5) == [0,1,1,2,1,2]
