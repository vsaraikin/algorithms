from node import TreeNode
from typing import Optional

class Solution:
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        ans = 0
        def helper(root: Optional[TreeNode]):
            nonlocal ans
            if not root:
                return 0
            
            l = helper(root.left)
            r = helper(root.right)
            ans = max(l + r, ans)
            return 1 + max(l, r)
        helper(root)
        return ans