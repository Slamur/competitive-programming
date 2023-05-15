/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func len(head* ListNode) int {
    n := 0
    for cur := head; cur != nil; cur = cur.Next {
        n++
    }
    return n
}

func get(head* ListNode, need int) *ListNode {
    cur := head
    for pos := 1; pos < need; pos++ {
        cur = cur.Next
    }
    return cur
}

func swapNodes(head *ListNode, k int) *ListNode {
    n := len(head)

    left := get(head, k)
    right := get(head, n - k + 1)

    left.Val, right.Val = right.Val, left.Val

    return head
}
