# https://leetcode.com/problems/climbing-stairs/

class Solution:
    
    def climbStairs(self, n: int) -> int:
        ways = [1] * (n + 1)
        for i in range(2, n + 1):
            ways[i] = ways[i-1] + ways[i-2]
        return ways[n]
        
        
s = Solution()
assert 2 == s.climbStairs(2)
assert 3 == s.climbStairs(3)
assert 5 == s.climbStairs(4)

