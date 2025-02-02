#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> num_set(nums.begin(), nums.end());
        int maxStreak = 0;

        for (int num : num_set) {
            if (num_set.find(num - 1) == num_set.end()) {
                int currentNum = num;
                int currentStreak = 1;

                while (num_set.find(currentNum + 1) != num_set.end()) {
                    currentNum++;
                    currentStreak++;
                }

                maxStreak = max(maxStreak, currentStreak);
            }
        }

        return maxStreak;
    }
};
int main() {
    Solution solution;

    vector<int> test1 = {};
    assert(solution.longestConsecutive(test1) == 0 && "Test 1 Failed");

    vector<int> test2 = {1};
    assert(solution.longestConsecutive(test2) == 1 && "Test 2 Failed");

    vector<int> test3 = {100, 4, 200, 1, 3, 2};
    assert(solution.longestConsecutive(test3) == 4 && "Test 3 Failed");

    vector<int> test4 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    assert(solution.longestConsecutive(test4) == 9 && "Test 4 Failed");

    vector<int> test5 = {1, 2, 3, 4, 5};
    assert(solution.longestConsecutive(test5) == 5 && "Test 5 Failed");

    vector<int> test6 = {5, 10, 15, 20};
    assert(solution.longestConsecutive(test6) == 1 && "Test 6 Failed");

    vector<int> test7 = {-3, -2, -1, 0, 1};
    assert(solution.longestConsecutive(test7) == 5 && "Test 7 Failed");

    vector<int> test8 = {1, 2, 2, 3, 3, 4, 5};
    assert(solution.longestConsecutive(test8) == 5 && "Test 8 Failed");

    vector<int> test9 = {1000000000, 1000000001, 1000000002};
    assert(solution.longestConsecutive(test9) == 3 && "Test 9 Failed");

    vector<int> test10 = {-5, -4, -3, 1, 2, 3, 4};
    assert(solution.longestConsecutive(test10) == 4 && "Test 10 Failed");

    cout << "All tests passed successfully!" << endl;
    return 0;
}