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
 * 236: 二叉树的最近公共祖先
 * 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
 *
 * 近公共祖先的定义为：对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点
 * x， 满足 x 是 p、q 的祖先且 x
 * 的深度尽可能大（一个节点也可以是它自己的祖先）。
 *
 * https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/description
 */
class Solution {
   public:
   /**
    * 法1：递归 O(n) O(n)
    */
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root->val == p->val || root->val == q->val)
            return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        // 如果左子树为空 一定在右子树中
        if (left == nullptr) return right;
        // 如果右子树为空 一定在左子树中
        if (right == nullptr) return left;
        // 都不会空，那么当前节点就是最近公共祖先
        return root;
    }
    /**
     * 法2：迭代法 O(n) O(n)
     * 先 DFS 记录父节点 最近公共祖先 肯定是出现的第一个
     */
    unordered_map<TreeNode*, TreeNode*> parent;
    unordered_map<TreeNode*, bool> visited;
    void dfs(TreeNode* root) {
        if (root->left) {
            parent[root->left] = root;
            dfs(root->left);
        }
        if (root->right) {
            parent[root->right] = root;
            dfs(root->right);
        }
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) return root;
        parent[root] = nullptr;
        // DFS 建立 父节点映射
        dfs(root);
        // 从 p 节点 向上找 并标记访问的节点
        while (p) {
            visited[p] = true;
            p = parent[p];
        }
        // 从 q 节点 向上找 找到第一个标记的节点 一定是公共最近祖先
        while (q) {
            if (visited[q]) return q;
            q = parent[q];
        }
        return nullptr;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {
        {3, 5, 1, 6, 2, 0, 8, null, null, 7, 4, null, null, null, null},
        {3, 5, 1, 6, 2, 0, 8, null, null, 7, 4, null, null, null, null},
        {1, 2}};
    vector<int> ps = {5, 5, 1};
    vector<int> qs = {1, 4, 2};
    for (int i = 0; i < arr.size(); i++) {
        TreeNode* root = new TreeNode(arr[i]);
        auto ans = s->lowestCommonAncestor(root, new TreeNode(ps[i]),
                                           new TreeNode(qs[i]));
        cout << ans->val << endl;
    }
}