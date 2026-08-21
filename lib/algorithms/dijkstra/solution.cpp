#include <cassert>
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
		auto [d, u] = pq.top();
		pq.pop();

		if (d > dist[u]) {
			continue;
		}

		for (auto [v, w]: adj[u]) {
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				pq.emplace(dist[v], v);
			}
		}
	}
	return dist;
}

int main() {
	{
		std::vector<std::vector<std::pair<int, int>>> adj(6);
		adj[0] = {{1, 4}, {2, 1}};
		adj[1] = {{3, 1}};
		adj[2] = {{1, 2}, {3, 6}, {4, 7}};
		adj[3] = {{4, 3}};

		auto dist = dijkstra(0, adj);
		assert(dist[0] == 0);
		assert(dist[1] == 3);
		assert(dist[2] == 1);
		assert(dist[3] == 4);
		assert(dist[4] == 7);
		assert(dist[5] == INT_MAX);
	}
}