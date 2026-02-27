#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        unordered_map<string, vector<string>> anagrams;
        for (const string& s: strs) {
            string sorted = s;
            sort(sorted.begin(), sorted.end());
            anagrams[sorted].push_back(s);
        }
        for (const auto& p: anagrams) {
            result.push_back(p.second);
        }
        return result;
    };
};


int main() {
    Solution s;

    vector<string> test1 = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> result1 = s.groupAnagrams(test1);
    assert(result1.size() == 3 && "Test 1 Failed: Size mismatch");

    vector<string> test2 = {""};
    vector<vector<string>> result2 = s.groupAnagrams(test2);
    assert(result2.size() == 1 && result2[0].size() == 1 && result2[0][0] == "" && "Test 2 Failed");

    vector<string> test3 = {"a"};
    vector<vector<string>> result3 = s.groupAnagrams(test3);
    assert(result3.size() == 1 && result3[0].size() == 1 && result3[0][0] == "a" && "Test 3 Failed");

    cout << "All tests passed!" << endl;
}