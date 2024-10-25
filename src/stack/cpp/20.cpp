#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <stack>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> brackets;
        for (char ch : s) {
            switch (ch) {
                case '(':
                case '{':
                case '[':
                    brackets.push(ch);
                    break;
                case ')':
                    if (brackets.empty() || brackets.top() != '(') return false;
                    brackets.pop();
                    break;
                case '}':
                    if (brackets.empty() || brackets.top() != '{') return false;
                    brackets.pop();
                    break;
                case ']':
                    if (brackets.empty() || brackets.top() != '[') return false;
                    brackets.pop();
                    break;
            }
        }
        return brackets.empty();
    }
};


int main() {
    Solution solution;

    // Test Case 1
    string test1 = "()";
    assert(solution.isValid(test1) == true && "Test 1 Failed");

    // Test Case 2
    string test2 = "()[]{}";
    assert(solution.isValid(test2) == true && "Test 2 Failed");

    // Test Case 3
    string test3 = "(]";
    assert(solution.isValid(test3) == false && "Test 3 Failed");

    // Test Case 4
    string test4 = "([])";
    assert(solution.isValid(test4) == true && "Test 4 Failed");

    cout << "All tests passed successfully!" << endl;
    return 0;
}