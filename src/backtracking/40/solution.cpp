#include <algorithm>
#include <cassert>
#include <vector>

class Solution {
public:
	std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
		std::sort(candidates.begin(), candidates.end());
		this->candidates = candidates;
		dfs(0, target, {});
		return res;
	}

private:
	std::vector<int> candidates;
	std::vector<std::vector<int>> res;
	void dfs(int s, int target, std::vector<int> path) {
		if (target < 0) {
			return;
		}

		if (target == 0) {
			res.push_back(path);
			return;
		}

		for (size_t i = s; i < candidates.size(); ++i) {
			if (i > (size_t)s && candidates[i] == candidates[i - 1]) {
				continue;
			}

			path.push_back(candidates[i]);
			dfs(i + 1, target - candidates[i], path);
			path.pop_back();
		}
	}
};

// Сравниваем как множество множеств: сортируем каждую комбинацию и список.
static std::vector<std::vector<int>> norm(std::vector<std::vector<int>> v) {
	for (auto& row : v) std::sort(row.begin(), row.end());
	std::sort(v.begin(), v.end());
	return v;
}

int main() {
	Solution s;

	// классика с дублями: каждое число используется максимум один раз
	{
		std::vector<int> c{10, 1, 2, 7, 6, 1, 5};
		assert(norm(s.combinationSum2(c, 8)) ==
		       (std::vector<std::vector<int>>{
		           {1, 1, 6}, {1, 2, 5}, {1, 7}, {2, 6}}));
	}

	// много одинаковых чисел
	{
		Solution s2;
		std::vector<int> c{2, 5, 2, 1, 2};
		assert(norm(s2.combinationSum2(c, 5)) ==
		       (std::vector<std::vector<int>>{{1, 2, 2}, {5}}));
	}

	// нет решения
	{
		Solution s3;
		std::vector<int> c{2, 4, 6};
		assert(s3.combinationSum2(c, 3).empty());
	}

	// все одинаковые — ровно одна комбинация
	{
		Solution s4;
		std::vector<int> c{1, 1, 1, 1};
		assert(norm(s4.combinationSum2(c, 2)) ==
		       (std::vector<std::vector<int>>{{1, 1}}));
	}

	return 0;
}
