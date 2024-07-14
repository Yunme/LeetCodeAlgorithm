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
 * 701: 二叉搜索树中的插入操作
 *
 * 给定二叉搜索树（BST）的根节点 root 和要插入树中的值 value
 * ，将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。 输入数据 保证
 * ，新值和原始二叉搜索树中的任意节点值都不同。
 *
 * https://leetcode.cn/problems/insert-into-a-binary-search-tree/description/
 */
class Solution {
   public:
    /**
     * 法1：递归
     * 根据 BST 的性质插入
     */
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr) return new TreeNode(val);
        return insertIntoBST(root, nullptr, val);
    }
    TreeNode* insertIntoBST(TreeNode* root, TreeNode* parent, int val) {
        if (root == nullptr) {
            TreeNode* node = new TreeNode(val);
            if (parent->val > val) {
                parent->left = node;
            } else {
                parent->right = node;
            }
            return nullptr;
        }
        if (root->val < val) {
            insertIntoBST(root->right, root, val);
        } else if (root->val > val) {
            insertIntoBST(root->left, root, val);
        }
        return root;
    }

    TreeNode* insertIntoBST2(TreeNode* root, int val) {
        TreeNode* node = new TreeNode(val);
        if (root == nullptr) return node;

        TreeNode* current = root;
        TreeNode* parent = nullptr;
        while (current) {
            parent = current;
            if (current->val < val) {
                current = current->right;
            } else if (current->val > val) {
                current = current->left;
            }
        }
        if (parent->val > val) {
            parent->left = node;
        } else {
            parent->right = node;
        }
        return root;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{4, 2, 7, 1, 3}, {4, 2, 7, 1, 3}};
    vector<int> target = {5, 6};
    for (int i = 0; i < list.size(); i++) {
        auto ans = s->insertIntoBST2(new TreeNode(list[i]), target[i]);
        if (ans) {
            ans->print();
            cout << endl;
        }
    }
}