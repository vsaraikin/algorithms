#include "../../../lib/cpp/node.cpp"


class Solution {
public:
    int goodNodes(TreeNode* root) { 
        return bfs(root, root->val);
    }

    int bfs(TreeNode* node, int max_so_far) {
        if (!node) {
            return 0;
        }

        int good = 1 ? node->val >= max_so_far : 0;
        max_so_far = std::max(max_so_far, node->val);


        return good + bfs(node->left, max_so_far) + bfs(node->right, max_so_far);
    }
};