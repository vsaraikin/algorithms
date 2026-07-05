#include <algorithm>
#include <cassert>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        std::vector<int> cur;
        std::sort(nums.begin(), nums.end());
        dfs(0, nums, cur);
        return res;
    }

private:
    std::vector<std::vector<int>> res;
    void dfs(int start, std::vector<int>& nums, std::vector<int>& cur) {
        res.push_back(cur);
        for (int i = start; i < (int)nums.size(); ++i) {
            if (i > start && nums[i] == nums[i - 1]) {
                continue;
            }
            cur.push_back(nums[i]);
            dfs(i + 1, nums, cur);
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

	// классика с дублями: [1,2,2] → 6 уникальных подмножеств (а не 8)
	{
		std::vector<int> nums{1, 2, 2};
		assert(norm(s.subsetsWithDup(nums)) ==
		       (std::vector<std::vector<int>>{
		           {}, {1}, {1, 2}, {1, 2, 2}, {2}, {2, 2}}));
	}

	// все одинаковые: [2,2,2] → {}, {2}, {2,2}, {2,2,2}
	{
		Solution s2;
		std::vector<int> nums{2, 2, 2};
		assert(norm(s2.subsetsWithDup(nums)) ==
		       (std::vector<std::vector<int>>{{}, {2}, {2, 2}, {2, 2, 2}}));
	}

	// без дублей ведёт себя как обычный subsets: 2^n
	{
		Solution s3;
		std::vector<int> nums{1, 2, 3};
		assert(s3.subsetsWithDup(nums).size() == 8);
	}

	// пустой ввод → одно пустое подмножество
	{
		Solution s4;
		std::vector<int> nums{};
		assert(norm(s4.subsetsWithDup(nums)) ==
		       (std::vector<std::vector<int>>{{}}));
	}

	// вход неотсортирован — sort внутри должен всё выровнять
	{
		Solution s5;
		std::vector<int> nums{4, 4, 4, 1, 4};
		// значения: {1,4,4,4,4} → подмножества по числу четвёрок 0..4 с/без 1
		assert(s5.subsetsWithDup(nums).size() == 10);
	}

	return 0;
}
