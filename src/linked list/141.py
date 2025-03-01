class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def hasCycle(self, head: ListNode) -> bool:
        if not head or not head.next:
            return False  # Empty list or single node without cycle

        slow = head
        fast = head

        while fast and fast.next:
            slow = slow.next        # Move slow by 1 step
            fast = fast.next.next   # Move fast by 2 steps

            if slow == fast:
                return True  # Cycle detected

        return False  # No cycle found