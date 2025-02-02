class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        if not s:
            return 0
        max_length = 0
        char_map = {}
        start = 0
        
        for i, char in enumerate(s):
            if char in char_map and start <= char_map[char]:
                start = char_map[char] + 1
            
            char_map[char] = i
            max_length = max(max_length, i - start + 1)

        return max_length




s = Solution()
assert s.lengthOfLongestSubstring("abcabcbb") == 3
assert s.lengthOfLongestSubstring("bb") == 1
assert s.lengthOfLongestSubstring("pwwkew") == 3
assert s.lengthOfLongestSubstring("aab") == 2
assert s.lengthOfLongestSubstring("cdd") == 2
assert s.lengthOfLongestSubstring("dvdf") == 3
assert s.lengthOfLongestSubstring("anviaj") == 5