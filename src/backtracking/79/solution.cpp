#include <cassert>
#include <string>
#include <vector>

class Solution {
public:
    int m;
    int n;

    bool exist(std::vector<std::vector<char>>& board, std::string word) {
        this->m = board.size() - 1;
        this->n = board[0].size() - 1;

        for (int i = 0; i <= this->m; ++i) {
            for (int j = 0; j <= this->n; ++j) {
                if (dfs(i, j, board, word, 0)) {
                    return true;
                }
            }
        }
        return false;
    };

    bool dfs(int x, int y, std::vector<std::vector<char>>& board, std::string word, int k) {
        if (x < 0 || x > this->m || y < 0 || y > this->n) {
            return false;
        }

        if (board[x][y] == '#') {
            return false;
        }

        if (word[k] != board[x][y]) {
            return false;
        }

        if (word.size() - 1 == k) {
            return true;
        }

        const char s = board[x][y];
        board[x][y] = '#';

        bool found =
            dfs(x + 1, y, board, word, k + 1) ||
            dfs(x - 1, y, board, word, k + 1) ||
            dfs(x, y + 1, board, word, k + 1) ||
            dfs(x, y - 1, board, word, k + 1);
        board[x][y] = s;

        return found;
    }
};

int main() {
	Solution s;

	std::vector<std::vector<char>> board{
	    {'A', 'B', 'C', 'E'},
	    {'S', 'F', 'C', 'S'},
	    {'A', 'D', 'E', 'E'}};

	assert(s.exist(board, "ABCCED") == true);
	assert(s.exist(board, "SEE") == true);
	assert(s.exist(board, "ABCB") == false);   // нельзя переиспользовать 'B'

	{
		std::vector<std::vector<char>> b{{'A'}};
		assert(s.exist(b, "A") == true);
		assert(s.exist(b, "B") == false);
	}

	{
		std::vector<std::vector<char>> b{{'A', 'A'}};
		assert(s.exist(b, "AAA") == false);
	}

	{
		std::vector<std::vector<char>> b{{'A', 'B'}, {'D', 'C'}};
		assert(s.exist(b, "ABCD") == true);   // A→B→C→D по кругу
	}

	return 0;
}
