from typing import Optional
from node import TreeNode


class Solution:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        def helper(node: Optional[TreeNode], low: int, high: int) -> bool:
            if not node:
                return True
            val = node.val
            if not (low < val < high):
                return False

            return helper(node.left, low, val) and helper(node.right, val, high)
            
        return helper(root, float('-inf'), float('inf'))