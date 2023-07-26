text1 = "abcde"
text2 = "ace" 

text3 = "abc"
text4 = "abc"

text5 = "abc"
text6 = "def"

class Solution:
    # Dynamic programming
    def longestCommonSubsequence(self, t1: str, t2: str) -> int:
        l1, l2 = len(t1), len(t2)
        dp = [[0] * (l2+1) for _ in range(l1 + 1)]
        
        for i in range(1, l1 + 1):
            for j in range(1, l2 + 1):
                if t1[i-1] == t2[j-1]:
                    dp[i][j] = dp[i-1][j-1] + 1
                else:
                    dp[i][j] = max(dp[i][j-1], dp[i-1][j])
                    
        return dp[l1][l2]
    
    # Recursion
    def longestCommonSubsequence(self, t1: str, t2: str) -> int:
        return self.helper(t1, t2, len(t1), len(t2))
        
    def helper(self, t1: str, t2: str, n1: int, n2: int):
        if n1 == 0 or n2 == 0:
            return 0
        elif t1[n1-1] == t2[n2-1]:
            return 1 + self.helper(t1, t2, n1-1, n2-1)
        else:
            return max(self.helper(t1, t2, n1-1, n2), self.helper(t1, t2, n1, n2-1))
    
s = Solution()
assert s.longestCommonSubsequence(text1, text2) == 3
assert s.longestCommonSubsequence(text3, text4) == 3
assert s.longestCommonSubsequence(text5, text6) == 0
