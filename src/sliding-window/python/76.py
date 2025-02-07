class Solution:
    # O(m + n)
    def minWindow(self, s: str, t: str) -> str:
        char_count_t = {}
        
        for char in t:
            char_count_t[char] = char_count_t.get(char, 0) + 1
        
        formed, required = 0, len(char_count_t)
        window_count = {}
        
        min_left, min_length = 0, float('inf') # best offset with best limit
        
        left = 0
        for right in range(len(s)):
            char = s[right]
            window_count[char] = window_count.get(char, 0) + 1
            
            if char in char_count_t and window_count[char] == char_count_t[char]:
                formed += 1
            
            while formed == required:
                char = s[left]
                
                if right - left + 1 < min_length:
                    min_length = right - left + 1
                    min_left = left
                    
                window_count[char] -= 1
                if char in char_count_t and window_count[char] < char_count_t[char]:
                    formed -= 1
                    
                left += 1
        return "" if min_length == float('inf') else s[min_left:min_left + min_length]
    
        
s = Solution()
assert s.minWindow("ADOBECODEBANC", "ABC") == "BANC"
assert s.minWindow("a", "a") == "a"
assert s.minWindow("a", "aa") == ""