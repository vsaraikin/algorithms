from typing import Optional
from node import TreeNode

class Solution:
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0

        left = self.maxDepth(root.left)
        right = self.maxDepth(root.right)

        return max(left, right) + 1
    
    
root = TreeNode(3)
root.left = TreeNode(9)
root.right = TreeNode(20, TreeNode(15), TreeNode(7))

sol = Solution()
assert sol.maxDepth(root) == 3, f"Expected depth 3, but got {sol.maxDepth(root)}"

print("Test passed!")