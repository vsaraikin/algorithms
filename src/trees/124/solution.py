from typing import Optional
from node import TreeNode


class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        self.result = float('-inf')

        def dfs(node: TreeNode | None):
            if not node:
                return 0
            
            left_max = max(0, dfs(node.left))
            right_max = max(0, dfs(node.right))
            self.result = max(self.result, node.val + left_max + right_max)
            return node.val + max(left_max, right_max)
        
        dfs(root)
        return self.result