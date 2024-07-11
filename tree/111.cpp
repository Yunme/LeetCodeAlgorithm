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
 * 111: 二叉树的最小深度
 *
 * 给定一个二叉树，找出其最小深度。
 * 最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
 * 说明：叶子节点是指没有子节点的节点。
 *
 * https://leetcode.cn/problems/minimum-depth-of-binary-tree/description/
 */
class Solution {
   public:
    /**
     * DFS
     * 根结点到叶子结点的深度
     */
    int minDepth(TreeNode* root) {
        // 空结点 深度为 0
        if (root == nullptr) return 0;
        // 叶子结点 深度为 1
        if (root->left == nullptr && root->right == nullptr) return 1;
        // 有一个孩子为空时: 返回不为空的孩子的深度
        if (root->left && root->right == nullptr) {
            return minDepth(root->left) + 1;
        }
        if (root->left == nullptr && root->right) {
            return minDepth(root->right) + 1;
        }
        // 都不为空 去左右孩子的较小值
        return min(minDepth(root->left), minDepth(root->right)) + 1;
    }

    /**
     * BFS 迭代
     * 根结点到叶子结点的深度
     */
    int minDepth2(TreeNode* root) {
        if (root == nullptr) return 0;
        queue<TreeNode*> queue;
        queue.push(root);
        int ans = 0;
        while (!queue.empty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                TreeNode* top = queue.front();
                queue.pop();
                // 碰到第一个叶子结点 返回
                if (top->left == nullptr && top->right == nullptr) {
                    return ans + 1;
                }
                if (top->left) queue.push(top->left);
                if (top->right) queue.push(top->right);
            }
            // 每层累加
            ans++;
        }
        return ans;
    }
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