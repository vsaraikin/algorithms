#include <cassert>
#include <vector>
#include <unordered_set>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Построить список из vector с опциональной "позицией цикла":
// posCycle = -1 → без цикла. Иначе хвост указывает на узел с этим индексом.
ListNode* build(const std::vector<int>& v, int posCycle = -1) {
	if (v.empty()) return nullptr;
	std::vector<ListNode*> nodes;
	nodes.reserve(v.size());
	for (int x : v) nodes.push_back(new ListNode(x));
	for (size_t i = 0; i + 1 < nodes.size(); i++) nodes[i]->next = nodes[i + 1];
	if (posCycle >= 0 && posCycle < (int)nodes.size()) {
		nodes.back()->next = nodes[posCycle];
	}
	return nodes.front();
}

// Освободить (только когда нет цикла).
void freeList(ListNode* head) {
	while (head) {
		auto* next = head->next;
		delete head;
		head = next;
	}
}

class Solution {
  public:
    bool hasCycle(ListNode *head) {
        std::unordered_set<ListNode*> nodes;
        while (head) {
            head = head->next;
            if (nodes.count(head)) {
                return true;
            }
            nodes.insert(head);
        }
        return false;
    }

	// Floyd's, canonical
	bool hasCycle2(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                return true;
            }
        }
        return false;
    }
};

int main() {
	Solution s;

	// 1) пустой список
	{
		assert(s.hasCycle(nullptr) == false);
	}

	// 2) один узел без цикла
	{
		auto* h = build({1});
		assert(s.hasCycle(h) == false);
		freeList(h);
	}

	// 3) один узел с циклом на себя
	{
		auto* h = build({1}, 0);
		assert(s.hasCycle(h) == true);
		// не освобождаем — цикл
	}

	// 4) обычный список без цикла
	{
		auto* h = build({1, 2, 3, 4, 5});
		assert(s.hasCycle(h) == false);
		freeList(h);
	}

	// 5) цикл с начала
	{
		auto* h = build({1, 2, 3, 4}, 0);
		assert(s.hasCycle(h) == true);
	}

	// 6) цикл с середины
	{
		auto* h = build({3, 2, 0, -4}, 1);
		assert(s.hasCycle(h) == true);
	}

	// 7) два узла без цикла
	{
		auto* h = build({1, 2});
		assert(s.hasCycle(h) == false);
		freeList(h);
	}

	// 8) два узла с циклом
	{
		auto* h = build({1, 2}, 0);
		assert(s.hasCycle(h) == true);
	}

	return 0;
}
