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
 * 105：从前序与中序遍历序列构造二叉树
 * 给定两个整数数组 preorder 和 inorder ，
 * 其中 preorder 是二叉树的先序遍历，
 * inorder 是同一棵树的中序遍历，
 * 请构造二叉树并返回其根节点。
 *
 * https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description
 */
class Solution {
   public:
    /**
     * 法1： 递归
     * 二叉树的前序遍历和中序遍历的性质
     * 前序遍历第一个肯定是根结点
     * 根结点把中序遍历过程分为左右子树
     * 递归操作
     */
    TreeNode* build(int preLeft, int preRight, int inLeft, int inRight,
                    vector<int>& preorder,
                    unordered_map<int, int>& inorderMap) {
        // cout << preLeft << " " << preRight << " " << inLeft << " " << inRight
        //      << endl;
        // 索引异常 返回 null
        if (preLeft > preRight || inLeft > inRight) return nullptr;
        // 从前序构造结点
        TreeNode* root = new TreeNode(preorder[preLeft]);
        // 从中序中找出根结点索引 分割
        // int inorderIndex = -1;
        // for (int i = inLeft; i <= inRight; i++) {
        //     if (inorder[i] == preorder[preLeft]) {
        //         inorderIndex = i;
        //         break;
        //     }
        // }
        int inorderIndex = inorderMap[preorder[preLeft]];
        // 左子树
        // 前序遍历 , 根左右
        // 左子树的元素个数
        int preLeftSize = inorderIndex - inLeft;
        // 缩小区间
        root->left = build(preLeft + 1, preLeft + preLeftSize, inLeft,
                           inorderIndex - 1, preorder, inorderMap);
        // 右子树
        root->right = build(preLeft + preLeftSize + 1, preRight,
                            inorderIndex + 1, inRight, preorder, inorderMap);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // 创建 map 更快的找到 中序序列的元素位置
        unordered_map<int, int> inorderMap;
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        return build(0, preorder.size() - 1, 0, inorder.size() - 1, preorder,
                     inorderMap);
    }

    /**
     * 法2：迭代法
     * 栈来维护前序中：没有考虑过右儿子的祖先结点，只有在栈中的结点才能连接右儿子
     * 一个指针 index 来指向中序遍历的位置，index
     * 对应结点，一直向左儿子走，直到叶子结点
     */
    TreeNode* buildTree2(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty()) return nullptr;
        stack<TreeNode*> stack;
        // 一个栈 维护前序遍历
        TreeNode* root = new TreeNode(preorder[0]);
        // 前序的第一个是根结点
        stack.push(root);
        // 一个指针 中序遍历
        int inorderIndex = 0;
        for (int i = 1; i < preorder.size(); i++) {
            int preorderVal = preorder[i];
            TreeNode* node = stack.top();
            // 遇到中序遍历之前都是左孩子
            if (node->val != inorder[inorderIndex]) {
                node->left = new TreeNode(preorderVal);
                stack.push(node->left);
            } else {
                // 右孩子
                // 不断出栈，中序指针前进；直到中序与栈顶不同
                while (!stack.empty() &&
                       stack.top()->val == inorder[inorderIndex]) {
                    node = stack.top();
                    stack.pop();
                    inorderIndex++;
                }
                // 右孩子入栈
                node->right = new TreeNode(preorderVal);
                stack.push(node->right);
            }
        }
        return root;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> preorders = {
        {3, 9, 20, 15, 7}, {-1}, {1, 2}, {3, 1, 2, 4}};
    vector<vector<int>> inorders = {
        {9, 3, 15, 20, 7}, {-1}, {1, 2}, {1, 2, 3, 4}};
    for (int i = 0; i < preorders.size(); i++) {
        auto root = s->buildTree2(preorders[i], inorders[i]);
        root->print();
        cout << endl;
    }
}