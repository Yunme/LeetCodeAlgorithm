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
 * 617: 合并二叉树
 *
 * 给你两棵二叉树： root1 和 root2 。
 * 想象一下，当你将其中一棵覆盖到另一棵之上时，两棵树上的一些节点将会重叠（而另一些不会）。你需要将这两棵树合并成一棵新二叉树。合并的规则是：如果两个节点重叠，那么将这两个节点的值相加作为合并后节点的新值；否则，不为
 * null 的节点将直接作为新二叉树的节点。 返回合并后的二叉树。 注意:
 * 合并过程必须从两个树的根节点开始。
 *
 * https://leetcode.cn/problems/merge-two-binary-trees/description/
 */
class Solution {
   public:
    /**
     * 法1：DFS 递归方法
     */
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        TreeNode* root = nullptr;
        // 都为空时，合并后为空
        if (root1 == nullptr && root2 == nullptr) {
            return nullptr;
        }
        // 某个为空时，合并后为另一个
        if (root1 == nullptr) return root2;
        if (root2 == nullptr) return root1;
        // 都不为空时，相加
        root = new TreeNode(root1->val + root2->val);
        root->left = mergeTrees(root1->left, root2->left);
        root->right = mergeTrees(root1->right, root2->right);
        return root;
    }

    /**
     * 法2：BFS 层序遍历法
     * 一个队列 同时 push 进去两个结点
     * 合并到一个结点上 不新建结点
     */
    TreeNode* mergeTrees2(TreeNode* root1, TreeNode* root2) {
        // 某个为空时，合并后为另一个
        if (root1 == nullptr) return root2;
        if (root2 == nullptr) return root1;
        queue<TreeNode*> queue;
        queue.push(root1);
        queue.push(root2);
        while (!queue.empty()) {
            TreeNode* node1 = queue.front();
            queue.pop();
            TreeNode* node2 = queue.front();
            queue.pop();
            // 合并到 node1 上
            node1->val += node2->val;
            if (node1->left && node2->left) {
                queue.push(node1->left);
                queue.push(node2->left);
            }
            if (node1->right && node2->right) {
                queue.push(node1->right);
                queue.push(node2->right);
            }
            // 关联
            if (node1->left == nullptr && node2->left) {
                node1->left = node2->left;
            }
            if (node1->right == nullptr && node2->right) {
                node1->right = node2->right;
            }
        }
        return root1;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list1 = {{1, 3, 2, 5}};
    vector<vector<int>> list2 = {{2, 1, 3, null, 4, null, 7}};
    for (int i = 0; i < list1.size(); i++) {
        auto ans =
            s->mergeTrees2(new TreeNode(list1[i]), new TreeNode(list2[i]));
        ans->print();
        cout << endl;
    }
}