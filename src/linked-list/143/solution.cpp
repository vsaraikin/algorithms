#include <cassert>
#include <vector>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* build(const std::vector<int>& v) {
	ListNode dummy;
	ListNode* tail = &dummy;
	for (int x : v) {
		tail->next = new ListNode(x);
		tail = tail->next;
	}
	return dummy.next;
}

std::vector<int> toVec(ListNode* head) {
	std::vector<int> out;
	for (auto* n = head; n; n = n->next) out.push_back(n->val);
	return out;
}

void freeList(ListNode* head) {
	while (head) {
		auto* next = head->next;
		delete head;
		head = next;
	}
}

class Solution {
  public:
	void reorderList(ListNode* head) {
		if (!head || !head->next) {
			return;
		}

		std::vector<ListNode*> nodes;
		for (auto* n = head; n; n = n->next) {
			nodes.push_back(n);
		}

		int l = 0;
		int r = nodes.size() - 1;
		while (l < r) {
			nodes[l]->next = nodes[r];
			++l;
			if (l == r) {
				break;
			}
			nodes[r]->next = nodes[l];
			--r;
		}
		nodes[l]->next = nullptr;
	}
};

int main() {
	Solution s;

	// 1) 4 элемента: [1,2,3,4] → [1,4,2,3]
	{
		auto* h = build({1, 2, 3, 4});
		s.reorderList(h);
		assert(toVec(h) == (std::vector<int>{1, 4, 2, 3}));
		freeList(h);
	}

	// 2) 5 элементов: [1,2,3,4,5] → [1,5,2,4,3]
	{
		auto* h = build({1, 2, 3, 4, 5});
		s.reorderList(h);
		assert(toVec(h) == (std::vector<int>{1, 5, 2, 4, 3}));
		freeList(h);
	}

	// 3) один элемент
	{
		auto* h = build({1});
		s.reorderList(h);
		assert(toVec(h) == (std::vector<int>{1}));
		freeList(h);
	}

	// 4) два элемента
	{
		auto* h = build({1, 2});
		s.reorderList(h);
		assert(toVec(h) == (std::vector<int>{1, 2}));
		freeList(h);
	}

	// 5) три элемента
	{
		auto* h = build({1, 2, 3});
		s.reorderList(h);
		assert(toVec(h) == (std::vector<int>{1, 3, 2}));
		freeList(h);
	}

	// 6) длинный чётный
	{
		auto* h = build({1, 2, 3, 4, 5, 6});
		s.reorderList(h);
		assert(toVec(h) == (std::vector<int>{1, 6, 2, 5, 3, 4}));
		freeList(h);
	}

	// 7) длинный нечётный
	{
		auto* h = build({1, 2, 3, 4, 5, 6, 7});
		s.reorderList(h);
		assert(toVec(h) == (std::vector<int>{1, 7, 2, 6, 3, 5, 4}));
		freeList(h);
	}

	return 0;
}
