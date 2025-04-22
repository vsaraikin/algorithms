from typing import Optional
from heapq import heappop, heappush

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def mergeKLists(self, lists: list[Optional[ListNode]]) -> Optional[ListNode]:
        heap = []
        for i, node in enumerate(lists):
            if node:
                heappush(heap, (node.val, i, node))
        
        head = ListNode(0)
        curr = head
        while heap:
            val, i, node = heappop(heap)
            curr.next = node
            curr = curr.next
            if node.next:
                heappush(heap, (node.next.val, i, node.next))
        return head.next
            
    
# Helper function to convert a list of lists into linked lists
def list_to_linked_lists(lists):
    linked_lists = []
    for lst in lists:
        dummy = ListNode(0)
        current = dummy
        for val in lst:
            current.next = ListNode(val)
            current = current.next
        linked_lists.append(dummy.next)
    return linked_lists

# Helper function to convert a linked list to a Python list
def linked_list_to_list(head):
    result = []
    while head:
        result.append(head.val)
        head = head.next
    return result

# Testing function for LeetCode 23: Merge k Sorted Lists
def test_merge_k_sorted_lists():
    sol = Solution()

    # Test 1: General case with multiple lists
    lists = [
        [1, 4, 5],
        [1, 3, 4],
        [2, 6]
    ]
    linked_lists = list_to_linked_lists(lists)
    merged_head = sol.mergeKLists(linked_lists)
    assert linked_list_to_list(merged_head) == [1, 1, 2, 3, 4, 4, 5, 6]

    # # Test 2: Single list
    # lists = [
    #     [1, 2, 3]
    # ]
    # linked_lists = list_to_linked_lists(lists)
    # merged_head = sol.mergeKLists(linked_lists)
    # assert linked_list_to_list(merged_head) == [1, 2, 3]

    # # Test 3: Multiple empty lists
    # lists = [
    #     [],
    #     [],
    #     []
    # ]
    # linked_lists = list_to_linked_lists(lists)
    # merged_head = sol.mergeKLists(linked_lists)
    # assert linked_list_to_list(merged_head) == []

    # # Test 4: One empty list and others non-empty
    # lists = [
    #     [],
    #     [1, 3, 5],
    #     []
    # ]
    # linked_lists = list_to_linked_lists(lists)
    # merged_head = sol.mergeKLists(linked_lists)
    # assert linked_list_to_list(merged_head) == [1, 3, 5]

    # # Test 5: Lists with one element each
    # lists = [
    #     [1],
    #     [2],
    #     [3]
    # ]
    # linked_lists = list_to_linked_lists(lists)
    # merged_head = sol.mergeKLists(linked_lists)
    # assert linked_list_to_list(merged_head) == [1, 2, 3]

    # # Test 6: All lists empty
    # lists = []
    # linked_lists = list_to_linked_lists(lists)
    # merged_head = sol.mergeKLists(linked_lists)
    # assert linked_list_to_list(merged_head) == []

    print("All test cases passed!")

# Run the tests
test_merge_k_sorted_lists()