#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cassert>

class Solution {
public:
    // n log n
    // std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
    //     std::unordered_map<int, int> counter;
    //     for (const auto& i: nums) {
    //         counter[i]++;
    //     }
        
    //     std::vector<std::pair<int, int>> pairs(counter.begin(), counter.end());
    //     std::sort(pairs.begin(), pairs.end(), [](auto &a, auto &b) {
    //         return a.second > b.second;
    //     });
    //     std::vector<int> res;
    //     for (int i = 0; i < k; ++i) {
    //         res.push_back(pairs[i].first);
    //     }
    //     return res;
    // }

    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> counter;
        for (const int& i: nums) {
            counter[i]++;
        }
        
        std::vector<std::vector<int>> buckets(nums.size() + 1);
        for (auto& [value, freq]: counter) {
            buckets[freq].push_back(value);
        }
        std::vector<int> res;
        for (int i = nums.size(); i >= 0 && res.size() < k; --i) {
            for (int val: buckets[i]) {
                res.push_back(val);
                if (res.size() == k) {
                    break;
                }
            }
        }

        return res;
    }
};

static std::vector<int> sorted_copy(std::vector<int> v) {
    std::sort(v.begin(), v.end());
    return v;
}

int main() {
    Solution s;

    std::vector<int> input1 = {1, 1, 1, 2, 2, 3};
    assert(sorted_copy(s.topKFrequent(input1, 2)) == (std::vector<int>{1, 2}));

    std::vector<int> input2 = {1};
    assert(sorted_copy(s.topKFrequent(input2, 1)) == (std::vector<int>{1}));

    std::vector<int> input3 = {1, 2};
    assert(sorted_copy(s.topKFrequent(input3, 2)) == (std::vector<int>{1, 2}));

    std::vector<int> input4 = {4, 4, 4, 5, 5, 6};
    assert(sorted_copy(s.topKFrequent(input4, 1)) == (std::vector<int>{4}));

    std::vector<int> input5 = {-1, -1, 2, 2, 3};
    assert(sorted_copy(s.topKFrequent(input5, 2)) == (std::vector<int>{-1, 2}));

    std::vector<int> input6 = {7, 7, 7, 7, 8, 8, 9};
    assert(sorted_copy(s.topKFrequent(input6, 3)) == (std::vector<int>{7, 8, 9}));

    return 0;
}
