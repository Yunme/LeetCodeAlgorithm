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
 * 257：二叉树的所有路径
 *
 * 给你一个二叉树的根节点 root ，按 任意顺序
 * 返回所有从根节点到叶子节点的路径。 叶子节点 是指没有子节点的节点。
 *
 * https://leetcode.cn/problems/binary-tree-paths/description/
 */
class Solution {
   public:
    /**
     * DFS
     */
    void dfs(TreeNode* root, string temp, vector<string>& ans) {
        if (root == nullptr) return;
        // 拼接当前结点值
        temp.append(to_string(root->val));
        // 碰到叶子结点 保存结果
        if (root->left == nullptr && root->right == nullptr) {
            ans.push_back(temp);
            return;
        }
        temp.append("->");
        dfs(root->left, temp, ans);
        dfs(root->right, temp, ans);
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        if (root == nullptr) return {};
        vector<string> ans;
        string temp;
        dfs(root, temp, ans);
        return ans;
    }

    /**
     * BFS 两个队列
     * 一个保存结点用于遍历
     * 一个保存路径
     */
    vector<string> binaryTreePaths2(TreeNode* root) {
        if (root == nullptr) return {};
        vector<string> ans;
        // 结点
        queue<TreeNode*> nodeQueue;
        // 路径
        queue<string> pathQueue;
        // 根结点
        nodeQueue.push(root);
        pathQueue.push(to_string(root->val));
        while (!nodeQueue.empty()) {
            TreeNode* front = nodeQueue.front();
            nodeQueue.pop();
            string path = pathQueue.front();
            pathQueue.pop();
            // 碰到叶子结点 保存当前路径
            if (front->left == nullptr && front->right == nullptr) {
                ans.push_back(path);
                continue;
            }
            if (front->left) {
                // 左孩子
                nodeQueue.push(front->left);
                string newPath = path;
                newPath.append("->").append(to_string(front->left->val));
                pathQueue.push(newPath);
            }
            if (front->right) {
                // 右孩子
                nodeQueue.push(front->right);
                string newPath = path;
                newPath.append("->").append(to_string(front->right->val));
                pathQueue.push(newPath);
            }
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{1, 2, 3, null, 5},
                               {1, null, 2},
                               {2, null, 3, null, 4, null, 5, null, 6}};
    for (auto& i : arr) {
        auto ans = s->binaryTreePaths2(new TreeNode(i));
        for (auto s : ans) {
            cout << s << " ";
        }
        cout << endl;
    }
}