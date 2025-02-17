class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
        
class Solution:
    def reverseList(self, head: ListNode) -> ListNode:
        prev = None
        curr = head

        while curr:
            next_node = curr.next
            curr.next = prev
            prev = curr
            curr = next_node
        return prev



solution = Solution()

some_node = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
result = solution.reverseList(some_node)
assert result.val == 5
assert result.next.val == 4
assert result.next.next.val == 3
assert result.next.next.next.val == 2
assert result.next.next.next.next.val == 1
assert result.next.next.next.next.next is None
