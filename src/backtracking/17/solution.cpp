#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

class Solution {
public:
    std::vector<std::string> letterCombinations(std::string digits) {
        ans.clear();  // на случай повторного вызова на одном объекте
        if (digits.empty()) {
            return {};
        }

        std::string path;
        dfs(digits, 0, path);
        return ans;
    }
private:
    const std::vector<std::string> mapping{"", "",    "abc",  "def", "ghi",
                                      "jkl", "mno", "pqrs", "tuv", "wxyz"};
    std::vector<std::string> ans;

    void dfs(const std::string& digits, int i, std::string& path) {    
        if (i == digits.size()) {
            ans.push_back(path);
            return;
        }

        for (const char letter: mapping[digits[i] - '0']) {
            path.push_back(letter);
            dfs(digits, i + 1, path);
            path.pop_back();
        }
    }
};

// Порядок выдачи backtracking фиксирован (DFS), но сравним как множество,
// чтобы тест не зависел от него.
static std::vector<std::string> sorted(std::vector<std::string> v) {
	std::sort(v.begin(), v.end());
	return v;
}

int main() {
	Solution s;

	// пустой ввод → пусто
	assert(s.letterCombinations("") == (std::vector<std::string>{}));

	// одна цифра
	assert(sorted(s.letterCombinations("2")) ==
	       (std::vector<std::string>{"a", "b", "c"}));

	// две цифры → 3 * 3 = 9
	assert(sorted(s.letterCombinations("23")) ==
	       (std::vector<std::string>{"ad", "ae", "af", "bd", "be", "bf", "cd",
	                                 "ce", "cf"}));

	// цифра с 4 буквами (7 = pqrs)
	assert(sorted(s.letterCombinations("7")) ==
	       (std::vector<std::string>{"p", "q", "r", "s"}));

	// 9 = wxyz, 4 буквы
	assert(s.letterCombinations("9").size() == 4);

	// две "толстые" цифры 7 и 9 → 4 * 4 = 16
	assert(s.letterCombinations("79").size() == 16);

	// три цифры → 3 * 3 * 3 = 27
	assert(s.letterCombinations("234").size() == 27);

	// проверим конкретную комбинацию присутствует
	{
		auto r = s.letterCombinations("23");
		assert(std::find(r.begin(), r.end(), "be") != r.end());
		assert(std::find(r.begin(), r.end(), "cf") != r.end());
	}

	return 0;
}
