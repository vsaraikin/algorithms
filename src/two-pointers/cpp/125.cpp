#include <iostream>
#include <vector>
#include <cassert>
#include <string>


using namespace std;


class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            while (left < right && !isalnum(s[left])) {
                left++;
            }
            while (left < right && !isalnum(s[right])) {
                right--;
            }
            if (tolower(s[left]) != tolower(s[right])) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
//    bool isPalindrome(string s) {
//        s.erase(std::remove_if(s.begin(), s.end(), [](char c) {
//            return !isalnum(c);
//        }), s.end());
//
//        transform(s.begin(), s.end(), s.begin(), ::tolower);
//
//        string s1 = s;
//        std::reverse(s.begin(), s.end());
//        return s1 == s;
//    }
};

int main() {
    Solution solution;

    // Test 1: Normal palindrome
    string test1 = "A man, a plan, a canal: Panama";
    assert(solution.isPalindrome(test1) == true && "Test 1 Failed");

    // Test 2: Non-palindrome
    string test2 = "race a car";
    assert(solution.isPalindrome(test2) == false && "Test 2 Failed");

    // Test 3: Empty string
    string test3 = "";
    assert(solution.isPalindrome(test3) == true && "Test 3 Failed");

    // Test 4: Single character palindrome
    string test4 = "a";
    assert(solution.isPalindrome(test4) == true && "Test 4 Failed");

    // Test 5: Only non-alphanumeric characters (should be treated as palindrome)
    string test5 = ".,!";
    assert(solution.isPalindrome(test5) == true && "Test 5 Failed");

    // Test 6: Mixed case palindrome
    string test6 = "Able , was I saw eLba";
    assert(solution.isPalindrome(test6) == true && "Test 6 Failed");

    // Test 7: Numeric palindrome
    string test7 = "12321";
    assert(solution.isPalindrome(test7) == true && "Test 7 Failed");

    // Test 8: Numeric non-palindrome
    string test8 = "12345";
    assert(solution.isPalindrome(test8) == false && "Test 8 Failed");

    cout << "All tests passed successfully!" << endl;
    return 0;
}