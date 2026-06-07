#include "../../../lib/cpp/node.cpp"
#include <algorithm>
#include <cassert>
#include <cmath>

class Solution {
public:
    bool isBalanced(TreeNode* root) { return check(root) != -1; }

    int check(TreeNode* root) {
        if (!root) {
            return 0;
        }

        int left = check(root->left);
        if (left == -1) {
            return -1;
        }

        int right = check(root->right);
        if (right == -1) {
            return -1;
        }

        if (std::abs(left - right) > 1) {
            return -1;
        }

        return 1 + std::max(left, right);
    }
};

int main() {
	Solution s;

	// пустое
	assert(s.isBalanced(nullptr) == true);

	// один узел
	{
		TreeNode root(1);
		assert(s.isBalanced(&root) == true);
	}

	// сбалансированное [3,9,20,null,null,15,7]
	{
		TreeNode n15(15), n7(7);
		TreeNode n9(9), n20(20, &n15, &n7);
		TreeNode root(3, &n9, &n20);
		assert(s.isBalanced(&root) == true);
	}

	// несбалансированное: левая ветка глубокая
	// [1,2,2,3,3,null,null,4,4]
	{
		TreeNode n4a(4), n4b(4);
		TreeNode n3a(3, &n4a, &n4b), n3b(3);
		TreeNode n2a(2, &n3a, &n3b), n2b(2);
		TreeNode root(1, &n2a, &n2b);
		assert(s.isBalanced(&root) == false);
	}

	// вырожденное (по сути список)
	{
		TreeNode n4(4);
		TreeNode n3(3, &n4, nullptr);
		TreeNode n2(2, &n3, nullptr);
		TreeNode root(1, &n2, nullptr);
		assert(s.isBalanced(&root) == false);
	}

	// разница ровно 1 в одном месте — ок
	{
		TreeNode n2(2);
		TreeNode root(1, &n2, nullptr);
		assert(s.isBalanced(&root) == true);
	}

	// глубина 1 у одного, 3 у другого → разница > 1
	{
		TreeNode n5(5);
		TreeNode n4(4, &n5, nullptr);
		TreeNode n3(3, &n4, nullptr);
		TreeNode n2(2);
		TreeNode root(1, &n3, &n2);
		assert(s.isBalanced(&root) == false);
	}

	// идеально сбалансированное полное дерево
	{
		TreeNode n4(4), n5(5), n6(6), n7(7);
		TreeNode n2(2, &n4, &n5), n3(3, &n6, &n7);
		TreeNode root(1, &n2, &n3);
		assert(s.isBalanced(&root) == true);
	}

	return 0;
}
