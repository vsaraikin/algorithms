from node import ListNode

class LinkedList:
    """
    A utility class for creating and manipulating linked lists.
    """

    def __init__(self, values=None):
        """
        Initializes the LinkedList.
        
        Parameters:
            values (list, optional): A list of values to create the linked list from.
        """
        if values is not None:
            self.head = self.from_list(values)
        else:
            self.head = None

    @staticmethod
    def from_list(values):
        """
        Build a linked list from a given Python list.

        Parameters:
            values (list): A list of values.

        Returns:
            ListNode: The head of the linked list.
        """
        dummy = ListNode(0)
        current = dummy
        for value in values:
            current.next = ListNode(value)
            current = current.next
        return dummy.next

    def to_list(self):
        """
        Convert the linked list back to a Python list.

        Returns:
            list: A list of node values.
        """
        result = []
        current = self.head
        while current:
            result.append(current.val)
            current = current.next
        return result

    def __repr__(self):
        return f"LinkedList({self.to_list()})"