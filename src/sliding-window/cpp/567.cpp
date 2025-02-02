#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.size() > s2.size()) {
            return false;
        }
        vector<int> count1(26,0), count2(26,0);
        for (char c: s1) {
            count1[c - 'a']++;
        }
        for (int i = 0; i < s2.size(); i++) {
            count2[s2[i] - 'a']++;
            if (i >= s1.size()) {
                count2[s2[i-s1.size()] - 'a']--;
            }
            if (count1 == count2) {
                return true;
            }
        }
        return false;
    }
};


int main() {
    Solution solution;

    string s1_1 = "ab";
    string s2_1 = "eidbaooo";
    assert(solution.checkInclusion(s1_1, s2_1) == true);

    string s1_2 = "ab";
    string s2_2 = "eidboaoo";
    assert(solution.checkInclusion(s1_2, s2_2) == false);

    string s1_3 = "abc";
    string s2_3 = "abc";
    assert(solution.checkInclusion(s1_3, s2_3) == true);

    string s1_4 = "xyz";
    string s2_4 = "zzxyzyxzz";
    assert(solution.checkInclusion(s1_4, s2_4) == true);

    string s1_5 = "aab";
    string s2_5 = "eidboaoo";
    assert(solution.checkInclusion(s1_5, s2_5) == false);

    string s1_6 = "";
    string s2_6 = "anystring";
    assert(solution.checkInclusion(s1_6, s2_6) == true);

    string s1_7 = "a";
    string s2_7 = "";
    assert(solution.checkInclusion(s1_7, s2_7) == false);

    string s1_8 = "abcd";
    string s2_8 = "abc";
    assert(solution.checkInclusion(s1_8, s2_8) == false);

    string s1_9 = "aabc";
    string s2_9 = "cbaebabacd";
    assert(solution.checkInclusion(s1_9, s2_9) == true);

    string s1_10 = "aaa";
    string s2_10 = "aaabaaa";
    assert(solution.checkInclusion(s1_10, s2_10) == true);

    cout << "All test cases passed!" << endl;

    return 0;
}