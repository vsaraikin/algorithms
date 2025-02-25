from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def reorderList(self, head: Optional[ListNode]) -> None:
        if not head or not head.next or not head.next.next:
            return

        fast, slow = head, head
        while fast and fast.next:
            fast = fast.next.next
            slow = slow.next

        prev, curr = None, slow.next
        slow.next = None

        while curr:
            temp = curr.next
            curr.next = prev
            prev = curr
            curr = temp

        first, second = head, prev
        while second:
            temp1, temp2 = first.next, second.next
            first.next = second
            second.next = temp1
            first, second = temp1, temp2
            


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

# Testing function for 143. Reorder List
def test_reorder_list():
    sol = Solution()

    # Test 1: Even number of nodes
    lst = [1, 2, 3, 4]
    head = list_to_linked_list(lst)
    sol.reorderList(head)
    assert linked_list_to_list(head) == [1, 4, 2, 3]

    # Test 2: Odd number of nodes
    lst = [1, 2, 3, 4, 5]
    head = list_to_linked_list(lst)
    sol.reorderList(head)
    assert linked_list_to_list(head) == [1, 5, 2, 4, 3]

    # Test 3: Single node (should remain the same)
    lst = [1]
    head = list_to_linked_list(lst)
    sol.reorderList(head)
    assert linked_list_to_list(head) == [1]

    # Test 4: Two nodes (should remain the same)
    lst = [1, 2]
    head = list_to_linked_list(lst)
    sol.reorderList(head)
    assert linked_list_to_list(head) == [1, 2]

    # Test 5: Three nodes
    lst = [1, 2, 3]
    head = list_to_linked_list(lst)
    sol.reorderList(head)
    assert linked_list_to_list(head) == [1, 3, 2]

    # Test 6: Empty list (should remain empty)
    lst = []
    head = list_to_linked_list(lst)
    sol.reorderList(head)
    assert linked_list_to_list(head) == []

    print("All test cases passed!")

# Run the tests
test_reorder_list()
    
