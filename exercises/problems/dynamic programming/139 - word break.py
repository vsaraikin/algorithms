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
        wordSet = set(wordDict)
        words = []
        
        s = ''
         
        for z in range(len(target)):
            p = ''
            for l in words:
                p += l
            if len(p) >= len(target):
                break
                    
                
            
            s += target[z]
            if s in wordSet:
                # if there is a longer word, don't append
                y = s
                for k in range(z, len(target)):
                    y += target[k]
                    if y in wordSet:
                        words.append(y)
                # else
                
                words.append(s)
                s = ''
                
        q = ''
        for w in words:
            q += w

        return q == target    

                
    
s = Solution()    
assert True == s.wordBreak(s1, wordDict1)
assert True == s.wordBreak(s2, wordDict2)
assert False == s.wordBreak(s3, wordDict3)
assert True == s.wordBreak(s4, wordDict4)

