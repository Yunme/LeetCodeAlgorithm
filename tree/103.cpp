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
 * 103：二叉树的锯齿形层序遍历
 * 给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。
 * （即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。
 *
 * https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/description/
 */
class Solution {
   public:
    /**
     * BFS 中序遍历
     * 双端队列存储 每层数据。
     * 一层添加到队列头，下一层添加到队列尾
     */
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == nullptr) return ans;
        queue<TreeNode*> queue;
        queue.push(root);
        bool reverse = false;
        while (!queue.empty()) {
            // 当前层的结点个数
            int levelSize = queue.size();
            // cout << levelSize << endl;
            deque<int> list;
            // 控制弹出当前层的所有元素
            for (int i = 0; i < levelSize; i++) {  // 循环 size 次
                TreeNode* front = queue.front();
                queue.pop();
                if (reverse) {
                    list.push_front(front->val);
                } else {
                    list.push_back(front->val);
                }

                if (front->left) {
                    queue.push(front->left);
                }
                if (front->right) {
                    queue.push(front->right);
                }
            }
            reverse = !reverse;
            ans.push_back(vector<int>(list.begin(), list.end()));
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {
        {3, 9, 20, null, null, 15, 7}, {3, 9, 20, 10, 11, 15, 7}, {1, null, 2}};
    for (auto& i : arr) {
        vector<vector<int>> ans = s->zigzagLevelOrder(new TreeNode(i));
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