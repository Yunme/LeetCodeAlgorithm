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
 * 108：将有序数组转换为二叉搜索树
 * 给你一个整数数组 nums ，其中元素已经按 升序 排列，请你将其转换为一棵
 * 平衡二叉搜索树。
 *
 * https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/description/
 */
class Solution {
   public:
    /**
     * 递归插入 平衡二叉树
     */
    TreeNode* dfs(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        int mid = (left + right) / 2;
        TreeNode* node = new TreeNode(nums[mid]);
        node->left = dfs(nums, left, mid - 1);
        node->right = dfs(nums, mid + 1, right);
        return node;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // 取中间的为第一个要插入的
        int n = nums.size();
        if (n == 0) return nullptr;
        return dfs(nums, 0, n - 1);
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{-10, -3, 0, 5, 9}, {1, 3}};
    for (auto& i : arr) {
        s->sortedArrayToBST(i)->print();
    }
}