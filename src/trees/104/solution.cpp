#include "../../../lib/cpp/node.cpp"
#include <algorithm>
#include <cassert>

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }
        return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
    }
};

int main() {
	Solution s;

	// пустое дерево
	assert(s.maxDepth(nullptr) == 0);

	// один узел
	{
		TreeNode root(1);
		assert(s.maxDepth(&root) == 1);
	}

	// сбалансированное [3,9,20,null,null,15,7]
	{
		TreeNode n15(15), n7(7);
		TreeNode n9(9), n20(20, &n15, &n7);
		TreeNode root(3, &n9, &n20);
		assert(s.maxDepth(&root) == 3);
	}

	// вырожденное влево: 1 → 2 → 3 → 4 → 5
	{
		TreeNode n5(5);
		TreeNode n4(4, &n5, nullptr);
		TreeNode n3(3, &n4, nullptr);
		TreeNode n2(2, &n3, nullptr);
		TreeNode root(1, &n2, nullptr);
		assert(s.maxDepth(&root) == 5);
	}

	// вырожденное вправо
	{
		TreeNode n5(5);
		TreeNode n4(4, nullptr, &n5);
		TreeNode n3(3, nullptr, &n4);
		TreeNode n2(2, nullptr, &n3);
		TreeNode root(1, nullptr, &n2);
		assert(s.maxDepth(&root) == 5);
	}

	// несимметричное
	{
		TreeNode n4(4), n5(5);
		TreeNode n2(2, &n4, nullptr);
		TreeNode n3(3, nullptr, &n5);
		TreeNode root(1, &n2, &n3);
		assert(s.maxDepth(&root) == 3);
	}

	// два узла
	{
		TreeNode n2(2);
		TreeNode root(1, &n2, nullptr);
		assert(s.maxDepth(&root) == 2);
	}

	return 0;
}
