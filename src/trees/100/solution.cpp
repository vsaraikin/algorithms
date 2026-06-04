#include "../../../lib/cpp/node.cpp"
#include <cassert>

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q) {
            return true;
        }
        if (!p || !q) {
            return false;
        }
        if (p->val != q->val) {
            return false;
        }
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

int main() {
    Solution s;

    // both empty
    assert(s.isSameTree(nullptr, nullptr) == true);

    // one empty, one not
    TreeNode a1(1);
    assert(s.isSameTree(&a1, nullptr) == false);
    assert(s.isSameTree(nullptr, &a1) == false);

    // identical: [1,2,3]
    TreeNode b_l(2), b_r(3), b_root(1, &b_l, &b_r);
    TreeNode c_l(2), c_r(3), c_root(1, &c_l, &c_r);
    assert(s.isSameTree(&b_root, &c_root) == true);

    // same shape, different value
    TreeNode d_l(2), d_r(4), d_root(1, &d_l, &d_r);
    assert(s.isSameTree(&b_root, &d_root) == false);

    // different shape: [1,2] vs [1,null,2]
    TreeNode e_l(2), e_root(1, &e_l, nullptr);
    TreeNode f_r(2), f_root(1, nullptr, &f_r);
    assert(s.isSameTree(&e_root, &f_root) == false);

    return 0;
}