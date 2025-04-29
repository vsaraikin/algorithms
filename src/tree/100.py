from typing import Optional
from node import TreeNode

class Solution:
    def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
        if not p or not q:
            return p == q
            
        return (p.val == q.val) and self.isSameTree(p.left, q.left) and self.isSameTree(p.right, q.right)
    
sol = Solution()


# Test 1: Both trees are empty.
assert sol.isSameTree(None, None) == True, "Test 1 failed: Both trees are None."

# Test 2: Single-node trees with the same value.
tree1 = TreeNode(1)
tree2 = TreeNode(1)
assert sol.isSameTree(tree1, tree2) == True, "Test 2 failed: Single-node trees should be the same."

# Test 3: Identical trees with multiple nodes.
#       Tree structure:
#             1
#            / \
#           2   3
tree1 = TreeNode(1, TreeNode(2), TreeNode(3))
tree2 = TreeNode(1, TreeNode(2), TreeNode(3))
assert sol.isSameTree(tree1, tree2) == True, "Test 3 failed: Identical trees should match."

# Test 4: Trees that have the same structure but different node values.
#       Tree1:      1           Tree2:      1
#                 /   \                  /   \
#                2     1                1     2
tree1 = TreeNode(1, TreeNode(2), TreeNode(1))
tree2 = TreeNode(1, TreeNode(1), TreeNode(2))
assert sol.isSameTree(tree1, tree2) == False, "Test 4 failed: Trees with different node values should not match."

# Test 5: Trees with different structures.
#       Tree1:      1             Tree2:      1
#                /                          \
#               2                            2
tree1 = TreeNode(1, TreeNode(2))
tree2 = TreeNode(1, None, TreeNode(2))
assert sol.isSameTree(tree1, tree2) == False, "Test 5 failed: Trees with different structures should not match."

print("All tests passed!")

