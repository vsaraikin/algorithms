class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        if len(s1) > len(s2):
            return False
        
        s1_freq = {}
        s2_freq = {}
        
        for char in s1:
            s1_freq[char] = s1_freq.get(char, 0) + 1
        
        for i in range(len(s1)):
            s2_freq[s2[i]] = s2_freq.get(s2[i], 0) + 1
        
        if s1_freq == s2_freq:
            return True
        
        for i in range(len(s1), len(s2)):
            if s2_freq[s2[i - len(s1)]] == 1:
                del s2_freq[s2[i - len(s1)]]
            else:
                s2_freq[s2[i - len(s1)]] -= 1
            
            s2_freq[s2[i]] = s2_freq.get(s2[i], 0) + 1
            
            if s1_freq == s2_freq:
                return True
        
        return False


s = Solution()
assert s.checkInclusion("ab", "eidboaoo") == False
assert s.checkInclusion("ab", "eidbaooo") == True
assert s.checkInclusion("adc", "dcda") == True
                