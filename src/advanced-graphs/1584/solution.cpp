#include <cstdlib>
#include <queue>
#include <unordered_set>
#include <vector>

class Solution {
  public:
	int minCostConnectPoints(std::vector<std::vector<int>> &points) {
		int n = points.size();
		std::vector<std::vector<int>> adj(n, std::vector<int>(n, 0));
		for (int i = 0; i < points.size(); ++i) {
			for (int j = 0; j < points.size(); ++j) {
				adj[i][j] = {std::abs(points[i][0] - points[j][0]) +
							 std::abs(points[i][1] - points[j][1])};
			}
		}
		using Item = std::pair<int, int>;
		std::priority_queue<Item, std::vector<Item>, std::greater<Item>> pq;
		std::unordered_set<int> visited;
		pq.push({adj[0][0], 0});
		int ans = 0;
		while (!pq.empty()) {
			auto [d, v] = pq.top();
			pq.pop();
			if (visited.count(v)) {
				continue;
			}
			visited.insert(v);
			ans += d;
			for (int to = 0; to < n; ++to) {
				if (!visited.count(to)) {
					pq.push({adj[v][to], to});
				}
			}
		}
		return ans;
	}
};
