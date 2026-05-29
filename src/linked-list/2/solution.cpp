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
	// recursion
	// O(max(m, n)) + O(n) on stack
	// ListNode* addTwoNumbers(ListNode* l1, ListNode* l2, int carry = 0) {
	// 	if (!l1 && !l2 && !carry) {
	// 		return nullptr;
	// 	}

	// 	int s = carry;
	// 	if (l1) {
	// 		s += l1->val;
	// 	}
	// 	if (l2) {
	// 		s += l2->val;
	// 	}

	// 	ListNode* result = new ListNode(s % 10);
	// 	result->next = this->addTwoNumbers(l1 ? l1->next : l1, l2 ? l2->next : l2, s / 10);
	// 	return result;
	// }

	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode dummy;
		ListNode* tail = &dummy;
        int carry = 0;
		while (l1 || l2 || carry) {
			int s = carry;
			if (l1) {
				s += l1->val;
				l1 = l1->next;
			}
			if (l2) {
				s += l2->val;
				l2 = l2->next;
			}
			carry = s / 10;
			tail->next = new ListNode(s % 10);
			tail = tail->next;
		}

		return dummy.next;
	}
};

int main() {
	Solution s;

	// 1) 342 + 465 = 807
	{
		auto* a = build({2, 4, 3});
		auto* b = build({5, 6, 4});
		auto* r = s.addTwoNumbers(a, b);
		assert(toVec(r) == (std::vector<int>{7, 0, 8}));
		freeList(a); freeList(b); freeList(r);
	}

	// 2) 0 + 0 = 0
	{
		auto* a = build({0});
		auto* b = build({0});
		auto* r = s.addTwoNumbers(a, b);
		assert(toVec(r) == (std::vector<int>{0}));
		freeList(a); freeList(b); freeList(r);
	}

	// 3) 9999999 + 9999 = 10009998 — длинные разные размеры + carry до конца
	{
		auto* a = build({9, 9, 9, 9, 9, 9, 9});
		auto* b = build({9, 9, 9, 9});
		auto* r = s.addTwoNumbers(a, b);
		assert(toVec(r) == (std::vector<int>{8, 9, 9, 9, 0, 0, 0, 1}));
		freeList(a); freeList(b); freeList(r);
	}

	// 4) 1 + 99 = 100 — carry создаёт новый разряд
	{
		auto* a = build({1});
		auto* b = build({9, 9});
		auto* r = s.addTwoNumbers(a, b);
		assert(toVec(r) == (std::vector<int>{0, 0, 1}));
		freeList(a); freeList(b); freeList(r);
	}

	// 5) разные длины без carry
	{
		auto* a = build({1, 2, 3});
		auto* b = build({4, 5});
		auto* r = s.addTwoNumbers(a, b);
		assert(toVec(r) == (std::vector<int>{5, 7, 3}));
		freeList(a); freeList(b); freeList(r);
	}

	// 6) 5 + 5 = 10 — carry в самом конце
	{
		auto* a = build({5});
		auto* b = build({5});
		auto* r = s.addTwoNumbers(a, b);
		assert(toVec(r) == (std::vector<int>{0, 1}));
		freeList(a); freeList(b); freeList(r);
	}

	// 7) один список длинный, второй короткий, без carry в общей части
	{
		auto* a = build({0, 1});
		auto* b = build({0, 1, 2});
		auto* r = s.addTwoNumbers(a, b);
		assert(toVec(r) == (std::vector<int>{0, 2, 2}));
		freeList(a); freeList(b); freeList(r);
	}

	return 0;
}
