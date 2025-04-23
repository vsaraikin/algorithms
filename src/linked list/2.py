from typing import Optional

from node import ListNode
from linked_list import LinkedList

class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0)
        current = dummy
        carry = 0
        while l1 or l2 or carry:
            val1 = l1.val if l1 else 0
            val2 = l2.val if l2 else 0
            total = val1 + val2 + carry
            val = total % 10
            carry = total // 10
            current.next = ListNode(val)
            
            current = current.next
            l1 = l1.next if l1 else None
            l2 = l2.next if l2 else None


        return dummy.next

s = Solution()
result_ll = LinkedList()
result_ll.head = s.addTwoNumbers(
    LinkedList([2, 4, 3]).head, LinkedList([5, 6, 4]).head
)
assert result_ll.to_list() == LinkedList([7, 0, 8]).to_list()

print("Test passed.")