#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>

using namespace std;


class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0, maxLength = 0;
        unordered_map<char, int> charIndex;
        for (int right = 0; right < s.size(); right++) {
            char currentChar = s[right];
            if (charIndex.contains(currentChar) && charIndex[currentChar] >= left) {
                left = charIndex[currentChar] + 1;
            }
            charIndex[currentChar] = right;
            maxLength = max(maxLength, right - left + 1);
        }
        return maxLength;
    }
};

int main() {
    Solution solution;
    // Test case 1: General case with repeating characters
    string s1 = "abcabcbb";
    int expected1 = 3;
    assert(solution.lengthOfLongestSubstring(s1) == expected1);

    // Test case 2: All unique characters
    string s2 = "abcdef";
    int expected2 = 6;
    assert(solution.lengthOfLongestSubstring(s2) == expected2);

    // Test case 3: Single character string
    string s3 = "a";
    int expected3 = 1;
    assert(solution.lengthOfLongestSubstring(s3) == expected3);

    // Test case 4: Empty string
    string s4 = "";
    int expected4 = 0;
    assert(solution.lengthOfLongestSubstring(s4) == expected4);

    // Test case 5: String with all identical characters
    string s5 = "aaaaaa";
    int expected5 = 1;
    assert(solution.lengthOfLongestSubstring(s5) == expected5);

    // Test case 6: String with mixed characters
    string s6 = "pwwkew";
    int expected6 = 3;
    assert(solution.lengthOfLongestSubstring(s6) == expected6);

    cout << "All test cases passed!" << endl;
    return 0;
}