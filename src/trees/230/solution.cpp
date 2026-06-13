

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        if (!root) {
            return 0;
        }
        count = k;
        dfs(root);
        return result;
    }

    void dfs(TreeNode* node) {
        if (!node || count == 0) {
            return;
        }

        dfs(node->left);
        if (--count == 0) {
            result = node->val;
            return;
        }
        dfs(node->right);
    }

private:
    int count = 0;
    int result = 0;
};