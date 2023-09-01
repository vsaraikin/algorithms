class Solution:
    def minWindow(self, s: str, t: str) -> str:
        char_count_t = {}
        
        for char in t:
            char_count_t[char] = char_count_t.get(char, 0) + 1
        
        left = 0
        min_window = ""
        min_length = float('inf')
        req_chars = len(char_count_t)
        formed_chars = 0
        window_char_count = {}
        
        for right, char in enumerate(s):
            window_char_count[char] = window_char_count.get(char, 0) + 1
            
            if char in char_count_t and window_char_count[char] == char_count_t[char]:
                formed_chars += 1
            
            while left <= right and formed_chars == req_chars:
                char = s[left]
                
                if right - left + 1 < min_length:
                    min_window = s[left:right + 1]
                    min_length = right - left + 1
                    
                window_char_count[char] -= 1
                if char in char_count_t and window_char_count[char] < char_count_t[char]:
                    formed_chars -= 1
                
                left += 1
                
        return min_window
    
        
s = Solution()
assert s.minWindow("ADOBECODEBANC", "ABC") == "BANC"
assert s.minWindow("a", "a") == "a"
assert s.minWindow("a", "aa") == ""