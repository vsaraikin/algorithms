#include <cassert>
#include <unordered_map>
#include <vector>

// На LeetCode Node предопределён — здесь задаём его сами для локальных тестов.
class Node {
public:
	int val;
	std::vector<Node*> neighbors;
	Node() : val(0) {}
	Node(int _val) : val(_val) {}
	Node(int _val, std::vector<Node*> _neighbors)
	    : val(_val), neighbors(_neighbors) {}
};

class Solution {
public:
	Node* cloneGraph(Node* node) {
		m.clear();  // на случай повторного вызова на одном объекте
		return dfs(node);
	}

private:
	std::unordered_map<Node*, Node*> m;
	Node* dfs(Node* node) {
		if (!node) {
			return nullptr;
		}
		if (m.count(node)) {
			return m[node];  // уже клонировали — вернуть, чтобы не зациклиться
		}

		Node* clone = new Node(node->val);
		m[node] = clone;  // регистрируем ДО обхода соседей (иначе бесконечный цикл)
		for (Node* neighbor : node->neighbors) {
			clone->neighbors.push_back(dfs(neighbor));
		}
		return clone;
	}
};

// ---- тесты ----

// Собрать граф из списка смежности (1-индексированного, как на LeetCode).
static std::vector<Node*> build(const std::vector<std::vector<int>>& adj) {
	int n = adj.size();
	std::vector<Node*> nodes(n + 1, nullptr);
	for (int i = 1; i <= n; ++i) nodes[i] = new Node(i);
	for (int i = 1; i <= n; ++i)
		for (int j : adj[i - 1]) nodes[i]->neighbors.push_back(nodes[j]);
	return nodes;
}

// Проверить, что clone — глубокая копия orig (обход с картой соответствий).
static void assertDeepCopy(Node* orig, Node* clone) {
	if (!orig) {
		assert(clone == nullptr);
		return;
	}
	std::unordered_map<Node*, Node*> seen;
	std::vector<Node*> stack{orig};
	seen[orig] = clone;
	while (!stack.empty()) {
		Node* o = stack.back();
		stack.pop_back();
		Node* c = seen[o];
		assert(c != o);                              // разные объекты (deep copy)
		assert(c->val == o->val);                    // тот же val
		assert(c->neighbors.size() == o->neighbors.size());
		for (size_t k = 0; k < o->neighbors.size(); ++k) {
			Node* on = o->neighbors[k];
			Node* cn = c->neighbors[k];
			assert(cn != on);                        // сосед тоже клонирован
			assert(cn->val == on->val);
			if (!seen.count(on)) {
				seen[on] = cn;
				stack.push_back(on);
			} else {
				assert(seen[on] == cn);              // тот же клон переиспользован
			}
		}
	}
}

int main() {
	Solution s;

	// классика: 4 узла по кругу [[2,4],[1,3],[2,4],[1,3]]
	{
		auto nodes = build({{2, 4}, {1, 3}, {2, 4}, {1, 3}});
		Node* clone = s.cloneGraph(nodes[1]);
		assertDeepCopy(nodes[1], clone);
	}

	// один узел без соседей [[]]
	{
		auto nodes = build({{}});
		Node* clone = s.cloneGraph(nodes[1]);
		assertDeepCopy(nodes[1], clone);
		assert(clone->neighbors.empty());
	}

	// пустой граф
	{
		assert(s.cloneGraph(nullptr) == nullptr);
	}

	// два узла, связанные друг с другом (цикл длины 2)
	{
		auto nodes = build({{2}, {1}});
		Node* clone = s.cloneGraph(nodes[1]);
		assertDeepCopy(nodes[1], clone);
		assert(clone->neighbors[0]->neighbors[0] == clone);  // 1→2→1 замкнулось на клон
	}

	return 0;
}
