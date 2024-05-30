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
 * 94: 二叉树的中序遍历
 * 给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。
 * https://leetcode.cn/problems/binary-tree-inorder-traversal/description/
 */
class Solution {
   public:
    /**
     * 递归版本
     */
    void inorderTraversalRecursive(TreeNode* root, vector<int>& ans) {
        if (root == nullptr) return;
        inorderTraversalRecursive(root->left, ans);
        ans.push_back(root->val);
        inorderTraversalRecursive(root->right, ans);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        inorderTraversalRecursive(root, ans);
        return ans;
    }

    /**
     * 迭代版本
     */
    vector<int> inorderTraversal2(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode*> stack;
        TreeNode* p = root;
        while (p || !stack.empty()) {
            if (p) {
                // 左边依次入栈，直到为空
                stack.push(p);
                p = p->left;
            } else {
                // 左子树依次出栈
                TreeNode* top = stack.top();
                ans.push_back(top->val);
                stack.pop();
                // 右子树入栈
                p = top->right;
            }
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{3, 9, 20, null, null, 15, 7}, {1, null, 2}};
    for (auto& i : arr) {
        auto ans = s->inorderTraversal2(new TreeNode(i));
        for (auto& j : ans) cout << j << " ";
        cout << endl;
    }
}