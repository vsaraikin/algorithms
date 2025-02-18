from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
        
class Solution:
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        prehead = ListNode(-1)
        curr = prehead
        while list1 and list2:
            if list1.val < list2.val:
                curr.next = list1
                list1 = list1.next
            else:
                curr.next = list2
                list2 = list2.next
            curr = curr.next
        curr.next = list1 if list1 else list2
        return prehead.next
        
            
def list_to_linked_list(lst):
    if not lst:
        return None
    head = ListNode(lst[0])
    curr = head
    for val in lst[1:]:
        curr.next = ListNode(val)
        curr = curr.next
    return head

def linked_list_to_list(head):
    result = []
    while head:
        result.append(head.val)
        head = head.next
    return result

def test_merge_two_sorted_lists():
    sol = Solution()

    # Test 1: Normal case
    l1 = list_to_linked_list([1, 2, 4])
    l2 = list_to_linked_list([1, 3, 4])
    result = sol.mergeTwoLists(l1, l2)
    assert linked_list_to_list(result) == [1, 1, 2, 3, 4, 4]

    # Test 2: One empty list
    l1 = list_to_linked_list([])
    l2 = list_to_linked_list([1, 3, 5])
    result = sol.mergeTwoLists(l1, l2)
    assert linked_list_to_list(result) == [1, 3, 5]

    # Test 3: Both lists empty
    l1 = list_to_linked_list([])
    l2 = list_to_linked_list([])
    result = sol.mergeTwoLists(l1, l2)
    assert linked_list_to_list(result) == []

    # Test 4: Lists with different lengths
    l1 = list_to_linked_list([2])
    l2 = list_to_linked_list([1, 3, 4, 5])
    result = sol.mergeTwoLists(l1, l2)
    assert linked_list_to_list(result) == [1, 2, 3, 4, 5]

    # Test 5: Lists with same elements
    l1 = list_to_linked_list([2, 2, 2])
    l2 = list_to_linked_list([2, 2, 2])
    result = sol.mergeTwoLists(l1, l2)
    assert linked_list_to_list(result) == [2, 2, 2, 2, 2, 2]

    print("All test cases passed!")

test_merge_two_sorted_lists()