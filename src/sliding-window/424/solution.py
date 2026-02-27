class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        freq_storage = {}
        left, right = 0, 0
        max_count = 0 # highest frequency
        max_length = 0
        
        for right, char in enumerate(s):
            freq_storage[char] = freq_storage.get(char, 0) + 1
            max_count = max(max_count, freq_storage[char])
            while (right - left + 1) - max_count > k:
                freq_storage[s[left]] -= 1
                left += 1
            
            max_length = max(max_length, right - left + 1)
        
        return max_length
       
s = Solution() 
assert s.characterReplacement("ABAB", 2) == 4
assert s.characterReplacement("AABABBA", 1) == 4
