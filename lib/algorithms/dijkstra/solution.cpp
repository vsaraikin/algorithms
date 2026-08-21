#include <cassert>
#include <climits>
#include <functional>
#include <queue>
#include <utility>
#include <vector>


std::vector<int> dijkstra(int src, const std::vector<std::vector<std::pair<int, int>>>& adj) {
	int n = adj.size();
	std::vector<int> dist(n, INT_MAX);
	dist[src] = 0;
	using Item = std::pair<int, int>;

	std::priority_queue<Item, std::vector<Item>, std::greater<Item>> pq;
	pq.push({0, src});
	while (!pq.empty()) {
		auto [d, u] = pq.top(); // distance, current node
		pq.pop();
		if (dist[u] < d) {
			continue;
		}
		
		for (auto [nei_v, nei_w]: adj[u]) {
			if (dist[nei_v] > nei_w +  d) {
				pq.push({nei_w + d, nei_v});
				dist[nei_v] = nei_w + d;
			}
			
		}
		
	}
	return dist;
}

int main() {
	{
		std::vector<std::vector<std::pair<int, int>>> adj(7);
		adj[1] = {{2, 4}, {3, 1}};
		adj[2] = {{4, 1}};
		adj[3] = {{2, 2}, {4, 6}, {5, 7}};
		adj[4] = {{5, 3}};

		auto dist = dijkstra(1, adj);
		assert(dist[1] == 0);
		assert(dist[2] == 3);        // 1 -> 3 -> 2
		assert(dist[3] == 1);
		assert(dist[4] == 4);        // 1 -> 3 -> 2 -> 4
		assert(dist[5] == 7);        // 1 -> 3 -> 2 -> 4 -> 5
		assert(dist[6] == INT_MAX);  // isloated
	}
}