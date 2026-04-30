#include <unordered_set>
#include <vector>

class Solution {
public:
    bool containsDuplicate(std::vector<int>& nums) {
        std::unordered_set<int> indexer;
        for (auto const& i: nums) {
            if (indexer.count(i)) {
                return true;
            }
            indexer.insert(i);
        }
        return false;
    }

    // bool containsDuplicate(std::vector<int>& nums) {
    //     return std::unordered_set<int>(nums.begin(), nums.end()).size() < nums.size();
    // }

};