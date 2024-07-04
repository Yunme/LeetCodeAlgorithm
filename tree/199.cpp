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
 * 199：二叉树的右视图
 *
 * 给定一个二叉树的 根节点
 * root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
 *
 * https://leetcode.cn/problems/binary-tree-right-side-view/description/
 */
class Solution {
   public:
    /**
     * 层序遍历 
     */
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        if (root == nullptr) return ans;
        queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            int size = queue.size();
            // 每一层的数据
            for (int i = 1; i <= size; i++) {
                TreeNode* front = queue.front();
                queue.pop();
                // 最后一个就是最右边的节点
                if (i == size) {
                    ans.push_back(front->val);
                }
                if (front->left) {
                    queue.push(front->left);
                }
                if (front->right) {
                    queue.push(front->right);
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{1, 2, 3, null, 5, null, 4}, {1, null, 3}};
    for (int i = 0; i < list.size(); i++) {
        auto ans = s->rightSideView(new TreeNode(list[i]));
        for (auto j : ans) {
            cout << j << " ";
        }
        cout << endl;
    }
}