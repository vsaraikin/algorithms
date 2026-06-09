#include "../../../lib/cpp/node.cpp"
#include <cassert>
#include <queue>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        std::vector<std::vector<int>> res;
        std::queue<TreeNode*> q;
        if (!root) {
            return res;
        }
        q.push(root);
        while (!q.empty()) {
            std::vector<int> lvl;
            size_t n = q.size();
            for (int i = 0; i < n; ++i) {
                TreeNode *el = q.front(); q.pop();
                lvl.push_back(el->val);
                if (el->left) {
                    q.push(el->left);
                }
                if (el->right) {
                    q.push(el->right);
                }
            }
            res.push_back(std::move(lvl));
        }
        return res;
    }
};

int main() {
	Solution s;

	// пустое
	assert(s.levelOrder(nullptr) == (std::vector<std::vector<int>>{}));

	// один узел
	{
		TreeNode root(1);
		assert(s.levelOrder(&root) == (std::vector<std::vector<int>>{{1}}));
	}

	// классический [3, 9, 20, null, null, 15, 7]
	//        3
	//       / \
	//      9  20
	//         / \
	//        15  7
	{
		TreeNode n15(15), n7(7);
		TreeNode n9(9), n20(20, &n15, &n7);
		TreeNode root(3, &n9, &n20);
		assert(s.levelOrder(&root) ==
		       (std::vector<std::vector<int>>{{3}, {9, 20}, {15, 7}}));
	}

	// несимметричное
	//        1
	//       / \
	//      2   3
	//     /     \
	//    4       5
	{
		TreeNode n4(4), n5(5);
		TreeNode n2(2, &n4, nullptr), n3(3, nullptr, &n5);
		TreeNode root(1, &n2, &n3);
		assert(s.levelOrder(&root) ==
		       (std::vector<std::vector<int>>{{1}, {2, 3}, {4, 5}}));
	}

	// вырожденное вправо
	{
		TreeNode n3(3);
		TreeNode n2(2, nullptr, &n3);
		TreeNode root(1, nullptr, &n2);
		assert(s.levelOrder(&root) ==
		       (std::vector<std::vector<int>>{{1}, {2}, {3}}));
	}

	// идеальное
	//        1
	//      /   \
	//     2     3
	//    / \   / \
	//   4   5 6   7
	{
		TreeNode n4(4), n5(5), n6(6), n7(7);
		TreeNode n2(2, &n4, &n5), n3(3, &n6, &n7);
		TreeNode root(1, &n2, &n3);
		assert(s.levelOrder(&root) ==
		       (std::vector<std::vector<int>>{
		           {1}, {2, 3}, {4, 5, 6, 7}}));
	}

	return 0;
}
