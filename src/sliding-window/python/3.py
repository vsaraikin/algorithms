class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        if not s:
            return 0
        char_index = {}
        start = 0
        max_length = 0
        for end, char in enumerate(s):
            if char in char_index and char_index[char] >= start:
                start = char_index[char] + 1

            char_index[char] = end
            max_length = max(max_length, end - start + 1)

        return max_length




s = Solution()
assert s.lengthOfLongestSubstring("abcabcbb") == 3
assert s.lengthOfLongestSubstring("bb") == 1
assert s.lengthOfLongestSubstring("pwwkew") == 3
assert s.lengthOfLongestSubstring("aab") == 2
assert s.lengthOfLongestSubstring("cdd") == 2
assert s.lengthOfLongestSubstring("dvdf") == 3
assert s.lengthOfLongestSubstring("anviaj") == 5