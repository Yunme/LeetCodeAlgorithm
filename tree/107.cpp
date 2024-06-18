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
 * 107：二叉树的层序遍历 II
 * 给你二叉树的根节点 root ，返回其节点值 自底向上的层序遍历 。
 * （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）
 *
 * https://leetcode.cn/problems/binary-tree-level-order-traversal/description/
 */
class Solution {
   public:
    /**
     * BFS 中序遍历 102的结果逆序
     */
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == nullptr) return ans;
        queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            // 当前层的结点个数
            int levelSize = queue.size();
            cout << levelSize << endl;
            vector<int> list;
            // 控制弹出当前层的所有元素
            for (int i = 0; i < levelSize; i++) {  // 循环 size 次
                TreeNode* front = queue.front();
                queue.pop();
                list.push_back(front->val);
                if (front->left) {
                    queue.push(front->left);
                }
                if (front->right) {
                    queue.push(front->right);
                }
            }
            ans.push_back(list);
        }
        // 逆转数组
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {
        {3, 9, 20, null, null, 15, 7}, {3, 9, 20, 10, 11, 15, 7}, {1, null, 2}};
    for (auto& i : arr) {
        vector<vector<int>> ans = s->levelOrderBottom(new TreeNode(i));
        for (auto& j : ans) {
            cout << "[";
            for (auto& k : j) {
                cout << k << " ";
            }
            cout << "]";
        }
        cout << endl;
    }
}