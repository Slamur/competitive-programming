/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
import (
    "math"
)

func maxLevelSum(root *TreeNode) int {
    levelSums := make(map[int]int)

    var dfs func(node *TreeNode, level int)
    dfs = func(node *TreeNode, level int) {
        if node == nil {
            return
        }

        levelSums[level] += node.Val

        dfs(node.Left, level + 1)
        dfs(node.Right, level + 1)
    }

    dfs(root, 1)

    bestLevel, bestSum := 0, math.MinInt

    for level, levelSum := range levelSums {
        if bestSum < levelSum {
            bestSum = levelSum
            bestLevel = level
        }
    }

    return bestLevel
}
