class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        max_length = 0
        max_freq = 0 
        left = 0
        char_count = {}
        
        for right in range(len(s)):
            
            char_count[s[right]] = char_count.get(s[right], 0) + 1
            
            max_freq = max(char_count[s[right]], max_freq)
            
            changes_needed = (right - left + 1) - max_freq
            
            if changes_needed > k:
                char_count[s[left]] -= 1
                left += 1
            
            max_length = max(max_length, right - left + 1)

        
        return max_length
       
s = Solution() 
assert s.characterReplacement("ABAB", 2) == 4
assert s.characterReplacement("AABABBA", 1) == 4
