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
 * 129: 求根节点到叶子节点数字之和
 *
 * 给你一个二叉树的根节点 root ，树中每个节点都存放有一个 0 到 9 之间的数字。
 * 每条从根节点到叶节点的路径都代表一个数字：
 * 例如，从根节点到叶节点的路径 1 -> 2 -> 3 表示数字 123 。
 * 计算从根节点到叶节点生成的 所有数字之和 。
 * 叶节点 是指没有子节点的节点。
 *
 * https://leetcode.cn/problems/sum-root-to-leaf-numbers/description
 */
class Solution {
   public:
    /**
     * 法1：DFS 递归法
     */
    int dfs(TreeNode* root, int path) {
        if (root == nullptr) {
            return 0;
        }
        // 当前层累加
        path = path * 10 + root->val;
        if (root->left == nullptr && root->right == nullptr) {
            // 叶子节点返回
            return path;
        }
        // 各个路径相加
        return dfs(root->left, path) + dfs(root->right, path);
    }
    int sumNumbers(TreeNode* root) {
        if (root == nullptr) return 0;
        return dfs(root, 0);
    }

    /**
     * BFS 迭代法
     * 两个队列 一个用于 BFS 遍历，一个保存路径之和
     */
    int sumNumbers2(TreeNode* root) {
        if (root == nullptr) return 0;

        queue<int> queueSum;
        queue<TreeNode*> queue;
        queueSum.push(root->val);
        queue.push(root);
        int ans = 0;
        while (!queue.empty()) {
            TreeNode* front = queue.front();
            queue.pop();
            int sum = queueSum.front();
            queueSum.pop();
            // 到达叶子节点 累加到结果
            if (front->left == nullptr && front->right == nullptr) {
                ans += sum;
                continue;
            }

            // 左孩子
            if (front->left) {
                queue.push(front->left);
                queueSum.push(sum * 10 + front->left->val);
            }
            // 右孩子
            if (front->right) {
                queue.push(front->right);
                queueSum.push(sum * 10 + front->right->val);
            }
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{1, 2, 3}, {4, 9, 0, 5, 1}};
    for (auto& i : arr) {
        auto ans = s->sumNumbers2(new TreeNode(i));
        cout << ans << endl << endl;
    }
}