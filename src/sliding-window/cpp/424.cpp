#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>

using namespace std;


// todo: re-solve later
class Solution {
public:
    int characterReplacement(string s, int k) {
        int left = 0, maxCount = 0, maxLength = 0;
        vector<int> count(26, 0);
        for (int right = 0; right < s.size(); right++) {
            count[s[right] - 'A']++;
            maxCount = max(maxCount, count[s[right] - 'A']);
            int windowSize = right - left + 1;
            if (windowSize - maxCount > k) {
                count[s[left] - 'A']--;
                left++;
            }
            maxLength = max(maxLength, right - left + 1);
        }
        return maxLength;
    }
};

int main() {
    Solution solution;

    string s1 = "ABAB";
    int k1 = 2;
    int expected1 = 4;
    assert(solution.characterReplacement(s1, k1) == expected1);

    string s2 = "AABABBA";
    int k2 = 1;
    int expected2 = 4;
    assert(solution.characterReplacement(s2, k2) == expected2);

    string s3 = "";
    int k3 = 0;
    int expected3 = 0;
    assert(solution.characterReplacement(s3, k3) == expected3);

    string s4 = "A";
    int k4 = 0;
    int expected4 = 1;
    assert(solution.characterReplacement(s4, k4) == expected4);

    string s5 = "AAAA";
    int k5 = 2;
    int expected5 = 4;
    assert(solution.characterReplacement(s5, k5) == expected5);
    cout << "All test cases passed!" << endl;

    return 0;
}