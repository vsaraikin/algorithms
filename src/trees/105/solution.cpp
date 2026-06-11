#include "../../../lib/cpp/node.cpp"
#include <cassert>
#include <unordered_map>
#include <vector>

class Solution {
  public:
	TreeNode* buildTree(std::vector<int>& preorder,
	                    std::vector<int>& inorder) {
		for (int i = 0; i < inorder.size(); ++i) {
			idx[inorder[i]] = i;
		}
		preIdx = 0;
		return build(preorder, 0, inorder.size() - 1);
	}

	private:
		int preIdx;
		std::unordered_map<int, int> idx;

	TreeNode* build(std::vector<int> pre, int lo, int hi) {
		if (lo > hi) {
			return nullptr;
		}
		int val = pre[preIdx++];
		TreeNode* root = new TreeNode(val);
		int mid = idx[val];
		root->left = build(pre, lo, mid-1);
		root->right = build(pre, mid + 1, hi);
		return root;
	};
};

// Хелперы для тестов: сравнить два дерева структурно (по значениям).
bool sameTree(TreeNode* a, TreeNode* b) {
	if (!a && !b) return true;
	if (!a || !b) return false;
	if (a->val != b->val) return false;
	return sameTree(a->left, b->left) && sameTree(a->right, b->right);
}

void freeTree(TreeNode* root) {
	if (!root) return;
	freeTree(root->left);
	freeTree(root->right);
	delete root;
}

int main() {
	Solution s;

	// 1) классический пример из задачи
	//        3
	//       / \
	//      9  20
	//         / \
	//        15  7
	{
		std::vector<int> pre = {3, 9, 20, 15, 7};
		std::vector<int> in = {9, 3, 15, 20, 7};
		auto* t = s.buildTree(pre, in);

		TreeNode n15(15), n7(7), n9(9), n20(20, &n15, &n7);
		TreeNode expected(3, &n9, &n20);
		assert(sameTree(t, &expected));
		freeTree(t);
	}

	// 2) пустые массивы → пустое дерево
	{
		std::vector<int> pre, in;
		assert(s.buildTree(pre, in) == nullptr);
	}

	// 3) один узел
	{
		std::vector<int> pre = {1};
		std::vector<int> in = {1};
		auto* t = s.buildTree(pre, in);
		TreeNode expected(1);
		assert(sameTree(t, &expected));
		freeTree(t);
	}

	// 4) вырожденное вправо (по сути список)
	// pre: [1,2,3,4,5], in: [1,2,3,4,5] → 1→right(2→right(3→right(4→right(5))))
	{
		std::vector<int> pre = {1, 2, 3, 4, 5};
		std::vector<int> in = {1, 2, 3, 4, 5};
		auto* t = s.buildTree(pre, in);

		TreeNode n5(5);
		TreeNode n4(4, nullptr, &n5);
		TreeNode n3(3, nullptr, &n4);
		TreeNode n2(2, nullptr, &n3);
		TreeNode expected(1, nullptr, &n2);
		assert(sameTree(t, &expected));
		freeTree(t);
	}

	// 5) вырожденное влево
	// pre: [1,2,3,4,5], in: [5,4,3,2,1] → 1→left(2→left(3→left(4→left(5))))
	{
		std::vector<int> pre = {1, 2, 3, 4, 5};
		std::vector<int> in = {5, 4, 3, 2, 1};
		auto* t = s.buildTree(pre, in);

		TreeNode n5(5);
		TreeNode n4(4, &n5, nullptr);
		TreeNode n3(3, &n4, nullptr);
		TreeNode n2(2, &n3, nullptr);
		TreeNode expected(1, &n2, nullptr);
		assert(sameTree(t, &expected));
		freeTree(t);
	}

	// 6) идеальное полное дерево:
	//        1
	//      /   \
	//     2     3
	//    / \   / \
	//   4   5 6   7
	{
		std::vector<int> pre = {1, 2, 4, 5, 3, 6, 7};
		std::vector<int> in = {4, 2, 5, 1, 6, 3, 7};
		auto* t = s.buildTree(pre, in);

		TreeNode n4(4), n5(5), n6(6), n7(7);
		TreeNode n2(2, &n4, &n5), n3(3, &n6, &n7);
		TreeNode expected(1, &n2, &n3);
		assert(sameTree(t, &expected));
		freeTree(t);
	}

	// 7) ассиметричное
	//        1
	//       / \
	//      2   3
	//     /     \
	//    4       5
	{
		std::vector<int> pre = {1, 2, 4, 3, 5};
		std::vector<int> in = {4, 2, 1, 3, 5};
		auto* t = s.buildTree(pre, in);

		TreeNode n4(4), n5(5);
		TreeNode n2(2, &n4, nullptr), n3(3, nullptr, &n5);
		TreeNode expected(1, &n2, &n3);
		assert(sameTree(t, &expected));
		freeTree(t);
	}

	// 8) отрицательные значения
	{
		std::vector<int> pre = {0, -1, 3, 2};
		std::vector<int> in = {-1, 0, 2, 3};
		auto* t = s.buildTree(pre, in);

		TreeNode n2(2);
		TreeNode nm1(-1), n3(3, &n2, nullptr);
		TreeNode expected(0, &nm1, &n3);
		assert(sameTree(t, &expected));
		freeTree(t);
	}

	return 0;
}
