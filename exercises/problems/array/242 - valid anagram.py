class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        if len(s) != len(t):
            return False
        
        d1 = {}
        d2 = {}
        
        for i in s:
            d1[i] = d1.get(i, 0) + 1
            
        for x in t:
            d2[x] = d2.get(x, 0) + 1
            
        return d1 == d2
        
        
       
s = Solution()        
# assert True == s.isAnagram("anagram", "nagaram")
assert False == s.isAnagram("car", "rat")

