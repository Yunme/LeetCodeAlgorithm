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
 * 114: 二叉树展开为链表
 * 给你二叉树的根结点 root ，请你将它展开为一个单链表：
 * 展开后的单链表应该同样使用 TreeNode ，其中 right
 * 子指针指向链表中下一个结点，而左子指针始终为 null 。
 * 展开后的单链表应该与二叉树 先序遍历 顺序相同。
 *
 * https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/description/
 */
class Solution {
   public:
    /**
     * 法1：前序遍历序列 连接 O(n) O(n)
     * 递归前序遍历
     */
    void preorder(TreeNode* root, vector<TreeNode*>& list) {
        if (root == nullptr) return;
        // 前序遍历序列 添加到列表中
        list.push_back(root);
        preorder(root->left, list);
        preorder(root->right, list);
    }
    // 迭代 前序遍历
    void preorder2(TreeNode* root, vector<TreeNode*>& list) {
        stack<TreeNode*> stack;
        TreeNode* node = root;
        while (node || !stack.empty()) {
            if (node) {
                list.push_back(node);
                stack.push(node);
                node = node->left;
            } else {
                TreeNode* top = stack.top();
                stack.pop();
                node = top->right;
            }
        }
    }
    void flatten(TreeNode* root) {
        vector<TreeNode*> list;
        preorder2(root, list);
        TreeNode* p = root;
        // 遍历列表 连接到 right 指针
        for (int i = 1; i < list.size(); i++) {
            p->right = list[i];
            // 左指针置空
            p->left = nullptr;
            p = p->right;
        }
    }

    /**
     * 法2： 寻找前驱节点 O(n) O(1)
     * 前序遍历 ：根，左，右，
     * 右孩子的前驱是左孩子中最右的。
     */
    void flatten2(TreeNode* root) {
        TreeNode* current = root;
        while (current) {
            if (current->left) {
                // 左孩子
                TreeNode* next = current->left;
                TreeNode* predecessor = next;
                while (predecessor->right) {  // 一直向右找前驱
                    predecessor = predecessor->right;
                }
                // 右孩子连接到前驱后面
                predecessor->right = current->right;
                current->left = nullptr;
                // 原来的左孩子连接到 右边
                current->right = next;
            }
            current = current->right;
        }
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{1, 2, 5, 3, 4, null, 6}, {}, {1, 2, 3}};
    for (auto& i : arr) {
        TreeNode* root = new TreeNode(i);
        s->flatten(root);
        root->print();
        cout << endl;
    }
}