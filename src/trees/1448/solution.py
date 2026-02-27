from node import TreeNode
from typing import Optional

class Solution:
    def goodNodes(self, root: TreeNode) -> int:
        def dfs(node: TreeNode | None, max_value: int) -> int:
            if not node:
                return 0
            
            count = 1 if node.val >= max_value else 0
            max_value = max(max_value, node.val)
            
            count += dfs(node.left, max_value)
            count += dfs(node.right, max_value)
            return count
        
        return dfs(root, root.val)
            