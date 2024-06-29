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
 * 106：从中序与后序遍历序列构造二叉树
 * 给定两个整数数组 inorder 和 postorder ，
 * 其中 inorder 是二叉树的中序遍历，
 * postorder 是同一棵树的后序遍历，请你构造并返回这颗 二叉树 。
 *
 * https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description
 */
class Solution {
   public:
    /**
     * 递归法
     */
    TreeNode* buildTree(vector<int>& postorder, int postLeft, int postRight,
                        unordered_map<int, int>& inorderMap, int inLeft,
                        int inRight) {
        cout << postLeft << " " << postRight << " " << inLeft << " " << inRight
             << endl;
        if (postLeft > postRight || inLeft > inRight) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(postorder[postRight]);
        int inOrderIndex = inorderMap[postorder[postRight]];
        cout << inOrderIndex << endl;

        int rightSize = inRight - inOrderIndex;
        // 左右根 先算右子树方便点
        // 新右的右 = 右 - 1
        // 新右的左 = 右 - rightSize
        root->right = buildTree(postorder, postRight - rightSize, postRight - 1,
                                inorderMap, inOrderIndex + 1, inRight);
        // int leftSize = inOrderIndex - inLeft;
        // 新左的右 = 新右的左 - 1
        // 新左的左 = 旧左
        root->left = buildTree(postorder, postLeft, postRight - rightSize - 1,
                               inorderMap, inLeft, inOrderIndex - 1);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (postorder.empty()) return nullptr;

        unordered_map<int, int> map;
        for (int i = 0; i < inorder.size(); i++) {
            map[inorder[i]] = i;
        }
        return buildTree(postorder, 0, postorder.size() - 1, map, 0,
                         inorder.size() - 1);
    }

    /**
     * 迭代法
     * 后序入栈
     * 与前序相反
     */
    TreeNode* buildTree2(vector<int>& inorder, vector<int>& postorder) {
        if (postorder.empty()) return nullptr;
        stack<TreeNode*> stack;
        TreeNode* root = new TreeNode(postorder.back());
        stack.push(root);
        int inorderIndex = inorder.size() - 1;
        for (int i = postorder.size() - 2; i >= 0; i--) {
            int postOrderVal = postorder[i];
            TreeNode* node = stack.top();
            if (inorder[inorderIndex] != stack.top()->val) {
                // 右孩子
                node->right = new TreeNode(postOrderVal);
                stack.push(node->right);
            } else {
                // 栈顶出栈 inorderIndex ++
                while (!stack.empty() &&
                       stack.top()->val == inorder[inorderIndex]) {
                    node = stack.top();
                    stack.pop();
                    inorderIndex--;
                }
                // 左孩子
                node->left = new TreeNode(postOrderVal);
                stack.push(node->left);
            }
        }
        return root;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> inorders = {
        {9, 3, 15, 20, 7}, {-1}, {1, 2}, {1, 2, 3, 4}};
    vector<vector<int>> postorders = {
        {9, 15, 7, 20, 3}, {-1}, {2, 1}, {2, 1, 4, 3}};
    for (int i = 0; i < postorders.size(); i++) {
        auto root = s->buildTree2(inorders[i], postorders[i]);
        root->print();
        cout << endl;
    }
}