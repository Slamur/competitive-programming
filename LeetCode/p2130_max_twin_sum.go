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
    for pos := 0; pos < need; pos++ {
        cur = cur.Next
    }
    return cur
}

func reverse(start *ListNode, end *ListNode) *ListNode {
    var cur *ListNode = nil
    next := start
    for ; next != end; {
        nextNext := next.Next
        next.Next = cur
        cur, next = next, nextNext
    }

    return cur
}

func pairSum(head *ListNode) int {
    n := len(head)

    rightStart := get(head, n / 2)
    leftStart := reverse(head, rightStart)

    ans := 0
    for left, right := leftStart, rightStart; left != nil; left, right = left.Next, right.Next {
        sum := left.Val + right.Val
        if ans < sum {
            ans = sum
        }
    }
    return ans
}
