#include <string>
#include <utility>
#include <vector>

class Solution {
public:
	// O(n^2) time, O(1) space
	std::string longestPalindrome(std::string s) {
		const int n = s.size();
		if (n == 0) {
			return "";
		}

		int start = 0;
		int bestLen = 1;

		auto expand = [&](int l, int r) -> std::pair<int, int> {
			while (l >= 0 && r < n && s[l] == s[r]) {
				--l;
				++r;
			}
			return {l + 1, r - 1};
		};

		for (int i = 0; i < n; ++i) {
			auto [l1, r1] = expand(i, i);
			if (r1 - l1 + 1 > bestLen) {
				bestLen = r1 - l1 + 1;
				start = l1;
			}

			auto [l2, r2] = expand(i, i + 1);
			if (r2 - l2 + 1 > bestLen) {
				bestLen = r2 - l2 + 1;
				start = l2;
			}
		}

		return s.substr(start, bestLen);
	}

	// O(n^2) time, O(n^2) space
	std::string longestPalindromeDP(std::string s) {
		const int n = s.size();
		if (n == 0) {
			return "";
		}

		std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
		int start = 0;
		int bestLen = 1;

		for (int i = n - 1; i >= 0; --i) {
			for (int j = i; j < n; ++j) {
				if (s[i] == s[j] && (j - i < 3 || dp[i + 1][j - 1])) {
					dp[i][j] = true;
					if (j - i + 1 > bestLen) {
						bestLen = j - i + 1;
						start = i;
					}
				}
			}
		}

		return s.substr(start, bestLen);
	}

	// O(n^3) time, O(n) space
	std::string longestPalindromeBrute(std::string s) {
		std::string res;
		for (int i = 0; i < (int)s.size(); ++i) {
			for (int j = i; j < (int)s.size(); ++j) {
				std::string tmp = s.substr(i, j - i + 1);
				if (isPalindrome(tmp) && tmp.size() > res.size()) {
					res = tmp;
				}
			}
		}
		return res;
	}

private:
	bool isPalindrome(const std::string& s) {
		int l = 0;
		int r = s.size() - 1;
		while (l < r) {
			if (s[l] != s[r]) {
				return false;
			}
			++l;
			--r;
		}
		return true;
	}
};
