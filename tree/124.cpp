#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "tree.h"
using namespace std;

/**
 * 124: 二叉树中的最大路径和
 * 二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。
 * 同一个节点在一条路径序列中 至多出现一次 。
 * 该路径 至少包含一个 节点，且不一定经过根节点。
 * 路径和 是路径中各节点值的总和。
 *
 * 给你一个二叉树的根节点 root ，返回其 最大路径和 。
 * https://leetcode.cn/problems/binary-tree-maximum-path-sum/description
 */
typedef TreeNode Node;
class Solution {
   private:
    int maxSum = INT_MIN;

   public:
    int maxPathSum(TreeNode* root) {
        maxGain(root);
        return maxSum;
    }
    // 求节点的最大贡献值
    int maxGain(TreeNode* node) {
        if (node == nullptr) return 0;

        // 递归计算左右 子节点的 最大贡献值
        int leftGain = max(maxGain(node->left), 0);
        int rightGain = max(maxGain(node->right), 0);
        // 节点的最大路径和 = 节点值 + 左孩子贡献值 + 右孩子贡献值
        int nodeGain = node->val + leftGain + rightGain;
        // 更新答案
        maxSum = max(maxSum, nodeGain);
        // 返回该节点的最大贡献值
        return node->val + max(leftGain, rightGain);
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{1, 2, 3}, {-10, 9, 20, null, null, 15, 7}};
    for (auto& i : arr) {
        auto ans = s->maxPathSum(new TreeNode(i));
        cout << ans << endl;
    }
}