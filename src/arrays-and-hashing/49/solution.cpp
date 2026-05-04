#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cassert>

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> counter;
        for (const auto &s: strs) {
            std::string key = s;
            std::sort(key.begin(), key.end());
            counter[key].push_back(s);
        }

        std::vector<std::vector<std::string>> result;
        result.reserve(counter.size());
        for (auto& [_, group] : counter) {
            result.push_back(std::move(group));
        }
        return result;
    }
};

static std::vector<std::vector<std::string>> normalize(
    std::vector<std::vector<std::string>> groups) {
    for (auto& g : groups) std::sort(g.begin(), g.end());
    std::sort(groups.begin(), groups.end());
    return groups;
}

int main() {
    Solution s;

    std::vector<std::string> input1 = {"eat","tea","tan","ate","nat","bat"};
    std::vector<std::vector<std::string>> expected1 = {
        {"ate","eat","tea"}, {"bat"}, {"nat","tan"}
    };
    assert(normalize(s.groupAnagrams(input1)) == normalize(expected1));

    std::vector<std::string> input2 = {""};
    std::vector<std::vector<std::string>> expected2 = {{""}};
    assert(normalize(s.groupAnagrams(input2)) == normalize(expected2));

    std::vector<std::string> input3 = {"a"};
    std::vector<std::vector<std::string>> expected3 = {{"a"}};
    assert(normalize(s.groupAnagrams(input3)) == normalize(expected3));

    std::vector<std::string> input4 = {"abc","bca","cab","xyz","zyx"};
    std::vector<std::vector<std::string>> expected4 = {
        {"abc","bca","cab"}, {"xyz","zyx"}
    };
    assert(normalize(s.groupAnagrams(input4)) == normalize(expected4));

    std::vector<std::string> input5 = {};
    std::vector<std::vector<std::string>> expected5 = {};
    assert(normalize(s.groupAnagrams(input5)) == normalize(expected5));

    return 0;
}