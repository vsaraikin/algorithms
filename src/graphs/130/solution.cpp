#include <cassert>
#include <vector>

class Solution {
public:
	void solve(std::vector<std::vector<char>>& board) {
		if (board.empty() || board[0].empty()) {
			return;
		}
		int m = board.size();
		int n = board[0].size();

		for (int i = 0; i < m; ++i) {
			dfs(i, 0, board);
			dfs(i, n - 1, board);
		}
		for (int j = 0; j < n; ++j) {
			dfs(0, j, board);
			dfs(m - 1, j, board);
		}

		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (board[i][j] == 'O') {
					board[i][j] = 'X';
				} else if (board[i][j] == 'V') {
					board[i][j] = 'O';
				}
			}
		}
	}

private:
	void dfs(int r, int c, std::vector<std::vector<char>>& board) {
		if (r < 0 || c < 0 || r >= (int)board.size() ||
		    c >= (int)board[0].size() || board[r][c] != 'O') {
			return;
		}
		board[r][c] = 'V';  // пометить безопасной
		dfs(r + 1, c, board);
		dfs(r - 1, c, board);
		dfs(r, c + 1, board);
		dfs(r, c - 1, board);
	}
};

int main() {
	Solution s;

	// классика: внутренняя область захвачена, нижняя 'O' у края — выживает
	{
		std::vector<std::vector<char>> board{
		    {'X', 'X', 'X', 'X'},
		    {'X', 'O', 'O', 'X'},
		    {'X', 'X', 'O', 'X'},
		    {'X', 'O', 'X', 'X'}};
		std::vector<std::vector<char>> expected{
		    {'X', 'X', 'X', 'X'},
		    {'X', 'X', 'X', 'X'},
		    {'X', 'X', 'X', 'X'},
		    {'X', 'O', 'X', 'X'}};
		s.solve(board);
		assert(board == expected);
	}

	// вертикальная 'O'-полоса касается верха и низа → вся выживает
	{
		std::vector<std::vector<char>> board{
		    {'X', 'O', 'X'},
		    {'X', 'O', 'X'},
		    {'X', 'O', 'X'}};
		std::vector<std::vector<char>> expected = board;
		s.solve(board);
		assert(board == expected);
	}

	// одна клетка
	{
		std::vector<std::vector<char>> board{{'O'}};
		std::vector<std::vector<char>> expected{{'O'}};  // на границе → выживает
		s.solve(board);
		assert(board == expected);
	}

	// полностью окружённая одиночная 'O'
	{
		std::vector<std::vector<char>> board{
		    {'X', 'X', 'X'},
		    {'X', 'O', 'X'},
		    {'X', 'X', 'X'}};
		std::vector<std::vector<char>> expected{
		    {'X', 'X', 'X'},
		    {'X', 'X', 'X'},
		    {'X', 'X', 'X'}};
		s.solve(board);
		assert(board == expected);
	}

	return 0;
}
