class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        if not s:
            return s
        
        char_index = {}
        left = 0
        max_length = 0
        
        for right, char in enumerate(s):
            if char in char_index:
                if char_index[char] >= left:
                    left = char_index[char] + 1
            
            char_index[char] = right
            max_length = max(max_length, right - left + 1)
            
        return max_length
        
        
        
s = Solution()
assert s.lengthOfLongestSubstring("abcabcbb") == 3
assert s.lengthOfLongestSubstring("bbbbb") == 1
assert s.lengthOfLongestSubstring("pwwkew") == 3