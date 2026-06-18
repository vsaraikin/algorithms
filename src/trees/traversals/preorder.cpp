#include "../../../lib/cpp/node.cpp"
#include <cassert>
#include <stack>
#include <vector>

// =============================================================================
// Pre-order: КОРЕНЬ → left → right
//
// Используется для:
//   • Копирования / сериализации дерева
//   • Префиксная запись выражений
//   • Обхода "сверху вниз" — родитель раньше детей
// =============================================================================

// Рекурсивно — самый компактный вариант.
void preorderRec(TreeNode* root, std::vector<int>& out) {
	if (!root) return;
	out.push_back(root->val);
	preorderRec(root->left, out);
	preorderRec(root->right, out);
}

// Итеративно через стек.
// Трюк: push сначала правого, потом левого (LIFO → левый выйдет первым).
std::vector<int> preorderIter(TreeNode* root) {
	std::vector<int> out;
	if (!root) return out;
	std::stack<TreeNode*> st;
	st.push(root);
	while (!st.empty()) {
		TreeNode* n = st.top();
		st.pop();
		out.push_back(n->val);
		if (n->right) st.push(n->right);
		if (n->left) st.push(n->left);
	}
	return out;
}

// Удобная обёртка над рекурсивной версией.
std::vector<int> preorderTraversal(TreeNode* root) {
	std::vector<int> out;
	preorderRec(root, out);
	return out;
}

int main() {
	// пустое
	assert(preorderTraversal(nullptr) == std::vector<int>{});
	assert(preorderIter(nullptr) == std::vector<int>{});

	// один узел
	{
		TreeNode root(42);
		assert(preorderTraversal(&root) == (std::vector<int>{42}));
		assert(preorderIter(&root) == (std::vector<int>{42}));
	}

	// классический пример:
	//        1
	//       / \
	//      2   3
	//     / \
	//    4   5
	// pre-order: 1, 2, 4, 5, 3
	{
		TreeNode n4(4), n5(5);
		TreeNode n2(2, &n4, &n5), n3(3);
		TreeNode root(1, &n2, &n3);
		std::vector<int> expected{1, 2, 4, 5, 3};
		assert(preorderTraversal(&root) == expected);
		assert(preorderIter(&root) == expected);
	}

	// вырожденное вправо: 1 → 2 → 3 → 4 → 5
	{
		TreeNode n5(5);
		TreeNode n4(4, nullptr, &n5);
		TreeNode n3(3, nullptr, &n4);
		TreeNode n2(2, nullptr, &n3);
		TreeNode root(1, nullptr, &n2);
		std::vector<int> expected{1, 2, 3, 4, 5};
		assert(preorderTraversal(&root) == expected);
		assert(preorderIter(&root) == expected);
	}

	// вырожденное влево
	{
		TreeNode n5(5);
		TreeNode n4(4, &n5, nullptr);
		TreeNode n3(3, &n4, nullptr);
		TreeNode n2(2, &n3, nullptr);
		TreeNode root(1, &n2, nullptr);
		std::vector<int> expected{1, 2, 3, 4, 5};
		assert(preorderTraversal(&root) == expected);
		assert(preorderIter(&root) == expected);
	}

	// идеальное полное дерево:
	//        1
	//      /   \
	//     2     3
	//    / \   / \
	//   4   5 6   7
	// pre-order: 1, 2, 4, 5, 3, 6, 7
	{
		TreeNode n4(4), n5(5), n6(6), n7(7);
		TreeNode n2(2, &n4, &n5), n3(3, &n6, &n7);
		TreeNode root(1, &n2, &n3);
		std::vector<int> expected{1, 2, 4, 5, 3, 6, 7};
		assert(preorderTraversal(&root) == expected);
		assert(preorderIter(&root) == expected);
	}

	return 0;
}
