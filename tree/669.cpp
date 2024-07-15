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
 * 669: 修剪二叉搜索树
 *
 * 给你二叉搜索树的根节点 root ，同时给定最小边界low 和最大边界
 * high。通过修剪二叉搜索树，使得所有节点的值在[low, high]中。 修剪树 不应该
 * 改变保留在树中的元素的相对结构
 * (即，如果没有被移除，原有的父代子代关系都应当保留)。 可以证明，存在
 * 唯一的答案 。
 *
 * https://leetcode.cn/problems/search-in-a-binary-search-tree/description/
 */
class Solution {
   public:
    /**
     * 法1：递归 DFS
     */
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (root == nullptr) return nullptr;
        // 当前结点 小于 low
        if (root->val < low) {
            // 应该被删掉，但其右子树里可能有在区间里的
            return trimBST(root->right, low, high);
        } else if (root->val > high) {
            // 当前结点大于 high 应该被删掉，但是其左子树里有可能有在区间里的
            return trimBST(root->left, low, high);
        }
        // 修建左子树
        root->left = trimBST(root->left, low, high);
        // 修建右子树
        root->right = trimBST(root->right, low, high);
        return root;
    }

    /**
     * 法2：迭代
     */
    TreeNode* trimBST2(TreeNode* root, int low, int high) {
        // 找到第一个在区间内的 结点 作为 root 返回
        while (root && (root->val < low || root->val > high)) {
            if (root->val < low) root = root->right;
            if (root->val > high) root = root->left;
        }
        if (root == nullptr) return nullptr;
        // 修剪 root 的左子树
        TreeNode* node = root;
        while (node->left) {
            // 左孩子小于 low。检查左孩子的右子树
            if (node->left->val < low) {
                node->left = node->left->right;
            } else {
                node = node->left;
            }
        }

        // 修剪 root 的右子树
        node = root;
        while (node->right) {
            // 右孩子的值大于 high 检查右孩子的左子树
            if (node->right->val > high) {
                node->right = node->right->left;
            } else {
                node = node->right;
            }
        }
        return root;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{1, 0, 2}, {3, 0, 4, null, 2, null, null, 1}};
    vector<int> low = {1, 1};
    vector<int> high = {2, 3};
    for (int i = 0; i < list.size(); i++) {
        auto ans = s->trimBST(new TreeNode(list[i]), low[i], high[i]);
        if (ans) {
            ans->print();
        }
    }
}