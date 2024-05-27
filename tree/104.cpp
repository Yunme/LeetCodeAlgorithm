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
 * 104：二叉树的最大深度
 * 给定一个二叉树 root ，返回其最大深度。
 * 二叉树的 最大深度 是指从根节点到最远叶子节点的最长路径上的节点数。
 * https://leetcode.cn/problems/maximum-depth-of-binary-tree/description/
 */
class Solution {
   public:
    /**
     * DFS
     */
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }

    /**
     * BFS
     * 队列里存的是当前层的结点
     * 当前层都搜索完，层数加1
     */
    int maxDepth2(TreeNode* root) {
        if (root == nullptr) return 0;
        queue<TreeNode*> queue;
        queue.push(root);
        int ans = 0;
        while (!queue.empty()) {
            int size = queue.size();
            while (size > 0) {
                TreeNode* node = queue.front();
                queue.pop();
                if (node->left) queue.push(node->left);
                if (node->right) queue.push(node->right);
                size--;
            }
            ans++;
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{3, 9, 20, null, null, 15, 7}, {1, null, 2}};
    for (auto& i : arr) {
        int ans = s->maxDepth2(new TreeNode(i));
        cout << ans << endl;
    }
}