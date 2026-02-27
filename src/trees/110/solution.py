from node import TreeNode
from typing import Optional

class Solution:
    def isBalanced(self, root: Optional[TreeNode]) -> bool:
        ans = True
        def maxDepth(self, root: Optional[TreeNode]) -> int:
            if not root or not ans:
                return 0

            left = self.maxDepth(root.left)
            right = self.maxDepth(root.right)
            
            if abs(right - left) > 1:
                ans = False

            return max(left, right) + 1
        maxDepth(root)
        return ans