class Solution:
    # dynamic programming
    def longestPalindrome(self, s: str) -> str:
        if not s:
            return ""
        
        n = len(s)
        start, end = 0, 0
        
        def expand(l: int, r: int):
            while l >= 0 and r < n and s[l] == s[r]:
                l -= 1
                r += 1
            return l + 1, r - 1
        
        for i in range(n):
            print(i)
            l1, r1 = expand(i, i)
            l2, r2 = expand(i, i + 1)
            if r1 - l1 > end - start:
                start, end = l1, r1
            if r2 - l2 > end - start:
                start, end = l2, r2
                
        return s[start:end+1]
    
    # dynaminc programming
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        if n < 2: return s
        dp = [[False] * n for _ in range(n)]
        start, maxLen = 0, 1
        for j in range(n):
            for i in range(0, j + 1):
                if s[i] == s[j] and (j - i < 2 or dp[i + 1][j - 1]):
                    dp[i][j] = True
                    if j - i + 1 > maxLen:
                        start = i
                        maxLen = j - i + 1
                        
        return s[start:start+maxLen]
        
        
        
s = Solution()
assert s.longestPalindrome("babad") == "bab"
# assert s.longestPalindrome("cbbd") == "bb"