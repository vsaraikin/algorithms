#include <cassert>
#include <climits>
#include <string>
#include <unordered_map>

class Solution {
  public:
	std::string minWindow(std::string s, std::string t) {
		std::unordered_map<char, int> need, have, best;
		for (char c : t) {
			need[c]++;
		}
		int bestL = 0;
		int l = 0;
		int bestLen = INT_MAX;

		for (int r = 0; r < s.size(); ++r) {
			have[s[r]]++;

			while (covers(have, need)) {
				if (r - l + 1 < bestLen) {
					bestLen = r - l + 1;
					bestL = l;
				}
				have[s[l]]--;
				l++;
			}


		}

		return bestLen == INT_MAX ? "" : s.substr(bestL, bestLen);

	}

private:
	bool covers(const std::unordered_map<char, int>& have,
	            const std::unordered_map<char, int>& need) {
		for (const auto& [k, v] : need) {
			auto it = have.find(k);
			if (it == have.end() || it->second < v) return false;
		}
		return true;
	}
};

int main() {
	Solution s;

	assert(s.minWindow("ADOBECODEBANC", "ABC") == "BANC");
	assert(s.minWindow("a", "a") == "a");
	assert(s.minWindow("a", "aa") == "");
	assert(s.minWindow("a", "b") == "");
	assert(s.minWindow("ab", "b") == "b");
	assert(s.minWindow("aa", "aa") == "aa");	
	assert(s.minWindow("cabwefgewcwaefgcf", "cae") == "cwae");
	assert(s.minWindow("abc", "ac") == "abc");
	assert(s.minWindow("", "a") == "");
	assert(s.minWindow("aaflslflsldkalskaaa", "aaa") == "aaa");

	return 0;
}
