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
 * 538: 把二叉搜索树转换为累加树
 * 给出二叉 搜索 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater
 * Sum Tree）， 使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。
 * 提醒一下，二叉搜索树满足下列约束条件：
 *
 * 节点的左子树仅包含键 小于 节点键的节点。
 * 节点的右子树仅包含键 大于 节点键的节点。
 * 左右子树也必须是二叉搜索树。
 *
 * https://leetcode.cn/problems/convert-bst-to-greater-tree/description/
 */
class Solution {
   public:
    /**
     * BST 的中序遍历递增
     * 反中序遍历：右中左遍历 递减
     */
    int sum = 0;
    TreeNode* convertBST(TreeNode* root) {
        if (root == nullptr) return nullptr;
        convertBST(root->right);
        sum += root->val;
        root->val = sum;
        convertBST(root->left);
        return root;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {
        {4, 1, 6, 0, 2, 5, 7, null, null, null, 3, null, null, null, 8},
        {0, null, 1}};
    for (int i = 0; i < arr.size(); i++) {
        TreeNode* root = new TreeNode(arr[i]);
        auto ans = s->convertBST(root);
        ans->print();
    }
}