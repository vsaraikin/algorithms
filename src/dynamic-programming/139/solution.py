# https://leetcode.com/problems/word-break/

class Solution:
    def wordBreak(self, target: str, wordDict: list[str]) -> bool:
        n = len(target)
        dp = [False] * (n + 1)
        dp[0] = True # handle empty substring
        
        for i in range(1, n+1):
            for j in range(i):
                if dp[j] and target[j:i] in wordDict:
                    dp[i] = True
                    break
        
        return dp[n]

s = Solution()    
assert True == s.wordBreak("leetcode", ["leet","code"])
assert True == s.wordBreak("applepenapple", ["apple","pen"])
assert False == s.wordBreak("catsandog", ["cats","dog","sand","and","cat"])
assert True == s.wordBreak("aaaaaaa", ["aaaa","aaa"])
