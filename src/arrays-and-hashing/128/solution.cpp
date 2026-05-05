#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <vector>

class Solution {
public:
//   int longestConsecutive(std::vector<int> &nums) {
//     if (nums.empty()) {
//       return 0;
//     }

//     std::sort(nums.begin(), nums.end());
//     int max_l = 1;
//     int cur = 1;
//     for (int i = 1; i < nums.size(); ++i) {
//       if (nums[i] - nums[i - 1] == 1) {
//         ++cur;
//       } else if (nums[i] == nums[i - 1]) {
//         continue;
//       } else {
//         cur = 1;
//       }
//       max_l = std::max(max_l, cur);
//     }
//     return max_l;
//   }
  int longestConsecutive(std::vector<int> &nums) {
    if (nums.empty()) {
      return 0;
    }
    std::unordered_set<int> set(nums.begin(), nums.end());
    int b = 0;
    for (int x: set) {
        if (set.count(x-1)) {
            continue; // not a start WHY?
        }

        int l = 1;
        while (set.count(x + l)) {
            ++l;
        }
        b = std::max(b, l);
    }
    return b;

}

};

int main() {
  Solution s;

  std::vector<int> input1 = {100, 4, 200, 1, 3, 2};
  assert(s.longestConsecutive(input1) == 4); // 1,2,3,4

  std::vector<int> input2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
  assert(s.longestConsecutive(input2) == 9); // 0..8

  std::vector<int> input3 = {};
  assert(s.longestConsecutive(input3) == 0);

  std::vector<int> input4 = {1};
  assert(s.longestConsecutive(input4) == 1);

  std::vector<int> input5 = {1, 1, 1, 1};
  assert(s.longestConsecutive(input5) == 1); // duplicates count as one

  std::vector<int> input6 = {-3, -2, -1, 0, 1};
  assert(s.longestConsecutive(input6) == 5); // negatives work too

  std::vector<int> input7 = {10, 5, 12, 3, 55, 30, 4, 11, 2};
  assert(s.longestConsecutive(input7) == 4); // 2,3,4,5 and 10,11,12 → 4

  return 0;
}
