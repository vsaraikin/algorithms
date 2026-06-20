#include "../../../lib/cpp/node.cpp"
#include <cassert>
#include <stack>
#include <vector>

// =============================================================================
// In-order: left → КОРЕНЬ → right
//
// Используется для:
//   • Получения отсортированной последовательности из BST
//   • Проверки BST (98 — должно идти строго возрастая)
//   • Поиска k-го наименьшего в BST (230)
//   • Конвертации BST в двусвязный список
// =============================================================================

// Рекурсивно — три строки тела.
void inorderRec(TreeNode* root, std::vector<int>& out) {
	if (!root) return;
	inorderRec(root->left, out);
	out.push_back(root->val);
	inorderRec(root->right, out);
}

// Итеративно через стек.
// Идея:
//   1) Спускаемся по left'ам до конца, push'ая каждый узел в стек.
//   2) Достаём верхний из стека, обрабатываем его.
//   3) Идём в его правое поддерево и повторяем с (1).
std::vector<int> inorderIter(TreeNode* root) {
	std::vector<int> out;
	std::stack<TreeNode*> st;
	TreeNode* cur = root;
	while (cur || !st.empty()) {
		while (cur) {
			st.push(cur);
			cur = cur->left;
		}
		cur = st.top();
		st.pop();
		out.push_back(cur->val);
		cur = cur->right;
	}
	return out;
}

// Удобная обёртка над рекурсивной версией.
std::vector<int> inorderTraversal(TreeNode* root) {
	std::vector<int> out;
	inorderRec(root, out);
	return out;
}

int main() {
	// пустое
	assert(inorderTraversal(nullptr) == std::vector<int>{});
	assert(inorderIter(nullptr) == std::vector<int>{});

	// один узел
	{
		TreeNode root(42);
		assert(inorderTraversal(&root) == (std::vector<int>{42}));
		assert(inorderIter(&root) == (std::vector<int>{42}));
	}

	// классический:
	//        1
	//       / \
	//      2   3
	//     / \
	//    4   5
	// in-order: 4, 2, 5, 1, 3
	{
		TreeNode n4(4), n5(5);
		TreeNode n2(2, &n4, &n5), n3(3);
		TreeNode root(1, &n2, &n3);
		std::vector<int> expected{4, 2, 5, 1, 3};
		assert(inorderTraversal(&root) == expected);
		assert(inorderIter(&root) == expected);
	}

	// BST даёт отсортированную последовательность:
	//        4
	//       / \
	//      2   6
	//     / \ / \
	//    1  3 5  7
	// in-order: 1, 2, 3, 4, 5, 6, 7
	{
		TreeNode n1(1), n3(3), n5(5), n7(7);
		TreeNode n2(2, &n1, &n3), n6(6, &n5, &n7);
		TreeNode root(4, &n2, &n6);
		std::vector<int> expected{1, 2, 3, 4, 5, 6, 7};
		assert(inorderTraversal(&root) == expected);
		assert(inorderIter(&root) == expected);
	}

	// вырожденное вправо:
	// in-order: 1, 2, 3, 4, 5
	{
		TreeNode n5(5);
		TreeNode n4(4, nullptr, &n5);
		TreeNode n3(3, nullptr, &n4);
		TreeNode n2(2, nullptr, &n3);
		TreeNode root(1, nullptr, &n2);
		std::vector<int> expected{1, 2, 3, 4, 5};
		assert(inorderTraversal(&root) == expected);
		assert(inorderIter(&root) == expected);
	}

	// вырожденное влево:
	// in-order: 5, 4, 3, 2, 1
	{
		TreeNode n5(5);
		TreeNode n4(4, &n5, nullptr);
		TreeNode n3(3, &n4, nullptr);
		TreeNode n2(2, &n3, nullptr);
		TreeNode root(1, &n2, nullptr);
		std::vector<int> expected{5, 4, 3, 2, 1};
		assert(inorderTraversal(&root) == expected);
		assert(inorderIter(&root) == expected);
	}

	// идеальное полное дерево:
	//        1
	//      /   \
	//     2     3
	//    / \   / \
	//   4   5 6   7
	// in-order: 4, 2, 5, 1, 6, 3, 7
	{
		TreeNode n4(4), n5(5), n6(6), n7(7);
		TreeNode n2(2, &n4, &n5), n3(3, &n6, &n7);
		TreeNode root(1, &n2, &n3);
		std::vector<int> expected{4, 2, 5, 1, 6, 3, 7};
		assert(inorderTraversal(&root) == expected);
		assert(inorderIter(&root) == expected);
	}

	return 0;
}
