class Solution:
    # recursions    
    def climbStairs(self, n: int) -> int:
        if n == 0 or n == 1:
            return 1
        return self.climbStairs(n-1) + self.climbStairs(n-2)
    
    # memorization
    def climbStairs(self, n: int, memo: dict = None) -> int:
        if memo is None:
            memo = {}
        if n in memo:
            return memo[n]
        if n <= 1:
            memo[n] = 1
        else:
            memo[n] = self.climbStairs(n-1, memo) + self.climbStairs(n-2, memo)
        return memo[n]
    
    # dp, o(n) memory
    def climbStairs(self, n: int) -> int:
        ways = [0] * (n + 1)
        ways[0], ways[1] = 1, 1
        for i in range(2, n + 1):
            ways[i] = ways[i-1] + ways[i-2]
        return ways[n]
    
    # dp, o(1) memory
    def climbStairs(self, n: int) -> int:
        prev2, prev1 = 1, 1
        for _ in range(2, n + 1):
            cur = prev2 + prev1
            prev2, prev1 = cur, prev2
        return cur
            
        
s = Solution()
assert 2 == s.climbStairs(2)
assert 3 == s.climbStairs(3)
assert 5 == s.climbStairs(4)

