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
 * 112: 路径总和
 * 给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在
 * 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum
 * 。如果存在，返回 true ；否则，返回 false 。 叶子节点 是指没有子节点的节点。
 *
 * https://leetcode.cn/problems/path-sum/description/
 */
class Solution {
   public:
    /**
     * 法1：DFS 回溯法
     */
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return false;
        // 到达叶子节点 最后剩余的
        if (root->left == nullptr && root->right == nullptr) {
            return root->val == targetSum;
        }

        // 每次减去当前节点的值
        return hasPathSum(root->left, targetSum - root->val) ||
               hasPathSum(root->right, targetSum - root->val);
    }

    /**
     * 法2：BFS
     */
    bool hasPathSum2(TreeNode* root, int targetSum) {
        if (root == nullptr) return false;
        // 两个队列存储，
        // 一个队列用来遍历，一个用来记录累加值
        queue<int> queueSum;
        queue<TreeNode*> queue;
        queueSum.push(root->val);
        queue.push(root);

        while (!queue.empty()) {
            TreeNode* front = queue.front();
            queue.pop();
            int tempSum = queueSum.front();
            queueSum.pop();
            // 到达叶子节点 判断当前和
            if (front->left == nullptr && front->right == nullptr) {
                if (tempSum == targetSum) return true;
                continue;
            }
            if (front->left) {
                queue.push(front->left);
                // 累加值
                queueSum.push(tempSum + front->left->val);
            }
            if (front->right) {
                queue.push(front->right);
                // 累加值
                queueSum.push(tempSum + front->right->val);
            }
        }
        return false;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {
        {5, 4, 8, 11, null, 13, 4, 7, 2, null, null, null, 1},
        {1, 2, 3},
        {1, 2}};
    vector<int> targets = {22, 5, 1};
    for (int i = 0; i < arr.size(); i++) {
        TreeNode* root = new TreeNode(arr[i]);
        auto ans = s->hasPathSum(root, targets[i]);
        cout << ans << endl;
    }
}