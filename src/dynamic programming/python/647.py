class Solution:
    # two pointers
    def countSubstrings(self, s: str) -> int:
        result = 0
        n = len(s)
        def expand(i, j):
            count = 0   
            while i >= 0 and j < n and s[i] == s[j]:
                count += 1
                i -= 1
                j += 1
            return count    
            
        for i in range(n):
            result += expand(i, i) + expand(i, i+1)
            
        return result
        
        
    # dynaminc programming
    def countSubstrings(self, s: str) -> int:
        count = 0
        n = len(s)
        dp = [[False] * n for _ in range(n)]
        for j in range(n):
            for i in range(0, j + 1):
                if s[i] == s[j] and (j - i < 2 or dp[i + 1][j - 1]):
                    dp[i][j] = True
                    count += 1
                        
        return count
        
s = Solution()
assert s.countSubstrings("abc") == 3
assert s.countSubstrings("aaa") == 6