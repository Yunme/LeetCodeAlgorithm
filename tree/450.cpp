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
 * 450. 删除二叉搜索树中的结点
 *
 * 给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key
 * 对应的节点，并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的根节点的引用。
 * 一般来说，删除节点可分为两个步骤：
 * 首先找到需要删除的节点；
 * 如果找到了，删除它。
 *
 * https://leetcode.cn/problems/delete-node-in-a-bst/description/
 */
class Solution {
   public:
    /**
     * 删除结点 结点情况
     * 1.叶子结点，直接删除
     * 2.有左右孩子，找到后继（右子树的最左孩子），删除后继，值替换到当前结点
     * 3.有且仅有一个孩子，用孩子替换它
     */
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return root;
        TreeNode* parent = nullptr;
        TreeNode* curr = root;
        while (curr) {
            if (curr->val == key) {
                break;
            }
            parent = curr;
            if (curr->val < key) {
                curr = curr->right;
            } else if (curr->val > key) {
                curr = curr->left;
            }
        }
        // 未找到要删除的结点 直接返回
        if (curr == nullptr) return root;
        // 删除结点有左右孩子: 用后继结点来替换它
        // 结点值替换，结点指针不变
        if (curr->left && curr->right) {
            // 寻找后继结点 右子树中的最小结点
            TreeNode* succssorParent = curr;
            TreeNode* succssor = curr->right;
            // 右子树的最小结点在左子树上
            while (succssor->left) {
                succssorParent = succssor;
                succssor = succssor->left;
            }
            // 删除后继结点，后继结点的值替换到当前结点
            if (succssorParent != curr) {
                // 后继不是当前要删除的直接右孩子
                // 删除后继，后继一定无左孩子，可能有右孩子
                // 变成删除只有右孩子的结点，把右孩子赋值给父亲的左孩子
                succssorParent->left = succssor->right;
            } else {
                // 后继是当前要删除的直接右孩子
                // 后继可能有右孩子
                // 删除只有右孩子的结点。
                succssorParent->right = succssor->right;
            }
            curr->val = succssor->val;
            delete succssor;
        } else {
            // 删除结点只有左孩子或只有右孩子，或是叶子结点
            TreeNode* child = nullptr;
            if (curr->left) {
                child = curr->left;
            } else if (curr->right) {
                child = curr->right;
            }
            // 删除的是根结点
            if (curr == root) {
                return child;
            } else if (curr == parent->left) {
                // 如果当前是左孩子，父的左指针替换为当前的孩子
                parent->left = child;
            } else if (curr == parent->right) {
                // 如果当前是右孩子，父的右指针替换为当前的孩子
                parent->right = child;
            }
            delete curr;
        }
        return root;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{5, 3, 6, 2, 4, null, 7},
                               {5, 3, 6, 2, 4, null, 7}};
    vector<int> deleteKeys = {3, 0};
    for (int i = 0; i < arr.size(); i++) {
        auto ans = s->deleteNode(new TreeNode(arr[i]), deleteKeys[i]);
        ans->print();
    }
}