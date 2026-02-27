from collections import defaultdict

class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        if len(s1) > len(s2):
            return False
        
        s1_freq = defaultdict(int)
        s2_freq = defaultdict(int)
        
        for i in range(len(s1)):
            s1_freq[s1[i]] += 1
            s2_freq[s2[i]] += 1
        
        if s1_freq == s2_freq:
            return True
        
        for i in range(len(s1), len(s2)):
            s2_freq[s2[i]] += 1
            s2_freq[s2[i - len(s1)]] -= 1
            
            if s2_freq[s2[i - len(s1)]] == 0:
                del s2_freq[s2[i - len(s1)]]
            
            if s1_freq == s2_freq:
                return True
        
        return False

    # solution with ord instead    
    def checkInclusionOrd(self, s1: str, s2: str) -> bool:
        if len(s1) > len(s2):
            return False
        
        s1_freq = [0] * 26
        s2_freq = [0] * 26
        a_ord = ord('a')
        
        for i in range(len(s1)):
            s1_freq[ord(s1[i]) - a_ord] += 1
            s2_freq[ord(s2[i]) - a_ord] += 1
        
        if s1_freq == s2_freq:
            return True
        
        for i in range(len(s1), len(s2)):
            s2_freq[ord(s2[i]) - a_ord] += 1
            s2_freq[ord(s2[i - len(s1)]) - a_ord] -= 1
            
            if s1_freq == s2_freq:
                return True
        
        return False


s = Solution()
assert s.checkInclusion("ab", "eidboaoo") == False
assert s.checkInclusion("ab", "eidbaooo") == True
assert s.checkInclusion("adc", "dcda") == True
                