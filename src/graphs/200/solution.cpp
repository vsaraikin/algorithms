#include <cassert>
#include <vector>

class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        int count = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == '1') {
                    dfs(i, j, grid);
                    ++count;
                }
            }
        }

        return count;
    }

    void dfs(int i, int j, std::vector<std::vector<char>>& grid) {
        if (i < 0 || i >= grid.size() || j >= grid[0].size() || j < 0 || grid[i][j] == '0') {
            return;
        }

        grid[i][j] = '0';
        dfs(i - 1, j, grid);
        dfs(i + 1, j, grid);
        dfs(i, j - 1, grid);
        dfs(i, j + 1, grid);
    }
};

int main() {
	Solution s;

	{
		std::vector<std::vector<char>> g{{'1', '1', '1', '1', '0'},
		                                 {'1', '1', '0', '1', '0'},
		                                 {'1', '1', '0', '0', '0'},
		                                 {'0', '0', '0', '0', '0'}};
		assert(s.numIslands(g) == 1);
	}

	{
		std::vector<std::vector<char>> g{{'1', '1', '0', '0', '0'},
		                                 {'1', '1', '0', '0', '0'},
		                                 {'0', '0', '1', '0', '0'},
		                                 {'0', '0', '0', '1', '1'}};
		assert(s.numIslands(g) == 3);
	}

	{
		std::vector<std::vector<char>> g{{'0', '0', '0'}, {'0', '0', '0'}};
		assert(s.numIslands(g) == 0);
	}

	{
		std::vector<std::vector<char>> g{{'1'}};
		assert(s.numIslands(g) == 1);
	}

	{
		// диагональ НЕ соединяет — 4 отдельных острова
		std::vector<std::vector<char>> g{{'1', '0', '1'},
		                                 {'0', '1', '0'},
		                                 {'1', '0', '0'}};
		assert(s.numIslands(g) == 4);
	}

	return 0;
}
