#include <vector>
#include <queue>

class Solution {
public:
    int orangesRotting(std::vector<std::vector<int>>& grid) {
        std::queue<std::pair<int, int>> q;

		int fresh = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                } else if (grid[i][j] == 1) {
					++fresh;
				}
            }
        }

        std::vector<std::pair<int, int>> bias = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
		int minutes = 0;
        while (!q.empty() && fresh > 0) {
			size_t sz = q.size();
			for (int k = 0; k < sz; ++k) {
				std::pair<int, int> rotten = q.front();
				q.pop();
				
				for (auto coor : bias) {
					int tmp_x = rotten.first + coor.first;
					int tmp_y = rotten.second + coor.second;
					if (0 <= tmp_x && tmp_x < grid.size() && 0 <= tmp_y && tmp_y < grid[0].size()) {
						if (grid[tmp_x][tmp_y] == 1) {
							grid[tmp_x][tmp_y] = 2;
							q.push({tmp_x, tmp_y});
							--fresh;
						}
					}
				}
			}
			
			++minutes;
        }
		return fresh == 0 ? minutes: -1;
    }
};