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
 * 173：二叉搜索树迭代器
 *
 * 实现一个二叉搜索树迭代器类BSTIterator
 * 表示一个按中序遍历二叉搜索树（BST）的迭代器：
 * - BSTIterator(TreeNode root) 初始化 BSTIterator 类的一个对象。
 * BST 的根节点 root 会作为构造函数的一部分给出。
 * 指针应初始化为一个不存在于 BST 中的数字，
 * 且该数字小于 BST 中的任何元素。
 * - boolean hasNext() 如果向指针右侧遍历存在数字，则返回 true ；否则返回 false
 *
 * - int next()将指针向右移动，然后返回指针处的数字。
 * 注意，指针初始化为一个不存在于 BST 中的数字，所以对 next() 的首次调用将返回
 * BST 中的最小元素。 你可以假设 next() 调用总是有效的，也就是说，当调用 next()
 * 时，BST 的中序遍历中至少存在一个下一个数字。
 *
 * https://leetcode.cn/problems/binary-search-tree-iterator/description
 */
class BSTIterator {
   private:
    /**
     * DFS 中序遍历保存
     */
    // 当前索引
    int index = 0;
    vector<TreeNode*> inorderList;
    void inorder(TreeNode* root) {
        if (root == nullptr) return;
        inorder(root->left);
        inorderList.push_back(root);
        inorder(root->right);
    }

   public:
    BSTIterator(TreeNode* root) { inorder(root); }

    int next() { return inorderList[index++]->val; }

    bool hasNext() { return index < inorderList.size(); }
};

/**
 * BFS 迭代 中序遍历
 * 左 根 右
 */
class BSTIterator2 {
   private:
    TreeNode* node;
    stack<TreeNode*> stack;

   public:
    BSTIterator2(TreeNode* root) { this->node = root; }

    int next() {
        // 所有左孩子入栈
        while (node) {
            stack.push(node);
            node = node->left;
        }
        // 到达叶子节点后
        // 出栈
        node = stack.top();
        stack.pop();
        int val = node->val;
        node = node->right;
        return val;
    }

    bool hasNext() { return node || !stack.empty(); }
};

typedef BSTIterator2 BSTIteratorTest;

int main() {
    vector<int> list = {7, 3, 15, null, null, 9, 20};
    TreeNode* root = new TreeNode(list);
    BSTIteratorTest bSTIterator(root);
    auto result = bSTIterator.next();  // 返回 3
    cout << result << endl;
    result = bSTIterator.next();  // 返回 7
    cout << result << endl;
    result = bSTIterator.hasNext();  // 返回 True
    cout << result << endl;
    result = bSTIterator.next();  // 返回 9
    cout << result << endl;
    result = bSTIterator.hasNext();  // 返回 True
    cout << result << endl;
    result = bSTIterator.next();  // 返回 15
    cout << result << endl;
    result = bSTIterator.hasNext();  // 返回 True
    cout << result << endl;
    result = bSTIterator.next();  // 返回 20
    cout << result << endl;
    result = bSTIterator.hasNext();  // 返回 False
    cout << result << endl;
}