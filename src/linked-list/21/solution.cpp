#include <cassert>
#include <vector>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Хелперы для тестов: построить список из vector, сравнить с vector, освободить.

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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
		ListNode tmp;
        ListNode* tail = &tmp;
        while (list1 && list2) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
		
		if (list1) {
			tail->next = list1;
		} else {
			tail->next = list2;
		}

        return tmp.next;
    }
};

int main() {
	Solution s;

	// 1) общий случай
	{
		auto* a = build({1, 2, 4});
		auto* b = build({1, 3, 4});
		auto* m = s.mergeTwoLists(a, b);
		assert(toVec(m) == (std::vector<int>{1, 1, 2, 3, 4, 4}));
		freeList(m);
	}

	// 2) оба пустые
	{
		auto* m = s.mergeTwoLists(nullptr, nullptr);
		assert(m == nullptr);
	}

	// 3) один пустой
	{
		auto* a = build({});
		auto* b = build({0});
		auto* m = s.mergeTwoLists(a, b);
		assert(toVec(m) == (std::vector<int>{0}));
		freeList(m);
	}

	// 4) второй пустой
	{
		auto* a = build({5});
		auto* b = build({});
		auto* m = s.mergeTwoLists(a, b);
		assert(toVec(m) == (std::vector<int>{5}));
		freeList(m);
	}

	// 5) полностью в одной стороне
	{
		auto* a = build({1, 2, 3});
		auto* b = build({10, 20, 30});
		auto* m = s.mergeTwoLists(a, b);
		assert(toVec(m) == (std::vector<int>{1, 2, 3, 10, 20, 30}));
		freeList(m);
	}

	// 6) разные длины
	{
		auto* a = build({1, 5, 9});
		auto* b = build({2, 3, 4, 6, 7, 8});
		auto* m = s.mergeTwoLists(a, b);
		assert(toVec(m) ==
		       (std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}));
		freeList(m);
	}

	// 7) дубликаты
	{
		auto* a = build({2, 2, 2});
		auto* b = build({2, 2});
		auto* m = s.mergeTwoLists(a, b);
		assert(toVec(m) == (std::vector<int>{2, 2, 2, 2, 2}));
		freeList(m);
	}

	// 8) отрицательные
	{
		auto* a = build({-5, 0, 3});
		auto* b = build({-2, 1});
		auto* m = s.mergeTwoLists(a, b);
		assert(toVec(m) == (std::vector<int>{-5, -2, 0, 1, 3}));
		freeList(m);
	}

	return 0;
}
