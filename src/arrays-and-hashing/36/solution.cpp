#include <vector>
#include <cassert>
#include <unordered_set>

class Solution {
public:
    bool isValidSudoku(std::vector<std::vector<char>>& board) {
        std::unordered_set<char> box[9], rows[9], cols[9];
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char ch = board[i][j];
                if (ch == '.') {
                    continue;
                }
                int box_i = (i / 3) * 3 + (j / 3);
                if (rows[i].count(ch) || cols[j].count(ch) || box[box_i].count(ch)) {
                    return false;
                }
                rows[i].insert(ch);
                cols[j].insert(ch);
                box[box_i].insert(ch);

            }
        }
        return true;
    }
};

int main() {
    Solution s;

    std::vector<std::vector<char>> valid = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    assert(s.isValidSudoku(valid) == true);

    // duplicate '8' in column 0 (rows 3 and 0 swapped)
    std::vector<std::vector<char>> invalid_col = valid;
    invalid_col[0][0] = '8';
    assert(s.isValidSudoku(invalid_col) == false);

    // duplicate '5' in row 0
    std::vector<std::vector<char>> invalid_row = valid;
    invalid_row[0][1] = '5';
    assert(s.isValidSudoku(invalid_row) == false);

    // duplicate in 3x3 box (top-left)
    std::vector<std::vector<char>> invalid_box = valid;
    invalid_box[2][2] = '5';
    assert(s.isValidSudoku(invalid_box) == false);

    // empty board (all dots) is valid
    std::vector<std::vector<char>> empty(9, std::vector<char>(9, '.'));
    assert(s.isValidSudoku(empty) == true);

    return 0;
}
