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
 * 230: 二叉搜索树中第 K 小的元素
 * 给定一个二叉搜索树的根节点 root ，和一个整数 k ，
 * 请你设计一个算法查找其中第 k 小的元素（从 1 开始计数）。
 * https://leetcode.cn/problems/kth-smallest-element-in-a-bst/description
 */
class Solution {
   public:
    /**
     * 法1：BFS 迭代查找
     */
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> stack;
        TreeNode* node = root;
        TreeNode* prev = nullptr;
        while (node || !stack.empty()) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
            TreeNode* top = stack.top();
            stack.pop();
            node = top->right;
            if (prev && top->val == prev->val) {
                continue;
            }
            prev = top;
            // 返回 第 k 小
            if (--k == 0) {
                return top->val;
            }
        }
        return -1;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{3, 1, 4, null, 2},
                               {5, 3, 6, 2, 4, null, null, 1}};
    vector<int> ks = {1, 3};
    for (int i = 0; i < arr.size(); i++) {
        TreeNode* root = new TreeNode(arr[i]);
        auto ans = s->kthSmallest(root, ks[i]);
        cout << ans << endl;
    }
}