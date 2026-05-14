#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

class Solution {
  public:
	int characterReplacement(std::string s, int k) {
		std::vector<int> freq(26, 0);
		int l = 0;
		int best = 0;
		int maxF = 0;
		for (int r = 0; r < (int)s.size(); ++r) {
			freq[s[r] - 'A']++;
			maxF = *std::max_element(freq.begin(), freq.end());
			if ((r - l + 1) - maxF > k) {
				freq[s[l] - 'A']--;
				++l;
			}
			best = std::max(best, r - l + 1);
		}
		return best;
	}
};

int main() {
	Solution s;

	assert(s.characterReplacement("ABAB", 2) == 4);
	assert(s.characterReplacement("AABABBA", 1) == 4);
	assert(s.characterReplacement("AAAA", 0) == 4);
	assert(s.characterReplacement("ABCDE", 1) == 2);
	assert(s.characterReplacement("A", 0) == 1);
	assert(s.characterReplacement("A", 5) == 1);
	assert(s.characterReplacement("ABAA", 0) == 2);
	assert(s.characterReplacement("BAAAB", 2) == 5);
	assert(s.characterReplacement("ABBB", 2) == 4);

	return 0;
}
