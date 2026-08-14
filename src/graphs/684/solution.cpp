#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
public:
    std::vector<int> findRedundantConnection(std::vector<std::vector<int>>& edges) {
		int n = edges.size();
		parent.resize(n + 1);
		for (int i = 1; i <= n; ++i) {
			parent[i] = i;
		}

		for (auto& pair: edges) {
			int u = pair[0];
			int v = pair[1];
			if (!unite(u, v)) {
				return {u, v};
			}
		}
		return {};
	};
private:
	std::vector<int> parent;

	int find(int x) {
		while (parent[x] != x) {
			x = parent[x];
		}
		return x;
	}

	bool unite(int u, int v) {
		int ru = find(u);
		int rv = find(v);
		if (ru == rv) {
			return false;
		}
		parent[rv] = ru;
		return true;
	}

    // std::vector<int> findRedundantConnection(std::vector<std::vector<int>>& edges) {
    //     std::unordered_map<int, std::vector<int>>  graph;
	// 	for (std::vector<int> edge: edges) {
	// 		int u = edge[0];
	// 		int v = edge[1];
	// 		if (hasPath(u, v, graph, {})) {
	// 			return {u, v};
	// 		}
	// 		graph[u].push_back(v);
	// 		graph[v].push_back(u);
	// 	}
	// 	return {};
    // }

	// // dfs
	// bool hasPath(int u, int v, std::unordered_map<int, std::vector<int>> & graph, std::unordered_set<int> visited) {
	// 	if (u == v) {
	// 		return true;
	// 	}

	// 	if (visited.count(u)) {
	// 		return false;
	// 	}

	// 	visited.insert(u);
	// 	for (int neighbour: graph[v]) {
	// 		if (hasPath(neighbour, u, graph, visited)) {
	// 			return true;
	// 		}
	// 	}
	// 	return false;
	// }
};
