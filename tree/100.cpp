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
 * 100: 相同的树
 * 给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同。
 * 如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。
 *
 * https://leetcode.cn/problems/same-tree/description/
 */
class Solution {
   public:
    /**
     * 法1：递归法 DFS
     */
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr)  // 同时为空相同
            return true;
        else if (p && q && p->val == q->val) {
            // 不为空，且值相同，递归左子树和右子树
            return isSameTree(p->left, q->left) &&
                   isSameTree(p->right, q->right);
        } else {  // 否则 false
            return false;
        }
    }

    /**
     * 法2：迭代法 BFS
     * 层序遍历流程
     * 两个 queue 分别存放两个树的结点
     */
    bool isSameTree2(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr) {
            return true;
        } else if (p == nullptr || q == nullptr) {
            return false;
        }

        queue<TreeNode*> queue1, queue2;
        queue1.push(p);
        queue2.push(q);
        while (!queue1.empty() && !queue2.empty()) {
            TreeNode* node1 = queue1.front();
            queue1.pop();
            TreeNode* node2 = queue2.front();
            queue2.pop();
            // 当前不同 返回false
            if (node1->val != node2->val) return false;
            // 进入下一层
            TreeNode* left1 = node1->left;
            TreeNode* right1 = node1->right;
            TreeNode* left2 = node2->left;
            TreeNode* right2 = node2->right;
            // 下一层结构左孩子 结构不同
            // 异或，不同的返回 true，相同的返回 false
            if (left1 == nullptr ^ left2 == nullptr) {
                return false;
            }
            // 下一层结构右孩子 结构不同
            if (right1 == nullptr ^ right2 == nullptr) {
                return false;
            }
            // 下一层
            if (left1) queue1.push(left1);
            if (right1) queue1.push(right1);
            if (left2) queue2.push(left2);
            if (right2) queue2.push(right2);
        }
        // 如果最后都遍历完，队列都为空 则相同
        return queue1.empty() && queue2.empty();
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr1 = {{1, 2, 3}, {1, 2}, {1, 2, 1}};
    vector<vector<int>> arr2 = {{1, 2, 3}, {1, null, 2}, {1, 1, 2}};
    for (int i = 0; i < arr1.size(); i++) {
        auto ans = s->isSameTree2(new TreeNode(arr1[i]), new TreeNode(arr2[i]));
        cout << ans << endl;
    }
}