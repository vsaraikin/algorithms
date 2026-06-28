#include "../../../lib/cpp/node.cpp"
#include <algorithm>
#include <cassert>

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        best = 0;
        depth(root);
        return best;
    }
private:
    int depth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        int left = depth(root->left);
        int right = depth(root->right);

        best = std::max(left + right, best);
        return 1 + std::max(left, right);
    }

    int best = 0;
};

int main() {
	Solution s;

	// пустое
	assert(s.diameterOfBinaryTree(nullptr) == 0);

	// один узел
	{
		TreeNode root(1);
		assert(s.diameterOfBinaryTree(&root) == 0);
	}

	// два узла — диаметр 1 ребро
	{
		TreeNode n2(2);
		TreeNode root(1, &n2, nullptr);
		assert(s.diameterOfBinaryTree(&root) == 1);
	}

	// классический пример [1,2,3,4,5]
	//        1
	//       / \
	//      2   3
	//     / \
	//    4   5
	// Самый длинный путь: 4 → 2 → 1 → 3 (3 ребра).
	{
		TreeNode n4(4), n5(5);
		TreeNode n2(2, &n4, &n5), n3(3);
		TreeNode root(1, &n2, &n3);
		assert(s.diameterOfBinaryTree(&root) == 3);
	}

	// путь НЕ через корень
	//        1
	//       /
	//      2
	//     / \
	//    3   4
	//   /     \
	//  5       6
	// Самый длинный: 5 → 3 → 2 → 4 → 6 (4 ребра).
	{
		TreeNode n5(5), n6(6);
		TreeNode n3(3, &n5, nullptr), n4(4, nullptr, &n6);
		TreeNode n2(2, &n3, &n4);
		TreeNode root(1, &n2, nullptr);
		assert(s.diameterOfBinaryTree(&root) == 4);
	}

	// вырожденное (список)
	{
		TreeNode n4(4);
		TreeNode n3(3, &n4, nullptr);
		TreeNode n2(2, &n3, nullptr);
		TreeNode root(1, &n2, nullptr);
		assert(s.diameterOfBinaryTree(&root) == 3);
	}

	// симметричное сбалансированное
	{
		TreeNode n4(4), n5(5), n6(6), n7(7);
		TreeNode n2(2, &n4, &n5), n3(3, &n6, &n7);
		TreeNode root(1, &n2, &n3);
		assert(s.diameterOfBinaryTree(&root) == 4);
	}

	return 0;
}
