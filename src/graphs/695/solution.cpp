#include <algorithm>
#include <vector>

class Solution {
  public:
	int maxAreaOfIsland(std::vector<std::vector<int>> &grid) {
		int best = 0;
		for (int i = 0; i < grid.size(); ++i) {
			for (int j = 0; j < grid[0].size(); ++j) {
				best = std::max(best, dfs(i, j, grid));
			}
		}
		return best;
	}

  private:
	int dfs(int i, int j, std::vector<std::vector<int>> &grid) {
		if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == 0) {
			return 0;
		}
		grid[i][j] = 0;
		return 1 + dfs(i + 1, j, grid) + dfs(i - 1, j, grid) +
			   dfs(i, j + 1, grid) + dfs(i, j - 1, grid);
	}
};
