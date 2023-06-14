/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func minDiffInBST(root *TreeNode) int {
    values := make([]int, 0)

    var dfs func(*TreeNode) 

    dfs = func(node *TreeNode) {
        if node == nil {
            return
        }

        values = append(values, node.Val)

        dfs(node.Left)
        dfs(node.Right)
    }

    dfs(root)

    sort.Ints(values)

    ans := int(1e9)
    for i := 1; i < len(values); i++ {
        if ans > values[i] - values[i - 1] {
            ans = values[i] - values[i - 1]
        }
    }

    return ans
}
