/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func swapPairs(head *ListNode) *ListNode {
    root := &ListNode {
        Val: -1,
        Next: head,
    }

    for cur := root; cur.Next != nil && cur.Next.Next != nil; cur = cur.Next.Next {
        left := cur.Next
        right := left.Next

        left.Next = right.Next
        right.Next = left
        cur.Next = right
    }

    return root.Next
}
