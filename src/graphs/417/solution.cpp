#include <algorithm>
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

class Solution {
public:
	std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>> &h) {
		const int C = h.size();
		const int R = h[0].size();

		std::vector<std::vector<int>> res;

		std::vector<std::vector<bool>> pac(C, std::vector<bool>(R, false));
		std::vector<std::vector<bool>> atl(C, std::vector<bool>(R, false));

		for (int i = 0; i < C; ++i) {
			dfs(i, 0, pac, h);
			dfs(i, R - 1, atl, h);
		}

		for (int j = 0; j < R; ++j) {
			dfs(0, j, pac, h);
			dfs(C - 1, j, atl, h);
		}

		for (int i = 0; i < C; ++i) {
			for (int j = 0; j < R; ++j) {
				if (pac[i][j] && atl[i][j]) {
					res.push_back({i, j});
				}
			}
		}

		return res;
	}

private:
	void dfs(int i, int j, std::vector<std::vector<bool>> &ocean, std::vector<std::vector<int>> &heights) {
		std::vector<std::pair<int, int>> arr = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};
		ocean[i][j] = true;
		for (auto coor: arr) {
			int ri = coor.first + i;
			int rj = coor.second + j;
			if (
				0 <= ri && ri < (int)heights.size() &&
				0 <= rj && rj < (int)heights[0].size() &&
				!ocean[ri][rj] &&
				heights[i][j] <= heights[ri][rj]
			) {
				dfs(ri, rj, ocean, heights);
			}
		}
	}
};

static std::vector<std::vector<int>> norm(std::vector<std::vector<int>> v) {
	std::sort(v.begin(), v.end());
	return v;
}

int main() {
	Solution s;

	{
		std::vector<std::vector<int>> h{{1, 2, 2, 3, 5},
										{3, 2, 3, 4, 4},
										{2, 4, 5, 3, 1},
										{6, 7, 1, 4, 5},
										{5, 1, 1, 2, 4}};
		auto expected =
			norm({{0, 4}, {1, 3}, {1, 4}, {2, 2}, {3, 0}, {3, 1}, {4, 0}});
		assert(norm(s.pacificAtlantic(h)) == expected);
	}

	{
		std::vector<std::vector<int>> h{{1}};
		assert(norm(s.pacificAtlantic(h)) ==
			   (std::vector<std::vector<int>>{{0, 0}}));
	}

	{
		std::vector<std::vector<int>> h{{1, 1}, {1, 1}};
		assert(s.pacificAtlantic(h).size() == 4);
	}

	{
		std::vector<std::vector<int>> h{{1, 2, 3}};
		assert(s.pacificAtlantic(h).size() == 3);
	}

	return 0;
}
