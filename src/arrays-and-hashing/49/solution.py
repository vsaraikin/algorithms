from collections import defaultdict


class Solution:
    def groupAnagrams(self, strs):
        anagram_map = defaultdict(list)

        for word in strs:
            sorted_word = ''.join(sorted(word))
            anagram_map[sorted_word].append(word)

        return list(anagram_map.values())


s = Solution()

# order does not matter, so errors are ok
assert s.groupAnagrams(["eat", "tea", "tan", "ate", "nat", "bat"]) == [["bat"], ["nat", "tan"], ["ate", "eat", "tea"]]
assert s.groupAnagrams([""]) == [[""]]
assert s.groupAnagrams(["a"]) == [["a"]]
assert s.groupAnagrams(["ddddddddddg", "dgggggggggg"]) == [["dgggggggggg"], ["ddddddddddg"]]
