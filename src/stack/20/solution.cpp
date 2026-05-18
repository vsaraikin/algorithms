#include <cassert>
#include <stack>
#include <string>
#include <unordered_map>

class Solution {
  public:
	bool isValid(std::string s) {
		std::unordered_map<char, char> index = {
			{'(', ')'},
			{'{', '}'},
			{'[', ']'}
		};
		std::stack<char> st;
		for (const auto& ch: s) {
			if (index.count(ch)) {
				st.push(ch);
			} else {
				if (st.empty()) {
					return false;
				}
				char el = st.top();
				st.pop();
				if (index[el] == ch) {
					continue;
				}
				return false;
				
			}
		}
		return st.empty();
	}
};

int main() {
	Solution s;

	assert(s.isValid("()") == true);
	assert(s.isValid("()[]{}") == true);
	assert(s.isValid("(]") == false);
	assert(s.isValid("([)]") == false);
	assert(s.isValid("{[]}") == true);
	assert(s.isValid("") == true);
	assert(s.isValid("(") == false);
	assert(s.isValid(")") == false);
	assert(s.isValid("((((((") == false);
	assert(s.isValid("))))))") == false);
	assert(s.isValid("(())") == true);
	assert(s.isValid("({[]})") == true);
	assert(s.isValid("({[)]}") == false);

	return 0;
}
