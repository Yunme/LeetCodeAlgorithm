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
 * 654: 最大二叉树
 * 给定一个不重复的整数数组 nums 。 最大二叉树 可以用下面的算法从 nums
 * 递归地构建: 创建一个根节点，其值为 nums 中的最大值。 递归地在最大值 左边 的
 * 子数组前缀上 构建左子树。 递归地在最大值 右边 的 子数组后缀上 构建右子树。
 * 返回 nums 构建的 最大二叉树 。
 *
 * https://leetcode.cn/problems/maximum-binary-tree/description/
 */
class Solution {
   private:
    /**
     * nums数组中 [left, right] 区间中的最大值 index
     */
    int maxValIndex(vector<int>& nums, int left, int right) {
        int maxIndex = left;
        int maxVal = nums[left];
        for (int i = left; i <= right; i++) {
            if (maxVal < nums[i]) {
                maxVal = nums[i];
                maxIndex = i;
            }
        }
        return maxIndex;
    }

   public:
    /**
     * 法1：递归模拟 O(n^2) O(n)
     */
    TreeNode* build(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        int index = maxValIndex(nums, left, right);
        TreeNode* root = new TreeNode(nums[index]);

        // 缩小区间

        // 左子树 left 不动， right 修改为 index-1
        root->left = build(nums, left, index - 1);
        // 右子树 right 不动， left 修改为 index + 1
        root->right = build(nums, index + 1, right);
        return root;
    }
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return nullptr;
        return build(nums, 0, n - 1);
    }

    /**
     * 法2：单调栈 O(n) O(n)
     * 维护从栈底到栈顶单调递减的单调栈
     * 栈顶元素大于待插入元素，直接入栈（待插入元素较小）栈顶元素.right =
     * 待插入元素
     * 栈顶元素小于待插入元素，栈顶出栈（待插入元素较大）待插入元素.left =
     * 栈顶元素
     */
    TreeNode* constructMaximumBinaryTree2(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return nullptr;
        stack<TreeNode*> stack;
        for (int i = 0; i < n; i++) {
            TreeNode* node = new TreeNode(nums[i]);
            while (!stack.empty()) {
                TreeNode* top = stack.top();
                if (top->val > node->val) {
                    stack.push(node);
                    top->right = node;
                    break;
                } else {
                    stack.pop();
                    node->left = top;
                }
            }
            if (stack.empty()) stack.push(node);
        }
        // 最后栈底的是跟结点
        TreeNode* root = nullptr;
        while (!stack.empty()) {
            root = stack.top();
            stack.pop();
        }
        return root;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> list = {{3, 2, 1, 6, 0, 5}, {3, 2, 1}, {5}};

    for (int i = 0; i < list.size(); i++) {
        auto root = s->constructMaximumBinaryTree2(list[i]);
        root->print();
        cout << endl;
    }
}