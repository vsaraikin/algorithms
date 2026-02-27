#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    void reverseString(vector<char>& s) {
        for (int i = 0; i < s.size() / 2; i++) {
            swap(s[i], s[s.size() - 1 - i]);
        }
    }
};


int main() {
    Solution solution;

    // Test case 1: Normal case
    std::vector<char> input1 = {'h', 'e', 'l', 'l', 'o'};
    std::vector<char> expected1 = {'o', 'l', 'l', 'e', 'h'};
    solution.reverseString(input1);
    assert(input1 == expected1);

    // Test case 2: Single character
    std::vector<char> input2 = {'a'};
    std::vector<char> expected2 = {'a'};
    solution.reverseString(input2);
    assert(input2 == expected2);

    // Test case 3: Empty vector
    std::vector<char> input3 = {};
    std::vector<char> expected3 = {};
    solution.reverseString(input3);
    assert(input3 == expected3);

    // Test case 4: Even number of characters
    std::vector<char> input4 = {'a', 'b', 'c', 'd'};
    std::vector<char> expected4 = {'d', 'c', 'b', 'a'};
    solution.reverseString(input4);
    assert(input4 == expected4);

    // Test case 5: Palindrome
    std::vector<char> input5 = {'m', 'a', 'd', 'a', 'm'};
    std::vector<char> expected5 = {'m', 'a', 'd', 'a', 'm'};
    solution.reverseString(input5);
    assert(input5 == expected5);

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}