class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def reverseList(head: ListNode) -> ListNode:
    previous = None
    current = head
    while current:
        temp = current.next
        current.next = previous

        previous = current
        current = temp
    return previous

def mergeTwoSortedLists(list1: ListNode, list2: ListNode):
    dummy = ListNode()
    current = dummy
    while list1 and list2:
        if list1.val < list2.val:
            current.next = list1
            list1 = list1.next
        else:
            current.next = list2
            list2 = list2.next
        current = current.next
    if list1:
        current.next = list1
    elif list2:
        current.next = list2
    return dummy.next

