#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

class Solution {
public:
	std::vector<std::string> generateParenthesis(int n) {
		res.clear();  // на случай повторного вызова на одном объекте
		dfs(0, 0, n, "");
		return res;
	}

private:
	std::vector<std::string> res;
	void dfs(int l, int r, int n, std::string path) {
		if (l > n || r > n || l < r) {
			return;
		}

		if (l == n && r == n) {
			res.push_back(path);
			return;
		}

		dfs(l + 1, r, n, path + '(');
		dfs(l, r + 1, n, path + ')');
	}
};

static std::vector<std::string> sorted(std::vector<std::string> v) {
	std::sort(v.begin(), v.end());
	return v;
}

int main() {
	Solution s;

	// n = 0 → одна пустая строка
	assert(s.generateParenthesis(0) == (std::vector<std::string>{""}));

	// n = 1
	assert(sorted(s.generateParenthesis(1)) == (std::vector<std::string>{"()"}));

	// n = 2 → 2 варианта
	assert(sorted(s.generateParenthesis(2)) ==
	       (std::vector<std::string>{"(())", "()()"}));

	// n = 3 → Каталан C(3) = 5
	assert(sorted(s.generateParenthesis(3)) ==
	       (std::vector<std::string>{"((()))", "(()())", "(())()", "()(())",
	                                 "()()()"}));

	// количество результатов = числа Каталана: 1, 1, 2, 5, 14, 42
	assert(s.generateParenthesis(4).size() == 14);
	assert(s.generateParenthesis(5).size() == 42);

	// каждая строка должна быть сбалансирована
	for (const auto& str : s.generateParenthesis(4)) {
		int bal = 0;
		for (char c : str) {
			bal += (c == '(') ? 1 : -1;
			assert(bal >= 0);  // не закрываемся раньше, чем открылись
		}
		assert(bal == 0);       // в конце всё закрыто
	}

	return 0;
}
