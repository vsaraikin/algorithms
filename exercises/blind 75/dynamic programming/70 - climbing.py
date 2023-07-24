n1 = 2
n2 = 3
n3 = 4


class Solution:
    
    def climbStairs(self, n: int) -> int:
        ways = [1] * (n + 1)
        for i in range(2, n + 1):
            ways[i] = ways[i-1] + ways[i-2]
        return ways[n]
            
                    
        
        
        
s = Solution()
print(s.climbStairs(n1))
print(s.climbStairs(n2))
print(s.climbStairs(n3))

