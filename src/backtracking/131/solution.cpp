#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

class Solution {
public:
	std::vector<std::vector<std::string>> partition(std::string s) {
		std::vector<std::string> path;
		dfs(0, s, path);
		return res;
	}

private:
	std::vector<std::vector<std::string>> res;

	void dfs(int start, const std::string& s, std::vector<std::string>& path) {
		if (start == (int)s.size()) {            // goal: вся строка разрезана
			res.push_back(path);
			return;
		}
		for (int end = start; end < (int)s.size(); ++end) {
			if (!isPalindrome(s, start, end)) {  // constraint: кусок — палиндром
				continue;
			}
			path.push_back(s.substr(start, end - start + 1));  // choose
			dfs(end + 1, s, path);                             // recurse
			path.pop_back();                                   // un-choose
		}
	}

	bool isPalindrome(const std::string& s, int l, int r) {
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

static std::vector<std::vector<std::string>> norm(
    std::vector<std::vector<std::string>> v) {
	std::sort(v.begin(), v.end());
	return v;
}

int main() {
	Solution s;

	// классика: "aab" → ["a","a","b"] и ["aa","b"]
	assert(norm(s.partition("aab")) ==
	       (std::vector<std::vector<std::string>>{
	           {"a", "a", "b"}, {"aa", "b"}}));

	// один символ → одно разбиение
	{
		Solution s2;
		assert(norm(s2.partition("a")) ==
		       (std::vector<std::vector<std::string>>{{"a"}}));
	}

	// целиком палиндром "aba": ["a","b","a"] и ["aba"]
	{
		Solution s3;
		assert(norm(s3.partition("aba")) ==
		       (std::vector<std::vector<std::string>>{
		           {"a", "b", "a"}, {"aba"}}));
	}

	// все одинаковые "aaa" → 4 разбиения (число разрезов = 2^(n-1))
	{
		Solution s4;
		assert(s4.partition("aaa").size() == 4);
	}

	// нет длинных палиндромов "abc" → только по одному символу
	{
		Solution s5;
		assert(norm(s5.partition("abc")) ==
		       (std::vector<std::vector<std::string>>{{"a", "b", "c"}}));
	}

	return 0;
}
