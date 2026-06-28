#include <cassert>
#include <stack>
#include <vector>

// =============================================================================
// DFS on a graph (adjacency list). Unlike a tree, a graph can have cycles and
// multiple components, so we MUST track visited nodes to avoid infinite loops.
//
//   • recursive  — concise; O(V) stack depth in the worst case
//   • iterative  — explicit std::stack; avoids stack-overflow on deep graphs
//
// Both produce a reachability/visit order from a start node.
// =============================================================================

class Graph {
  public:
	explicit Graph(int n) : adj(n) {}

	void addEdge(int u, int v, bool directed = false) {
		adj[u].push_back(v);
		if (!directed) adj[v].push_back(u);
	}

	// Recursive DFS from `start`, returns visit order.
	std::vector<int> dfsRecursive(int start) {
		std::vector<int> order;
		std::vector<bool> seen(adj.size(), false);
		dfs(start, seen, order);
		return order;
	}

	// Iterative DFS from `start`, returns visit order.
	// Push neighbours in reverse so the smallest-index neighbour is explored
	// first (mirrors the recursive order).
	std::vector<int> dfsIterative(int start) {
		std::vector<int> order;
		std::vector<bool> seen(adj.size(), false);
		std::stack<int> st;
		st.push(start);
		while (!st.empty()) {
			int u = st.top();
			st.pop();
			if (seen[u]) continue;
			seen[u] = true;
			order.push_back(u);
			for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it) {
				if (!seen[*it]) st.push(*it);
			}
		}
		return order;
	}

	// Count connected components (undirected graph).
	int countComponents() {
		std::vector<bool> seen(adj.size(), false);
		std::vector<int> order;
		int comps = 0;
		for (int v = 0; v < (int)adj.size(); ++v) {
			if (!seen[v]) {
				++comps;
				dfs(v, seen, order);
			}
		}
		return comps;
	}

  private:
	std::vector<std::vector<int>> adj;

	void dfs(int u, std::vector<bool>& seen, std::vector<int>& order) {
		seen[u] = true;
		order.push_back(u);
		for (int v : adj[u]) {
			if (!seen[v]) dfs(v, seen, order);
		}
	}
};

int main() {
	// Graph:
	//   0 - 1 - 3
	//   |       |
	//   2 ------+
	// (undirected) + isolated node 4 + edge 5-6
	{
		Graph g(7);
		g.addEdge(0, 1);
		g.addEdge(0, 2);
		g.addEdge(1, 3);
		g.addEdge(2, 3);
		g.addEdge(5, 6);

		assert(g.dfsRecursive(0) == (std::vector<int>{0, 1, 3, 2}));
		assert(g.dfsIterative(0) == (std::vector<int>{0, 1, 3, 2}));

		// components: {0,1,2,3}, {4}, {5,6} = 3
		assert(g.countComponents() == 3);
	}

	// directed chain 0->1->2->3
	{
		Graph g(4);
		g.addEdge(0, 1, true);
		g.addEdge(1, 2, true);
		g.addEdge(2, 3, true);
		assert(g.dfsRecursive(0) == (std::vector<int>{0, 1, 2, 3}));
		assert(g.dfsIterative(0) == (std::vector<int>{0, 1, 2, 3}));
	}

	// cycle 0-1-2-0 must terminate
	{
		Graph g(3);
		g.addEdge(0, 1);
		g.addEdge(1, 2);
		g.addEdge(2, 0);
		assert(g.dfsRecursive(0).size() == 3);
		assert(g.dfsIterative(0).size() == 3);
	}

	// single node
	{
		Graph g(1);
		assert(g.dfsRecursive(0) == (std::vector<int>{0}));
		assert(g.countComponents() == 1);
	}

	return 0;
}
