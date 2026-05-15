#include <cassert>
#include <string>
#include <vector>

class Solution {
  public:
	bool checkInclusion(std::string s1, std::string s2) {
		std::vector<int> c1(26, 0), c2(26, 0);
		for (int i = 0; i < s1.size(); ++i) {
			c1[s1[i] - 'a']++;
		}

		int l = 0;
		for (int r = 0 ; r < s2.size(); ++r) {
			c2[s2[r] - 'a']++;
			if (r < s1.size() - 1) {
				continue;
			}
			if (c1 == c2) {
				return true;
			}
			c2[s2[l] - 'a']--;
			++l;
			
		}
		return false;
	}
};

int main() {
	Solution s;

	assert(s.checkInclusion("ab", "eidbaooo") == true);
	assert(s.checkInclusion("ab", "eidboaoo") == false);
	assert(s.checkInclusion("abc", "bbbca") == true);
	assert(s.checkInclusion("hello", "ooolleoooleh") == false);
	assert(s.checkInclusion("a", "a") == true);
	assert(s.checkInclusion("a", "b") == false);
	assert(s.checkInclusion("abc", "ab") == false);
	assert(s.checkInclusion("adc", "dcda") == true);
	assert(s.checkInclusion("ab", "ab") == true);
	assert(s.checkInclusion("ab", "ba") == true);
	assert(s.checkInclusion("abc", "ccccbbbbaaaa") == false);

	return 0;
}
