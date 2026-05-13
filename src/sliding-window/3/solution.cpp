#include <algorithm>
#include <cassert>
#include <string>
#include <unordered_set>

class Solution {
  public:
	int lengthOfLongestSubstring(std::string s) {
		std::unordered_set<char> window;
		int l = 0, best = 0;
		for (int r = 0; r < (int)s.size(); r++) {
			while (window.count(s[r])) {
				window.erase(s[l]);
				l++;
			}
			window.insert(s[r]);
			best = std::max(best, r - l + 1);
		}
		return best;
	}
};

int main() {
	Solution s;

	assert(s.lengthOfLongestSubstring("abcabcbb") == 3);
	assert(s.lengthOfLongestSubstring("bbbbb") == 1);
	assert(s.lengthOfLongestSubstring("pwwkew") == 3);
	assert(s.lengthOfLongestSubstring("") == 0);
	assert(s.lengthOfLongestSubstring(" ") == 1);
	assert(s.lengthOfLongestSubstring("au") == 2);
	assert(s.lengthOfLongestSubstring("dvdf") == 3);
	assert(s.lengthOfLongestSubstring("abba") == 2);
	assert(s.lengthOfLongestSubstring("tmmzuxt") == 5);
	assert(s.lengthOfLongestSubstring("abcdefg") == 7);

	return 0;
}
