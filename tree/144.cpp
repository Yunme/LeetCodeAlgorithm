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
 * 144：二叉树的前序遍历
 *
 * 给你二叉树的根节点 root ，返回它节点值的 前序 遍历。
 *
 * https://leetcode.cn/problems/binary-tree-preorder-traversal/description/
 */
class Solution {
   public:
    /**
     * 法1：DFS 递归版本
     * 根左右
     */
    void dfs(TreeNode* root, vector<int>& ans) {
        if (root == nullptr) return;
        ans.push_back(root->val);
        dfs(root->left, ans);
        dfs(root->right, ans);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        dfs(root, ans);
        return ans;
    }

    /**
     * 法2：BFS 迭代版本
     * 根左右
     */
    vector<int> preorderTraversal2(TreeNode* root) {
        vector<int> ans;
        if (root == nullptr) return ans;
        stack<TreeNode*> stack;
        TreeNode* node = root;
        while (node || !stack.empty()) {
            while (node) {
                stack.push(node);
                ans.push_back(node->val);
                node = node->left;
            }
            node = stack.top();
            stack.pop();
            node = node->right;
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{1, 2, 3, 4, 5}, {}, {1}};
    for (auto& i : arr) {
        auto ans = s->preorderTraversal(new TreeNode(i));
        for (auto j : ans) {
            cout << j << " ";
        }
        cout << endl;
    }
}