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
 * 501: 二叉搜索树中的众数
 *
 * 给你一个含重复值的二叉搜索树（BST）的根节点 root ，找出并返回 BST 中的所有
 * 众数（即，出现频率最高的元素）。 如果树中有不止一个众数，可以按 任意顺序
 * 返回。 假定 BST 满足如下定义： 结点左子树中所含节点的值 小于等于 当前节点的值
 * 结点右子树中所含节点的值 大于等于 当前节点的值
 * 左子树和右子树都是二叉搜索树
 *
 * https://leetcode.cn/problems/find-mode-in-binary-search-tree/description/
 */
class Solution {
   public:
    /**
     * 法1：迭代 O(n) O(n)
     * 中序遍历后的数组中寻找出现频率最高的元素
     */
    vector<int> findMode(TreeNode* root) {
        if (root == nullptr) return {};
        vector<int> ans;
        stack<TreeNode*> stack;
        TreeNode* node = root;
        vector<int> list;
        while (node || !stack.empty()) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
            node = stack.top();
            list.push_back(node->val);
            stack.pop();
            node = node->right;
        }
        if (list.size() == 1) {
            return {list[0]};
        }
        // 有序数组寻找出现频率最高的数，可能有多个相同次数的
        int tempCount = 0;
        int maxCount = 0;
        int base = list[0];
        for (int i = 0; i < list.size(); i++) {
            // 相同 累加
            if (list[i] == base) {
                tempCount++;
            } else {
                // 不相同 置为 1 当前数个数
                tempCount = 1;
                base = list[i];
            }
            if (tempCount == maxCount) {
                // 与目前频率最高的个数相同，保存
                ans.push_back(base);
            } else if (tempCount > maxCount) {
                maxCount = tempCount;
                // 有更大的频率了 清空结果集
                ans.clear();
                ans.push_back(base);
            }
        }
        return ans;
    }

    /**
     * 法2：递归 O(n) O(1)
     * 递归中序 找最高频率的
     */
    int base = INT_MIN, tempCount = 0, maxCount = 0;
    vector<int> findMode2(TreeNode* root) {
        if (root == nullptr) return {};
        vector<int> ans;
        dfs(root, ans);
        return ans;
    }
    void dfs(TreeNode* root, vector<int>& ans) {
        if (root == nullptr) return;
        dfs(root->left, ans);
        // 更新频率
        updateMost(root->val, ans);
        dfs(root->right, ans);
    }
    void updateMost(int val, vector<int>& ans) {
        if (val == base) {
            tempCount++;
        } else {
            tempCount = 0;
            base = val;
        }
        if (tempCount == maxCount) {
            ans.push_back(base);
        } else if (tempCount > maxCount) {
            maxCount = tempCount;
            ans.clear();
            ans.push_back(base);
        }
    }
};

int main() {
    vector<vector<int>> arr = {
        {2, 1, 2}, {0}, {1, null, 2}, {1, 0, 1, 0, 0, 1, 1, 0}};
    for (auto& i : arr) {
        Solution* s = new Solution();
        auto ans = s->findMode2(new TreeNode(i));
        for (auto j : ans) {
            cout << j << " ";
        }
        cout << endl;
    }
}