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
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};

int main() {
	Solution s;

	// 1) обычный
	{
		auto* h = build({1, 2, 3, 4, 5});
		auto* r = s.reverseList(h);
		assert(toVec(r) == (std::vector<int>{5, 4, 3, 2, 1}));
		freeList(r);
	}

	// 2) два элемента
	{
		auto* h = build({1, 2});
		auto* r = s.reverseList(h);
		assert(toVec(r) == (std::vector<int>{2, 1}));
		freeList(r);
	}

	// 3) один элемент
	{
		auto* h = build({7});
		auto* r = s.reverseList(h);
		assert(toVec(r) == (std::vector<int>{7}));
		freeList(r);
	}

	// 4) пустой
	{
		auto* r = s.reverseList(nullptr);
		assert(r == nullptr);
	}

	// 5) с отрицательными
	{
		auto* h = build({-3, 0, 5, -7});
		auto* r = s.reverseList(h);
		assert(toVec(r) == (std::vector<int>{-7, 5, 0, -3}));
		freeList(r);
	}

	// 6) дубликаты
	{
		auto* h = build({1, 1, 1});
		auto* r = s.reverseList(h);
		assert(toVec(r) == (std::vector<int>{1, 1, 1}));
		freeList(r);
	}

	return 0;
}
