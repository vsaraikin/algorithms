s1 = "leetcode"
wordDict1 = ["leet","code"]

s2 = "applepenapple"
wordDict2 = ["apple","pen"]

s3 = "catsandog"
wordDict3 = ["cats","dog","sand","and","cat"]

s4 = "aaaaaaa"
wordDict4 = ["aaaa","aaa"]


class Solution:
    def wordBreak(self, target: str, wordDict: list[str]) -> bool:
        n = len(target)
        dp = [False] * (n + 1)
        dp[0] = True
        
        for i in range(1, n+1):
            for j in range(i):
                if dp[j] and target[j:i] in wordDict:
                    dp[i] = True
                    break
        
        return dp[n]

                
    
s = Solution()    
assert True == s.wordBreak(s1, wordDict1)
assert True == s.wordBreak(s2, wordDict2)
assert False == s.wordBreak(s3, wordDict3)
assert True == s.wordBreak(s4, wordDict4)

