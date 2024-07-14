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
 * 530：二叉搜索树的最小绝对差
 * 给你一个二叉搜索树的根节点 root ，返回 树中任意两不同节点值之间的最小差值 。
 * 差值是一个正数，其数值等于两值之差的绝对值。
 *
 * https://leetcode.cn/problems/minimum-absolute-difference-in-bst/description
 */
class Solution {
   public:
    /**
     * 法1： BFS 迭代
     * 二叉搜索树中序遍历有序递增
     * 中序遍历出来 后面的前去前面的
     */
    int getMinimumDifference(TreeNode* root) {
        if (root == nullptr) return 0;
        stack<TreeNode*> stack;
        TreeNode *node = root, *prev = nullptr;
        int ans = INT_MAX;
        while (node || !stack.empty()) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
            node = stack.top();
            if (prev) {
                // cout << node->val << " " << prev->val << endl;
                ans = min(ans, abs(node->val - prev->val));
            }
            prev = node;

            stack.pop();
            node = node->right;
        }
        return ans;
    }

    /**
     * 法2：DFS 递归法
     * 中序遍历
     */
    void dfs(TreeNode* root, TreeNode* pre, int& ans) {
        if (root == nullptr) return;
        // 左
        dfs(root->left, pre, ans);
        // 当前结点 root 和中序遍历前一个结点的差值
        if (pre == nullptr) {
            pre = root;
        } else {
            ans = min(ans, abs(root->val - pre->val));
            pre = root;
        }
        // 右
        dfs(root->right, pre, ans);
    }

    int getMinimumDifference2(TreeNode* root) {
        if (root == nullptr) return 0;
        int ans = INT_MAX;
        dfs(root, nullptr, ans);
        return ans;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{4, 2, 6, 1, 3}, {1, 0, 48, null, null, 12, 49}};
    for (auto& i : arr) {
        TreeNode* root = new TreeNode(i);
        auto ans = s->getMinimumDifference2(root);
        cout << ans << endl;
    }
}