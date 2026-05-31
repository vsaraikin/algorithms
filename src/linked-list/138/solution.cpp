#include <cassert>
#include <unordered_map>
#include <vector>

struct Node {
	int val;
	Node* next;
	Node* random;
	Node(int v) : val(v), next(nullptr), random(nullptr) {}
};

// Хелпер: построить список с random'ами.
// vals — значения, randomIdx[i] = индекс узла куда должен указать i-й random
// (или -1 если nullptr).
Node* build(const std::vector<int>& vals,
            const std::vector<int>& randomIdx) {
	if (vals.empty()) return nullptr;
	std::vector<Node*> nodes;
	for (int v : vals) nodes.push_back(new Node(v));
	for (size_t i = 0; i + 1 < nodes.size(); i++) nodes[i]->next = nodes[i + 1];
	for (size_t i = 0; i < nodes.size(); i++) {
		if (randomIdx[i] >= 0) nodes[i]->random = nodes[randomIdx[i]];
	}
	return nodes.front();
}

void freeList(Node* head) {
	while (head) {
		auto* next = head->next;
		delete head;
		head = next;
	}
}

// Проверить что копия структурно равна оригиналу:
// все val совпадают и random'ы указывают на узлы с теми же индексами.
bool deepEqual(Node* orig, Node* copy) {
	std::unordered_map<Node*, int> origIdx;
	std::unordered_map<Node*, int> copyIdx;
	int i = 0;
	for (auto* n = orig; n; n = n->next) origIdx[n] = i++;
	int j = 0;
	for (auto* n = copy; n; n = n->next) copyIdx[n] = j++;
	if (origIdx.size() != copyIdx.size()) return false;

	auto* o = orig;
	auto* c = copy;
	while (o && c) {
		if (o == c) return false;          // должны быть НОВЫЕ узлы
		if (o->val != c->val) return false;
		int ro = o->random ? origIdx[o->random] : -1;
		int rc = c->random ? copyIdx[c->random] : -1;
		if (ro != rc) return false;
		o = o->next;
		c = c->next;
	}
	return !o && !c;
}

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) {
            return nullptr;
        }

        std::unordered_map<Node*, Node*> m;
        for (Node* n = head; n; n = n->next) {
            m[n] = new Node(n->val);
        }

        for (Node* n = head; n; n = n->next) {
            m[n]->next = n->next ? m[n->next] : nullptr;
            m[n]->random = n->random ? m[n->random] : nullptr;
        }

        return m[head];
    }
};



int main() {
	Solution s;

	// 1) обычный список
	{
		auto* h = build({7, 13, 11, 10, 1},
		                {-1, 0, 4, 2, 0});
		auto* c = s.copyRandomList(h);
		assert(deepEqual(h, c));
		freeList(h);
		freeList(c);
	}

	// 2) пустой
	{
		auto* c = s.copyRandomList(nullptr);
		assert(c == nullptr);
	}

	// 3) один узел без random
	{
		auto* h = build({5}, {-1});
		auto* c = s.copyRandomList(h);
		assert(deepEqual(h, c));
		freeList(h);
		freeList(c);
	}

	// 4) один узел с random на себя
	{
		auto* h = build({5}, {0});
		auto* c = s.copyRandomList(h);
		assert(deepEqual(h, c));
		freeList(h);
		freeList(c);
	}

	// 5) все random'ы nullptr
	{
		auto* h = build({1, 2, 3}, {-1, -1, -1});
		auto* c = s.copyRandomList(h);
		assert(deepEqual(h, c));
		freeList(h);
		freeList(c);
	}

	// 6) все random'ы на head
	{
		auto* h = build({1, 2, 3, 4}, {0, 0, 0, 0});
		auto* c = s.copyRandomList(h);
		assert(deepEqual(h, c));
		freeList(h);
		freeList(c);
	}

	return 0;
}
