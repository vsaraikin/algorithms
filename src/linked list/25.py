from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        dummy = ListNode(0)
        dummy.next = head
        group_prev = dummy
        
        def get_kth_node(curr: ListNode, k: int):
            while curr and k > 0:
                curr = curr.next
                k -= 1
            return curr
    
        while True:
            kth = get_kth_node(group_prev, k)
            if not kth:
                break
        
            group_next = kth.next
            prev, curr = kth.next, group_prev.next
            while curr != group_next:
                temp = curr.next
                curr.next = prev
                prev = curr
                curr = temp
            
            temp = group_next.next
            group_prev.next = kth
            group_prev = temp

        return dummy.next

# Helper function to convert list to linked list
def list_to_linked_list(lst):
    dummy = ListNode(0)
    curr = dummy
    for val in lst:
        curr.next = ListNode(val)
        curr = curr.next
    return dummy.next

# Helper function to convert linked list to list
def linked_list_to_list(head):
    result = []
    while head:
        result.append(head.val)
        head = head.next
    return result

# Testing function for LeetCode 25: Reverse Nodes in k-Group
def test_reverse_k_group():
    sol = Solution()

    # Test 1: Standard reversal in pairs
    head = list_to_linked_list([1, 2, 3, 4, 5])
    result = sol.reverseKGroup(head, 2)
    assert linked_list_to_list(result) == [2, 1, 4, 3, 5]

    # Test 2: Reversal in groups of 3
    head = list_to_linked_list([1, 2, 3, 4, 5])
    result = sol.reverseKGroup(head, 3)
    assert linked_list_to_list(result) == [3, 2, 1, 4, 5]

    # Test 3: k is 1 (no change)
    head = list_to_linked_list([1, 2, 3])
    result = sol.reverseKGroup(head, 1)
    assert linked_list_to_list(result) == [1, 2, 3]

    # Test 4: k equals length of list
    head = list_to_linked_list([1, 2, 3, 4])
    result = sol.reverseKGroup(head, 4)
    assert linked_list_to_list(result) == [4, 3, 2, 1]

    # Test 5: k greater than length (no change)
    head = list_to_linked_list([1, 2])
    result = sol.reverseKGroup(head, 3)
    assert linked_list_to_list(result) == [1, 2]

    # Test 6: Empty list
    head = list_to_linked_list([])
    result = sol.reverseKGroup(head, 2)
    assert linked_list_to_list(result) == []

    print("All test cases passed!")

# Run the tests
test_reverse_k_group()