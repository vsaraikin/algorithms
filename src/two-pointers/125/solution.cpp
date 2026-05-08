#include <cctype>
#include <string>
#include <cassert>

class Solution {
public:
    bool isPalindrome(std::string s) {
        int l = 0, r = s.size() - 1;
        while (l < r) {
            while (l < r &&!std::isalnum(s[l])) {
                l++;
            }
            while (l < r && !std::isalnum(s[r])) {
                r--;
            }
            
            if (std::tolower(s[l]) != std::tolower(s[r])) {
                return false;
            }
            l++;
            r--;
        }
        return true;
    }
};

int main() {
    Solution s;

    assert(s.isPalindrome("A man, a plan, a canal: Panama") == true);
    assert(s.isPalindrome("race a car") == false);
    assert(s.isPalindrome(" ") == true);
    assert(s.isPalindrome("") == true);
    assert(s.isPalindrome("a") == true);
    assert(s.isPalindrome("0P") == false);
    assert(s.isPalindrome("ab_a") == true);   // underscore is not alphanumeric
    assert(s.isPalindrome("Was it a car or a cat I saw?") == true);

    return 0;
}
