#include <utility>
#include <vector>
#include <cassert>

class Solution {
public:
    void reverseString(std::vector<char>& s) {
        int l = 0, r = (int)s.size() - 1;
        while (l < r) {
            std::swap(s[l], s[r]);
            l++;
            r--;
        }
    }
};
int main() {
    Solution s;

    std::vector<char> v1 = {'h', 'e', 'l', 'l', 'o'};
    s.reverseString(v1);
    assert(v1 == (std::vector<char>{'o', 'l', 'l', 'e', 'h'}));

    std::vector<char> v2 = {'H', 'a', 'n', 'n', 'a', 'h'};
    s.reverseString(v2);
    assert(v2 == (std::vector<char>{'h', 'a', 'n', 'n', 'a', 'H'}));

    std::vector<char> v3 = {'a'};
    s.reverseString(v3);
    assert(v3 == (std::vector<char>{'a'}));

    std::vector<char> v4 = {'a', 'b'};
    s.reverseString(v4);
    assert(v4 == (std::vector<char>{'b', 'a'}));

    return 0;
}
