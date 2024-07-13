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
 * 700: 二叉搜索树中的搜索
 *
 * 给定二叉搜索树（BST）的根节点 root 和一个整数值 val。
 * 你需要在 BST 中找到节点值等于 val 的节点。 返回以该节点为根的子树。
 * 如果节点不存在，则返回 null 。
 *
 * https://leetcode.cn/problems/search-in-a-binary-search-tree/description/
 */
class Solution {
   public:
    /**
     * 法1：递归 BST 查找结点
     */
    TreeNode* searchBST(TreeNode* root, int val) {
        if (root == nullptr) return nullptr;
        // 当前结点返回
        if (root->val == val) return root;
        // 根结点较大 搜左子树
        if (root->val > val) {
            return searchBST(root->left, val);
        } else {
            // 较小 搜右子树
            return searchBST(root->right, val);
        }
    }

    /**
     * 法2：迭代 BST 查找结点
     */
    TreeNode* searchBST2(TreeNode* root, int val) {
        if (root == nullptr) return nullptr;
        while (root) {
            if (root->val == val)
                return root;
            else if (root->val > val)
                root = root->left;
            else
                root = root->right;
        }
        return nullptr;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{4, 2, 7, 1, 3}, {4, 2, 7, 1, 3}};
    vector<int> target = {2, 5};
    for (int i = 0; i < list.size(); i++) {
        auto ans = s->searchBST2(new TreeNode(list[i]), target[i]);
        if (ans) {
            ans->print();
        }
    }
}