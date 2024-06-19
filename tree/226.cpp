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
 * 226：翻转二叉树
 * 给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。
 * 交换左右孩子
 * https://leetcode.cn/problems/invert-binary-tree/description/
 */
class Solution {
   public:
    /**
     * DFS 递归法
     */
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return root;

        // 翻转左子树
        TreeNode* newRight = invertTree(root->left);
        // 左子树 = 翻转右子树
        root->left = invertTree(root->right);
        // 交换
        root->right = newRight;
        return root;
    }

    /**
     * BFS 迭代法
     * 层序遍历法
     */
    TreeNode* invertTree2(TreeNode* root) {
        if (root == nullptr) return root;
        queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            TreeNode* front = queue.front();
            queue.pop();
            // 每层左右子树交换
            TreeNode* temp = front->left;
            front->left = front->right;
            front->right = temp;
            if (front->left) queue.push(front->left);
            if (front->right) queue.push(front->right);
        }
        return root;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{4, 2, 7, 1, 3, 6, 9}, {2, 1, 3}};
    for (auto& i : arr) {
        TreeNode* root = new TreeNode(i);
        s->invertTree2(root)->print();
        cout << endl;
    }
}