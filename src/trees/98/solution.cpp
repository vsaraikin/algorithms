#include "../../../lib/cpp/node.cpp"
#include <cassert>
#include <climits>

class Solution {
  public:
	bool isValidBST(TreeNode* root) {
		return helper(root, LLONG_MIN, LLONG_MAX);
	}

	bool helper(TreeNode* root, long long left, long long right) {
		if (!root) return true;
		if (root->val <= left || root->val >= right) return false;
		return helper(root->left, left, root->val) &&
		       helper(root->right, root->val, right);
	}
};

int main() {
	Solution s;

	// пустое
	assert(s.isValidBST(nullptr) == true);

	// один узел
	{
		TreeNode root(1);
		assert(s.isValidBST(&root) == true);
	}

	// валидный: [2, 1, 3]
	{
		TreeNode n1(1), n3(3);
		TreeNode root(2, &n1, &n3);
		assert(s.isValidBST(&root) == true);
	}

	// невалидный: [5, 1, 4, null, null, 3, 6] — 3 в правом поддереве 5
	{
		TreeNode n3(3), n6(6);
		TreeNode n1(1), n4(4, &n3, &n6);
		TreeNode root(5, &n1, &n4);
		assert(s.isValidBST(&root) == false);
	}

	// невалидный: [2, 2, 2] — дубликаты не разрешены
	{
		TreeNode l(2), r(2);
		TreeNode root(2, &l, &r);
		assert(s.isValidBST(&root) == false);
	}

	// граничный: INT_MIN как корень
	{
		TreeNode root(INT_MIN);
		assert(s.isValidBST(&root) == true);
	}

	// граничный: INT_MAX как корень
	{
		TreeNode root(INT_MAX);
		assert(s.isValidBST(&root) == true);
	}

	// глубокий валидный
	//        4
	//       / \
	//      2   6
	//     / \ / \
	//    1  3 5  7
	{
		TreeNode n1(1), n3(3), n5(5), n7(7);
		TreeNode n2(2, &n1, &n3), n6(6, &n5, &n7);
		TreeNode root(4, &n2, &n6);
		assert(s.isValidBST(&root) == true);
	}

	// невалидный: левое поддерево содержит значение > корня где-то глубоко
	//        10
	//       /  \
	//      5    15
	//          /  \
	//         6    20    ← 6 < 10 в правом поддереве 10
	{
		TreeNode n6(6), n20(20);
		TreeNode n5(5), n15(15, &n6, &n20);
		TreeNode root(10, &n5, &n15);
		assert(s.isValidBST(&root) == false);
	}

	return 0;
}
