from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        count = 0
        node = head
        while node and count < k:
            node = node.next
            count += 1
            
        if count < k:
            return head
        
        new_head = self._reverse(head, node)
        head.next = self.reverseKGroup(node, k)
        return new_head
    
    def _reverse(self, head: Optional[ListNode], tail: Optional[ListNode]) -> ListNode:
        prev = None
        curr = head
        
        while curr != tail:
            next_node = curr.next
            curr.next = prev
            prev = curr
            curr = next_node

        return prev
    