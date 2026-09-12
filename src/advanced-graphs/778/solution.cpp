#include <algorithm>
#include <array>
#include <queue>
#include <vector>

constexpr std::array<std::pair<int,int>, 4> neighbours = {{{0,1}, {1,0}, {-1,0}, {0,-1}}};

class Solution {
public:
    int swimInWater(std::vector<std::vector<int>>& grid) {
		int n = grid.size();
		std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
		using Pair = std::tuple<int,int,int>; // value, x, y
		std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;

		pq.push({grid[0][0], 0, 0});
		while (!pq.empty()) {
			auto [t, i, j] = pq.top(); pq.pop();
			if (i == n-1 && j == n-1) {
				return t;
			}
			if (visited[i][j]) {
				continue;
			}
			visited[i][j] = true;
			for (auto [d_x, d_y]: neighbours) {
				int tmp_x = i - d_x; int tmp_y = j - d_y;
				if (tmp_x >= n || tmp_x < 0 || tmp_y >= n || tmp_y < 0 || visited[tmp_x][tmp_y]) {
					continue;
				}
				pq.push({std::max(t, grid[tmp_x][tmp_y]), tmp_x, tmp_y});
			}
		}
		return 0;
    }
};