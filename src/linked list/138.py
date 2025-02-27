from typing import Optional

class Node:
    def __init__(self, val=0, next=None, random=None):
        self.val = val
        self.next = next
        self.random = random


class Solution:
    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        if not head:
            return None

        old_to_new = {}
        curr = head
        while curr:
            old_to_new[curr] = Node(curr.val)
            curr = curr.next

        curr = head
        while curr:
            old_to_new[curr].next = old_to_new.get(curr.next)
            old_to_new[curr].random = old_to_new.get(curr.random)
            curr = curr.next
        return old_to_new[head]
    
    
    # Helper function to convert a list representation into a linked list with random pointers
def list_to_linked_list_with_random(lst):
    if not lst:
        return None
    
    nodes = [Node(val) for val, _ in lst]
    
    # Set next pointers
    for i in range(len(lst) - 1):
        nodes[i].next = nodes[i + 1]
    
    # Set random pointers
    for i, (_, random_index) in enumerate(lst):
        if random_index is not None:
            nodes[i].random = nodes[random_index]
    
    return nodes[0]

# Helper function to convert a linked list with random pointers back to a list representation
def linked_list_to_list_with_random(head):
    if not head:
        return []
    
    node_to_index = {}
    curr = head
    index = 0

    # First pass: Store node indices
    while curr:
        node_to_index[curr] = index
        curr = curr.next
        index += 1

    # Second pass: Create list representation
    result = []
    curr = head
    while curr:
        random_index = node_to_index[curr.random] if curr.random else None
        result.append((curr.val, random_index))
        curr = curr.next
    
    return result

# Testing function for LeetCode 138: Copy List with Random Pointer
def test_copy_random_list():
    sol = Solution()

    # Test 1: General case with random pointers
    lst = [(7, None), (13, 0), (11, 4), (10, 2), (1, 0)]
    head = list_to_linked_list_with_random(lst)
    copied_head = sol.copyRandomList(head)
    assert linked_list_to_list_with_random(copied_head) == lst

    # Test 2: Single node with no random pointer
    lst = [(1, None)]
    head = list_to_linked_list_with_random(lst)
    copied_head = sol.copyRandomList(head)
    assert linked_list_to_list_with_random(copied_head) == lst

    # Test 3: Single node with random pointer to itself
    lst = [(1, 0)]
    head = list_to_linked_list_with_random(lst)
    copied_head = sol.copyRandomList(head)
    assert linked_list_to_list_with_random(copied_head) == lst

    # Test 4: Two nodes with cross random pointers
    lst = [(1, 1), (2, 0)]
    head = list_to_linked_list_with_random(lst)
    copied_head = sol.copyRandomList(head)
    assert linked_list_to_list_with_random(copied_head) == lst

    # Test 5: Empty list (should return empty list)
    lst = []
    head = list_to_linked_list_with_random(lst)
    copied_head = sol.copyRandomList(head)
    assert linked_list_to_list_with_random(copied_head) == lst

    print("All test cases passed!")

# Run the tests
test_copy_random_list()