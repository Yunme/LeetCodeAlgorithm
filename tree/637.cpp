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
 * 637: 二叉树的层平均值
 *
 * 给定一个非空二叉树的根节点 root ,
 * 以数组的形式返回每一层节点的平均值。与实际答案相差 10-5
 * 以内的答案可以被接受。
 *
 * https://leetcode.cn/problems/average-of-levels-in-binary-tree/description/
 */
class Solution {
   public:
    /**
     * 层序遍历
     */
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> ans;
        if (root == nullptr) return ans;
        queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            int size = queue.size();
            // 每一层的数据
            long long sum = 0;
            for (int i = 1; i <= size; i++) {
                TreeNode* front = queue.front();
                queue.pop();
                sum += front->val;
                if (front->left) {
                    queue.push(front->left);
                }
                if (front->right) {
                    queue.push(front->right);
                }
            }
            double average = (double)sum / size;
            ans.push_back(average);
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{3, 9, 20, null, null, 15, 7},
                                {3, 9, 20, 15, 7}};
    for (int i = 0; i < list.size(); i++) {
        auto ans = s->averageOfLevels(new TreeNode(list[i]));
        for (auto j : ans) {
            cout << j << " ";
        }
        cout << endl;
    }
}