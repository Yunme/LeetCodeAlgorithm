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
 * 145：二叉树的后序遍历
 *
 * 给你二叉树的根节点 root ，返回它节点值的 后序 遍历。
 *
 * https://leetcode.cn/problems/binary-tree-postorder-traversal/description/
 */
class Solution {
   public:
    /**
     * 法1：DFS 递归
     * 左右根
     */
    void dfs(TreeNode* root, vector<int>& ans) {
        if (root == nullptr) return;
        dfs(root->left, ans);
        dfs(root->right, ans);
        ans.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        dfs(root, ans);
        return ans;
    }

    /**
     * 法2：BFS 迭代
     * 左右根
     */
    vector<int> postorderTraversal2(TreeNode* root) {
        vector<int> ans;
        if (root == nullptr) return ans;
        stack<TreeNode*> stack;
        TreeNode* node = root;
        TreeNode* prev = nullptr;
        while (node || !stack.empty()) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
            node = stack.top();
            stack.pop();
            if (node->right == nullptr || node->right == prev) {
                ans.push_back(node->val);
                prev = node;
                node = nullptr;
            } else {
                stack.push(node);
                node = node->right;
            }
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{1, 2, 3, 4, 5}, {}, {1}};
    for (auto& i : arr) {
        auto ans = s->postorderTraversal2(new TreeNode(i));
        for (auto j : ans) {
            cout << j << " ";
        }
        cout << endl;
    }
}