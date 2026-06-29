#include <algorithm>
#include <cassert>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        std::vector<int> cur;
        dfs(0, nums, cur);
        return res;
    }

private:
    std::vector<std::vector<int>> res;
    void dfs(int i, std::vector<int>& nums, std::vector<int>& cur) {
        res.push_back(cur);
        for (int j = i; j < (int)nums.size(); ++j) {
            cur.push_back(nums[j]);
            dfs(j + 1, nums, cur);
            cur.pop_back();
        }
    }
};

// Сравниваем как множество подмножеств: сортируем каждое и список.
static std::vector<std::vector<int>> norm(std::vector<std::vector<int>> v) {
	for (auto& row : v) std::sort(row.begin(), row.end());
	std::sort(v.begin(), v.end());
	return v;
}

int main() {
	Solution s;

	// n = 3 → 2^3 = 8 подмножеств
	{
		std::vector<int> nums{1, 2, 3};
		assert(norm(s.subsets(nums)) ==
		       (std::vector<std::vector<int>>{{}, {1}, {1, 2}, {1, 2, 3},
		                                      {1, 3}, {2}, {2, 3}, {3}}));
	}

	// пустой ввод → одно пустое подмножество
	{
		Solution s2;
		std::vector<int> nums{};
		assert(norm(s2.subsets(nums)) == (std::vector<std::vector<int>>{{}}));
	}

	// n = 1
	{
		Solution s3;
		std::vector<int> nums{0};
		assert(norm(s3.subsets(nums)) == (std::vector<std::vector<int>>{{}, {0}}));
	}

	// количество = 2^n для n = 5
	{
		Solution s4;
		std::vector<int> nums{1, 2, 3, 4, 5};
		assert(s4.subsets(nums).size() == 32);
	}

	return 0;
}
