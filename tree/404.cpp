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
 * 404: 左叶子之和
 *
 * 给定二叉树的根节点 root ，返回所有左叶子之和。
 *
 * https://leetcode.cn/problems/sum-of-left-leaves/description/
 */
class Solution {
   public:
    /**
     * DFS
     */
    int dfs(TreeNode* root, bool left, int sum) {
        if (root == nullptr) return 0;
        // 来自左孩子 且为叶子结点时 相加
        if (left && root->left == nullptr && root->right == nullptr) {
            sum += root->val;
            return sum;
        }
        // 递归左右孩子
        return dfs(root->left, true, sum) + dfs(root->right, false, sum);
    }
    int sumOfLeftLeaves(TreeNode* root) {
        int sum = 0;
        return dfs(root, false, sum);
    }

    /**
     * BFS
     * 层序遍历
     */
    int sumOfLeftLeaves2(TreeNode* root) {
        if (root == nullptr) return 0;
        int ans = 0;
        queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                TreeNode* front = queue.front();
                queue.pop();
                if (front->left) {
                    // left 结点是叶子结点
                    if (front->left->left == nullptr &&
                        front->left->right == nullptr) {
                        ans += front->left->val;
                    }
                    queue.push(front->left);
                }
                if (front->right) queue.push(front->right);
            }
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
        auto ans = s->sumOfLeftLeaves2(new TreeNode(i));
        cout << ans << endl;
    }
}