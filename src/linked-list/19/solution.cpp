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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* fast = head;
        ListNode* slow = head;

        for (int i = 0; i < n; ++i) {
            fast = fast->next;
        }

        if (!fast) {
            return head->next; 
        }

        while (fast->next) {
            fast = fast->next;
            slow = slow->next;
        }

        slow->next = slow->next->next;
        return head;
    }
};
int main() {
	Solution s;

	// 1) обычный случай — убрать 2й с конца
	{
		auto* h = build({1, 2, 3, 4, 5});
		auto* r = s.removeNthFromEnd(h, 2);
		assert(toVec(r) == (std::vector<int>{1, 2, 3, 5}));
		freeList(r);
	}

	// 2) убрать единственный элемент
	{
		auto* h = build({1});
		auto* r = s.removeNthFromEnd(h, 1);
		assert(r == nullptr);
	}

	// 3) убрать первый (последний с конца)
	{
		auto* h = build({1, 2});
		auto* r = s.removeNthFromEnd(h, 2);
		assert(toVec(r) == (std::vector<int>{2}));
		freeList(r);
	}

	// 4) убрать последний (первый с конца)
	{
		auto* h = build({1, 2});
		auto* r = s.removeNthFromEnd(h, 1);
		assert(toVec(r) == (std::vector<int>{1}));
		freeList(r);
	}

	// 5) убрать из середины
	{
		auto* h = build({1, 2, 3, 4, 5});
		auto* r = s.removeNthFromEnd(h, 3);
		assert(toVec(r) == (std::vector<int>{1, 2, 4, 5}));
		freeList(r);
	}

	// 6) убрать первый из длинного
	{
		auto* h = build({1, 2, 3, 4, 5});
		auto* r = s.removeNthFromEnd(h, 5);
		assert(toVec(r) == (std::vector<int>{2, 3, 4, 5}));
		freeList(r);
	}

	// 7) убрать последний из длинного
	{
		auto* h = build({1, 2, 3, 4, 5});
		auto* r = s.removeNthFromEnd(h, 1);
		assert(toVec(r) == (std::vector<int>{1, 2, 3, 4}));
		freeList(r);
	}

	return 0;
}
