#include <algorithm>
#include <cassert>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        visited.assign(nums.size(), false);
        dfs(nums, {});
        return res;
    }
private:
    std::vector<std::vector<int>> res;
    std::vector<bool> visited;

    void dfs(std::vector<int>& nums, std::vector<int> path) {
        if (nums.size() == path.size()) {
            res.push_back(path);
            return;
        }

        for (int i = 0; i < (int)nums.size(); ++i) {
            if (visited[i]) {
                continue;
            }
            visited[i] = true;
            path.push_back(nums[i]);
            dfs(nums, path);
            visited[i] = false;
            path.pop_back();
        }
    }
};

// Порядок обхода фиксирован, но сравним как множество перестановок.
static std::vector<std::vector<int>> norm(std::vector<std::vector<int>> v) {
	std::sort(v.begin(), v.end());
	return v;
}

int main() {
	Solution s;

	// n = 3 → 3! = 6 перестановок
	{
		std::vector<int> nums{1, 2, 3};
		assert(norm(s.permute(nums)) ==
		       (std::vector<std::vector<int>>{{1, 2, 3}, {1, 3, 2}, {2, 1, 3},
		                                      {2, 3, 1}, {3, 1, 2}, {3, 2, 1}}));
	}

	// n = 1 → одна перестановка
	{
		Solution s2;
		std::vector<int> nums{7};
		assert(norm(s2.permute(nums)) == (std::vector<std::vector<int>>{{7}}));
	}

	// n = 2
	{
		Solution s3;
		std::vector<int> nums{0, 1};
		assert(norm(s3.permute(nums)) ==
		       (std::vector<std::vector<int>>{{0, 1}, {1, 0}}));
	}

	// количество = n! для n = 4
	{
		Solution s4;
		std::vector<int> nums{1, 2, 3, 4};
		assert(s4.permute(nums).size() == 24);
	}

	return 0;
}
