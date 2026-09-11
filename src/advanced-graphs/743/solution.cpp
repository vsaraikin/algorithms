#include <algorithm>
#include <climits>
#include <queue>
#include <vector>


class Solution {
public:
    int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k) {
        std::vector<int> dist(n + 1, INT_MAX);
		dist[k] = 0;
		using Item = std::pair<int, int>;

		std::vector<std::vector<std::pair<int, int>>> adj(n + 1);
		for (int i = 0; i < times.size(); ++i) {
			adj[times[i][0]].push_back({times[i][1], times[i][2]});
		}


		std::priority_queue<Item, std::vector<Item>, std::greater<Item>> pq;
		pq.push({0, k});
		while (!pq.empty()) {
			auto [d, u] = pq.top();
			pq.pop();
			if (dist[u] < d) {
				continue;
			}

			for (auto [nei_v, nei_w]: adj[u]) {
				if (dist[nei_v] > nei_w + d) {
					pq.push({nei_w + d, nei_v});
					dist[nei_v] = nei_w + d;
				}
			}
		}
		int m = *std::max_element(dist.begin() + 1, dist.end());
		if (m == INT_MAX) {
			return -1;
		};
		return m;
    }
};
