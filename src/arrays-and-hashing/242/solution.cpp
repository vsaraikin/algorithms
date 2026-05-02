#include <string>
#include <unordered_map>

class Solution {
public:
    bool isAnagram(std::string s, std::string t) {
        std::unordered_map<char, int> s_counter;
        std::unordered_map<char, int> t_counter;

        for (const auto& i: s) {
            s_counter[i]++;
        }


        for (const auto& i: t) {
            t_counter[i]++;
        }

        return s_counter == t_counter;

    }
};