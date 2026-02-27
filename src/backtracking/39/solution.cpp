#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        dfs(0, target, {});
        return ans;
    }
private:
void dfs(int i, int target, vector<int> path) {

}
};


int main() {
    Solution s;
    vector<int> input = {2,3,6,7};
    auto res = s.combinationSum(input, 7);

    return 0;
}