#include <cassert>
#include <cstddef>
#include <vector>

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
  public:
	ListNode *mergeKLists(std::vector<ListNode *> &lists) {
		if (lists.empty())
			return nullptr;
		int n = lists.size();

		while (n > 1) {
			int l = 0, r = n - 1;
			while (l < r) {
				lists[l] = mergeTwoLists(lists[l], lists[r]);
				l++;
				r--;
			}
			n = (n + 1) / 2; // длина активной части после прохода
		}
		return lists[0];
	}

	ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
		ListNode dummy;
		ListNode *tail = &dummy;
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
		tail->next = list1 ? list1 : list2; // одной строкой: подвесить остаток
		return dummy.next;
	}
};

ListNode *build(const std::vector<int> &v) {
	ListNode dummy;
	ListNode *tail = &dummy;
	for (int x : v) {
		tail->next = new ListNode(x);
		tail = tail->next;
	}
	return dummy.next;
}

std::vector<int> toVec(ListNode *head) {
	std::vector<int> out;
	for (auto *n = head; n; n = n->next)
		out.push_back(n->val);
	return out;
}

void freeList(ListNode *head) {
	while (head) {
		auto *next = head->next;
		delete head;
		head = next;
	}
}

int main() {
	Solution s;

	// 1) обычный
	{
		std::vector<ListNode *> lists = {build({1, 4, 5}), build({1, 3, 4}),
										 build({2, 6})};
		auto *r = s.mergeKLists(lists);
		assert(toVec(r) == (std::vector<int>{1, 1, 2, 3, 4, 4, 5, 6}));
		freeList(r);
	}

	// 2) пустой массив
	{
		std::vector<ListNode *> lists;
		auto *r = s.mergeKLists(lists);
		assert(r == nullptr);
	}

	// 3) массив из одного пустого
	{
		std::vector<ListNode *> lists = {nullptr};
		auto *r = s.mergeKLists(lists);
		assert(r == nullptr);
	}

	// 4) один список
	{
		std::vector<ListNode *> lists = {build({1, 2, 3})};
		auto *r = s.mergeKLists(lists);
		assert(toVec(r) == (std::vector<int>{1, 2, 3}));
		freeList(r);
	}

	// 5) несколько пустых среди непустых
	{
		std::vector<ListNode *> lists = {nullptr, build({1, 2}), nullptr,
										 build({3, 4})};
		auto *r = s.mergeKLists(lists);
		assert(toVec(r) == (std::vector<int>{1, 2, 3, 4}));
		freeList(r);
	}

	// 6) все одинаковые значения
	{
		std::vector<ListNode *> lists = {build({1, 1, 1}), build({1, 1}),
										 build({1})};
		auto *r = s.mergeKLists(lists);
		assert(toVec(r) == (std::vector<int>{1, 1, 1, 1, 1, 1}));
		freeList(r);
	}

	// 7) отрицательные
	{
		std::vector<ListNode *> lists = {build({-10, -5, 0}), build({-7, -2}),
										 build({1, 2})};
		auto *r = s.mergeKLists(lists);
		assert(toVec(r) == (std::vector<int>{-10, -7, -5, -2, 0, 1, 2}));
		freeList(r);
	}

	return 0;
}
