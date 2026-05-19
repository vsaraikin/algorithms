#include <cassert>
#include <cstddef>
#include <stack>
#include <string>
#include <vector>

class Solution {
  public:
	int evalRPN(std::vector<std::string> &tokens) {
		std::stack<int> numbers;
		for (const std::string &t : tokens) {
			if (!(t == "+" || t == "-" || t == "*" || t == "/")) {
				int v = std::stoi(t);
				numbers.push(v);
			} else {
				int b = numbers.top();
				numbers.pop();
				int a = numbers.top();
				numbers.pop();

				int r;

				if (t == "+") {
					r = a + b;
				} else if (t == "/") {
					r = a / b;
				} else if (t == "*") {
					r = a * b;
				} else {
					r = a - b;
				}
				numbers.push(r);
			}
		}
		return numbers.top();
	}
};

int main() {
	Solution s;

	std::vector<std::string> input1 = {"2", "1", "+", "3", "*"};
	assert(s.evalRPN(input1) == 9);

	std::vector<std::string> input2 = {"4", "13", "5", "/", "+"};
	assert(s.evalRPN(input2) == 6);

	std::vector<std::string> input3 = {"10", "6", "9",	"3", "+", "-11", "*",
									   "/",	 "*", "17", "+", "5", "+"};
	assert(s.evalRPN(input3) == 22);

	std::vector<std::string> input4 = {"3"};
	assert(s.evalRPN(input4) == 3);

	std::vector<std::string> input5 = {"-3"};
	assert(s.evalRPN(input5) == -3);

	std::vector<std::string> input6 = {"4", "3", "-"};
	assert(s.evalRPN(input6) == 1);

	std::vector<std::string> input7 = {"7", "2", "/"};
	assert(s.evalRPN(input7) == 3);

	std::vector<std::string> input8 = {"-7", "2", "/"};
	assert(s.evalRPN(input8) == -3);

	return 0;
}
