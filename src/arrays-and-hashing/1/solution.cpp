#include <iostream>
#include <assert.h>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        return res;
    }
};

int main() {
    Solution s = Solution();
    vector<int> input1 = {2,7,11,15};
    vector<int> output1 = {0,1};
    assert(s.twoSum(input1, 9) == output1);
    return 0;
}