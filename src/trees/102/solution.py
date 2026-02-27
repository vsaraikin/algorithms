from typing import Optional
from node import TreeNode
from collections import deque

class Solution:
    def levelOrder(self, root: Optional[TreeNode]) -> list[list[int]]:
        if not root:
            return []
        
        queue = deque([root])
        result = []
        
        while queue:
            levels = []
            level_size = len(queue)
            
            for _ in range(level_size):
                node = queue.popleft()
                levels.append(node.val)
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)

            result.append(levels)
        return result