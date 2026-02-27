#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for (const auto &i: nums) {
            freq[i]++;
        }
        priority_queue<pair<int, int>> maxHeap;
        for (auto& [num, count] : freq) {
            maxHeap.push({count, num});
        }

        vector<int> result;
        for (int i = 0; i < k; i++) {
            result.push_back(maxHeap.top().second);
            maxHeap.pop();
        }
        return result;
    }
};


int main() {
    Solution solution;

    vector<int> test1 = {1, 1, 1, 2, 2, 3};
    vector<int> result1 = solution.topKFrequent(test1, 2);
    assert((find(result1.begin(), result1.end(), 1) != result1.end() &&
            find(result1.begin(), result1.end(), 2) != result1.end()) && "Test 1 Failed");

    vector<int> test2 = {1};
    vector<int> result2 = solution.topKFrequent(test2, 1);
    assert(result2.size() == 1 && result2[0] == 1 && "Test 2 Failed");

    cout << "All tests passed successfully!" << endl;    return 0;
}
