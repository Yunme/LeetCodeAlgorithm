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
 * 100: 对称二叉树
 * 给你一个二叉树的根节点 root ， 检查它是否轴对称。
 *
 * 沿中轴左右对称
 * https://leetcode.cn/problems/symmetric-tree/description/
 */
class Solution {
   public:
    /**
     *  中序遍历结果对称 回文 (方案错误)
     *  比如：中序遍历结果：2 2 1 2 2 但不对称
     *     1
     *  2    2
     * 2    2
     */
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        stack<TreeNode*> stack;
        TreeNode* p = root;
        vector<int> ans;
        while (p || !stack.empty()) {
            if (p) {
                // 依次入栈左孩子
                stack.push(p);
                p = p->left;
            } else {
                // 左孩子为空后，出栈
                TreeNode* front = stack.top();
                stack.pop();
                ans.push_back(front->val);
                // 入栈右孩子
                p = front->right;
            }
        }

        for (auto& n : ans) {
            cout << n << " ";
        }
        cout << endl;

        // 判断数组是否对称
        int i = 0, j = ans.size() - 1;
        while (i <= j) {
            if (ans[i] != ans[j]) return false;
            i++;
            j--;
        }
        return true;
    }

    /**
     * 法1：对称 递归
     * 两个结点值相同，且一个的左孩子与另个右孩子值相等，一个右孩子与另一个左孩子值相等
     */
    bool isSymmetricHelper(TreeNode* left, TreeNode* right) {
        // 同为 空 对称
        if (left == nullptr && right == nullptr) return true;
        // 只有一个为空 不对称
        if (left == nullptr || right == nullptr) return false;

        if (left && right) {
            // 值相等，且左左和右右，左右和右左 也对称
            return left->val == right->val &&
                   isSymmetricHelper(left->left, right->right) &&
                   isSymmetricHelper(left->right, right->left);
        }
        return false;
    }
    bool isSymmetric2(TreeNode* root) {
        if (root == nullptr) return true;
        return isSymmetricHelper(root->left, root->right);
    }

    /**
     * 迭代 队列
     * 每次入队两个
     */
    bool isSymmetric3(TreeNode* root) {
        if (root == nullptr || root->left == nullptr && root->right == nullptr)
            return true;
        queue<TreeNode*> queue;
        queue.push(root->left);
        queue.push(root->right);
        while (!queue.empty()) {
            // 队列中取出两个结点 比较
            TreeNode* left = queue.front();
            queue.pop();
            TreeNode* right = queue.front();
            queue.pop();
            // 相等继续
            if (left == nullptr && right == nullptr) continue;
            // 不相等 有一个为 null 不对称 返回  false
            if (left == nullptr || right == nullptr) return false;
            if (left->val != right->val) return false;

            // 分别放入左左，右右
            queue.push(left->left);
            queue.push(right->right);

            // 左右，右左
            queue.push(left->right);
            queue.push(right->left);
        }
        return true;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{1, 2, 2, 3, 4, 4, 3},
                               {1, 2, 2, null, 3, null, 3}};
    for (int i = 0; i < arr.size(); i++) {
        auto ans = s->isSymmetric2(new TreeNode(arr[i]));
        cout << ans << endl;
    }
}