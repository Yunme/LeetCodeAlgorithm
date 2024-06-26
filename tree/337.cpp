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

#include "../tree/tree.h"
using namespace std;

/**
 * 337: 打家劫舍 III
 * 小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为 root 。
 * 除了 root
 * 之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。
 * 如果 两个直接相连的房子在同一天晚上被打劫 ，房屋将自动报警。 给定二叉树的
 * root 。返回 在不触动警报的情况下 ，小偷能够盗取的最高金额 。
 *
 * https://leetcode.cn/problems/house-robber-iii/description/
 */
class Solution {
   public:
    /**
     * DFS
     * 抽象为：每个子树的最大权值，父子结点不能同时选择
     * 选择根结点 i 的最大权值 f(i), 不选择根结点 i 的最大权值为 g(i)
     * f(i) = val(i) + g(lc) + g(rc)
     * // 不选i，子孩子可以选和不选，取选和不选中的较大值
     * g(i) = max(f(lc), g(lc)) + max(f(rc), g(rc))
     */
    void dfs(unordered_map<TreeNode*, int>& fMap,
             unordered_map<TreeNode*, int>& gMap, TreeNode* treeNode) {
        if (treeNode == nullptr) return;
        // 后序遍历  状态从后向前推导
        dfs(fMap, gMap, treeNode->left);
        dfs(fMap, gMap, treeNode->right);
        // 选择结点 treeNode
        fMap[treeNode] =
            treeNode->val + gMap[treeNode->left] + gMap[treeNode->right];
        // 不选结点 treeNode
        gMap[treeNode] = max(fMap[treeNode->left], gMap[treeNode->left]) +
                         max(fMap[treeNode->right], gMap[treeNode->right]);
    }

    int rob(TreeNode* root) {
        unordered_map<TreeNode*, int> fMap, gMap;
        dfs(fMap, gMap, root);
        return max(fMap[root], gMap[root]);
    }

    /**
     * 树形dp  空间压缩版本，每个结点只和左右孩子有关
     * 抽象为：每个子树的最大权值，父子结点不能同时选择
     * 选择根结点 i 的最大权值 f(i), 不选择根结点 i 的最大权值为 g(i)
     * f(i) = val(i) + g(lc) + g(rc)
     * // 不选i，子孩子可以选和不选，取选和不选中的较大值
     * g(i) = max(f(lc), g(lc)) + max(f(rc), g(rc))
     */
    // 返回值记录每个结点的 f，g 值
    pair<int, int> dfs2(TreeNode* treeNode) {
        if (treeNode == nullptr) return {0, 0};
        // 后序遍历  状态从后向前推导
        auto left = dfs2(treeNode->left);
        auto right = dfs2(treeNode->right);
        // 选择结点 treeNode
        int chooseNode = treeNode->val + left.second + right.second;
        // 不选结点 treeNode
        int noChoose =
            max(left.first, left.second) + max(right.first, right.second);
        return {chooseNode, noChoose};
    }

    int rob2(TreeNode* root) {
        // pair 第一个值表示 f，第二个表示 g
        pair<int, int> pair = dfs2(root);
        return max(pair.first, pair.second);
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{3, 2, 3, null, 3, null, 1},
                                {3, 4, 5, 1, 3, null, 1}};
    for (auto i : list) {
        TreeNode* node = new TreeNode(i);
        int count = s->rob2(node);
        cout << count << endl << endl;
    }
}