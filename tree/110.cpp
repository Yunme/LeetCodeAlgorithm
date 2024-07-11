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
 * 110: 平衡二叉树
 *
 * 给定一个二叉树，判断它是否是平衡二叉树
 * 平衡二叉树: 是指该树所有节点的左右子树的深度相差不超过 1。
 *
 * https://leetcode.cn/problems/balanced-binary-tree/description/
 */
class Solution {
   public:
    /**
     * 计算高度
     */
    int getHeight(TreeNode* root) {
        if (root == nullptr) return 0;
        return max(getHeight(root->left), getHeight(root->right)) + 1;
    }
    /**
     * 法1: 自顶向下 O(n^2)
     */
    bool isBalanced(TreeNode* root) {
        if (root == nullptr) return true;
        // 计算左右子树的高度
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);
        // 高度差 <= 1 且 左右子树都是平衡的
        return abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) &&
               isBalanced(root->right);
    }

    /**
     * 法2: 自底向上 后序遍历 O(n)
     * 先判断左右子树是否平衡, 如果平衡返回其高度, 如果不平衡返回 -1
     * 如果一颗子树不平衡,则整个二叉树不平衡
     */
    int getHeight2(TreeNode* root) {
        if (root == nullptr) return 0;
        // 计算左右子树的高度
        int leftHeight = getHeight2(root->left);
        int rightHeight = getHeight2(root->right);
        // 不平衡 返回 -1
        if (leftHeight == -1 || rightHeight == -1 ||
            abs(leftHeight - rightHeight) > 1) {
            return -1;
        }
        // 平衡 返回 高度
        return max(leftHeight, rightHeight) + 1;
    }
    bool isBalanced2(TreeNode* root) { return getHeight2(root) != -1; }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{3, 9, 20, null, null, 15, 7},
                               {1, null, 2},
                               {2, null, 3, null, 4, null, 5, null, 6}};
    for (auto& i : arr) {
        int ans = s->minDepth2(new TreeNode(i));
        cout << ans << endl;
    }
}