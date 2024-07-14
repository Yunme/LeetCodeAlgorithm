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
 * 235: 二叉搜索树的最近公共祖先
 * 给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
 *
 * 近公共祖先的定义为：对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点
 * x， 满足 x 是 p、q 的祖先且 x
 * 的深度尽可能大（一个节点也可以是它自己的祖先）。
 *
 * https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/description/
 */
class Solution {
   public:
    /**
     * 法1：迭代版本
     * 根据二叉搜索树的性质
     * 公共祖先一定是结点值处于 p，q中间的结点
     */
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* current = root;
        while (current) {
            // 当前结点比 p q都大，应该寻找左子树
            if (current->val > p->val && current->val > q->val) {
                current = current->left;
            } else if (current->val < p->val && current->val < q->val) {
                // current 比 p q 都小，应该寻找右子树
                current = current->right;
            } else {
                // current 值在 p q 中间
                return current;
            }
        }
        return nullptr;
    }

    /**
     * 法2：递归版本
     * 根据二叉搜索树的性质
     * 公共祖先一定是结点值处于 p，q中间的结点
     */
    TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) return nullptr;
        // 当前结点比 p q都大，应该寻找左子树
        if (root->val > p->val && root->val > q->val) {
            TreeNode* left = lowestCommonAncestor(root->left, p, q);
            if (left) {
                return left;
            }
        } else if (root->val < p->val && root->val < q->val) {
            // current 比 p q 都小，应该寻找右子树
            TreeNode* right = lowestCommonAncestor(root->right, p, q);
            if (right) {
                return right;
            }
        }
        return root;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{6, 2, 8, 0, 4, 7, 9, null, null, 3, 5},
                               {6, 2, 8, 0, 4, 7, 9, null, null, 3, 5}};
    vector<int> ps = {2, 2};
    vector<int> qs = {8, 4};
    for (int i = 0; i < arr.size(); i++) {
        TreeNode* root = new TreeNode(arr[i]);
        auto ans = s->lowestCommonAncestor2(root, new TreeNode(ps[i]),
                                            new TreeNode(qs[i]));
        cout << ans->val << endl;
    }
}