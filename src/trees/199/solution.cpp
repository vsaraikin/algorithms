#include <vector>
#include <queue>
#include "../../../lib/cpp/node.cpp"


class Solution {
public:
    std::vector<int> rightSideView(TreeNode* root) {
        std::queue<TreeNode*> q;
        std::vector<int> res;
        if (!root) {
            return res;
        }

        q.push(root);
        while(!q.empty()) {
            size_t n = q.size();
            for (int i = 0; i < n; ++i) {
                TreeNode* node = q.front(); q.pop();
                if (i == n - 1) {
                    res.push_back(node->val);
                }
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
        }
        return res;
    }
};