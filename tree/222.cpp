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
 * 222: 完全二叉树的节点个数
 *
 * 给你一棵 完全二叉树 的根节点 root ，求出该树的节点个数。
 * 完全二叉树 的定义如下：
 * 在完全二叉树中，除了最底层节点可能没填满外，
 * 其余每层节点数都达到最大值，
 * 并且最下面一层的节点都集中在该层最左边的若干位置。
 * 若最底层为第 h 层，则该层包含 1~ 2h 个节点。
 *
 * https://leetcode.cn/problems/count-complete-tree-nodes/description
 */
class Solution {
   public:
    /**
     * 法1：O(n) 简单方法
     * 遍历节点来计算
     */
    int countNodes(TreeNode* root) {
        if (root == nullptr) return 0;
        int ans = 0;
        // 前序遍历  根 左 右
        stack<TreeNode*> stack;
        TreeNode* node = root;
        while (node || !stack.empty()) {
            while (node) {
                stack.push(node);
                cout << node->val << " ";
                node = node->left;
            }
            node = stack.top();
            stack.pop();
            ans++;
            node = node->right;
        }
        return ans;
    }

    /**
     * 更清晰的递归方法
     * 满二叉树 左孩子深度 = 右孩子深度
     */
    int countNode4(TreeNode* root) {
        if (root == nullptr) return 0;
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        int leftDepth = 1, rightDepth = 1;  // 初始计算上 root 这层的个数
        while (left) {
            left = left->left;
            leftDepth++;
        }
        while (right) {
            right = right->right;
            rightDepth++;
        }
        // 如果相等, 满二叉树
        // 以 root 为根结点的二叉树是 满二叉树 个数 = 2^depth - 1
        if (leftDepth == rightDepth) {
            return (1 << leftDepth) - 1;
        }
        // 如果不相等 递归计算直到 满二叉树为止
        // 加上当前 root 这一个
        return countNode4(root->left) + countNode4(root->right) + 1;
    }

    /**
     * 法2：递归 O(logN * logN)
     * 根据完全二叉树的性质：除最后一层外，其余层全部占满，最后一层左侧靠拢
     *
     * 如果根结点左子树深度 = 右子树深度，说明左子树为满二叉树
     * 如果根结点左子树深入 > 右子树深度，说明右子树为满二叉树
     * 满二叉树的节点个数为 2^n - 1 n 为深度
     */
    int countLevels(TreeNode* root) {
        int level = 0;
        // 完全二叉树的深度
        while (root) {
            root = root->left;
            level++;
        }
        return level;
    }
    int countNodes2(TreeNode* root) {
        if (root == nullptr) return 0;
        int leftLevel = countLevels(root->left);
        int rightLevel = countLevels(root->right);
        if (leftLevel == rightLevel) {
            // 左子树为满二叉树 个数为 2^leftLevel - 1 + 1(root)
            return countNodes2(root->right) + (1 << leftLevel);
        } else {
            // 右子树为满二叉树
            return countNodes2(root->left) + (1 << rightLevel);
        }
    }

    /**
     * 法3：二分查找 O(logN * logN)
     * 满二叉树的性质
     * 除了最后一层，上面都是满二叉树，所以总个数在 2^(h-1) - 1 + 1 到 2 ^ h -1
     * 范围 最后一层的个数为 1 到 2 ^(h-1)  h 为总层数
     * 二分查找这个范围
     */
    int countNodes3(TreeNode* root) {
        if (root == nullptr) return 0;
        int level = countLevels(root);
        int levelPrev = level - 1;
        // 二分搜索范围：
        int low = 1, high = 1 << levelPrev;
        while (low <= high) {
            int mid = (low + high) >> 1;
            if (isExist(root, mid, levelPrev)) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        int ans = (1 << levelPrev) - 1 + low - 1;
        return ans;
    }
    /**
     * 根据 index 检查满二叉树最后一层节点是否存在
     */
    bool isExist(TreeNode* root, int index, int level) {
        TreeNode* node = root;
        while (level > 0) {
            // 2^n / 2 最后一层的中间分割
            int mid = (1 << level) >> 1;
            if (index > mid) {
                // index 在右子树
                index -= mid;
                node = node->right;
            } else {
                node = node->left;
            }
            level--;
        }
        return node != nullptr;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{1, 2, 3, 4, 5, 6, null}, {}, {1}};
    for (int i = 0; i < list.size(); i++) {
        auto ans = s->countNodes3(new TreeNode(list[i]));
        cout << ans << endl;
    }
}