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
 * 98：验证二叉搜索树
 * 给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。
 *
 * 有效 二叉搜索树定义如下：
 * 节点的左子树只包含 小于 当前节点的数。
 * 节点的右子树只包含 大于 当前节点的数。
 * 所有左子树和右子树自身必须也是二叉搜索树
 *
 * https://leetcode.cn/problems/validate-binary-search-tree/description/
 */
class Solution {
   public:
    /**
     * 中序遍历 是否递增
     */
    bool isValidBST(TreeNode* root) {
        TreeNode *node = root, *prev = nullptr;
        stack<TreeNode*> stack;
        while (node || !stack.empty()) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
            node = stack.top();
            stack.pop();
            // 不递增 返回 false
            if (prev && node->val <= prev->val) {
                return false;
            }
            prev = node;
            node = node->right;
        }
        return true;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr1 = {
        {2, 1, 3}, {5, 1, 4, null, null, 3, 6}, {2, 2, 2}};
    for (int i = 0; i < arr1.size(); i++) {
        auto ans = s->isValidBST(new TreeNode(arr1[i]));
        cout << ans << endl;
    }
}