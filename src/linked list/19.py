from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        fast = slow = head
        
        for _ in range(n):
            fast = fast.next
            
        if not fast:
            return head.next
        
        while fast.next:
            fast = fast.next
            slow = slow.next
        
        slow.next = slow.next.next
        return head

# Helper function to convert a list to a linked list
def list_to_linked_list(lst):
    if not lst:
        return None
    head = ListNode(lst[0])
    curr = head
    for val in lst[1:]:
        curr.next = ListNode(val)
        curr = curr.next
    return head

# Helper function to convert a linked list back to a list
def linked_list_to_list(head):
    result = []
    while head:
        result.append(head.val)
        head = head.next
    return result

# Testing function for LeetCode 19: Remove Nth Node From End
def test_remove_nth_from_end():
    sol = Solution()

    # Test 1: Remove 2nd node from end
    lst = [1, 2, 3, 4, 5]
    head = list_to_linked_list(lst)
    new_head = sol.removeNthFromEnd(head, 2)
    assert linked_list_to_list(new_head) == [1, 2, 3, 5]

    # Test 2: Remove last node
    lst = [1, 2, 3]
    head = list_to_linked_list(lst)
    new_head = sol.removeNthFromEnd(head, 1)
    assert linked_list_to_list(new_head) == [1, 2]

    # Test 3: Remove first node
    lst = [1, 2, 3, 4]
    head = list_to_linked_list(lst)
    new_head = sol.removeNthFromEnd(head, 4)
    assert linked_list_to_list(new_head) == [2, 3, 4]

    # Test 4: Single node list (remove the only node)
    lst = [1]
    head = list_to_linked_list(lst)
    new_head = sol.removeNthFromEnd(head, 1)
    assert linked_list_to_list(new_head) == []

    # Test 5: Two-node list (remove first node)
    lst = [1, 2]
    head = list_to_linked_list(lst)
    new_head = sol.removeNthFromEnd(head, 2)
    assert linked_list_to_list(new_head) == [2]

    # Test 6: Two-node list (remove last node)
    lst = [1, 2]
    head = list_to_linked_list(lst)
    new_head = sol.removeNthFromEnd(head, 1)
    assert linked_list_to_list(new_head) == [1]

    print("All test cases passed!")
    
test_remove_nth_from_end()