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
 * 513：找树左下角的值
 *
 * 给定一个二叉树的 根节点 root，请找出该二叉树的 最底层 最左边 节点的值。
 * 假设二叉树中至少有一个节点。
 *
 * https://leetcode.cn/problems/find-bottom-left-tree-value/description/
 */
class Solution {
   public:
    /**
     * DFS
     */
    void dfs(TreeNode* root, int height, int& currentVal, int& maxHeight) {
        if (root == nullptr) return;
        height++;
        dfs(root->left, height, currentVal, maxHeight);
        dfs(root->right, height, currentVal, maxHeight);
        if (height > maxHeight) {
            maxHeight = height;
            currentVal = root->val;
        }
    }
    int findBottomLeftValue(TreeNode* root) {
        if (root == nullptr) return 0;
        int currentVal = 0, currentHeight = 0;
        dfs(root, 0, currentVal, currentHeight);
        return currentVal;
    }
    /**
     * 法2：BFS 层序遍历 从左到右
     * 遍历每一层
     * 更新结果为左边的结点
     */
    int findBottomLeftValue2(TreeNode* root) {
        if (root == nullptr) return -1;
        queue<TreeNode*> queue;
        queue.push(root);
        int ans = root->val;
        while (!queue.empty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                TreeNode* front = queue.front();
                queue.pop();
                // 当前层最左侧结点
                if (i == 0) {
                    // 每层更新结果
                    ans = front->val;
                }
                if (front->left) queue.push(front->left);
                if (front->right) queue.push(front->right);
            }
        }
        return ans;
    }

    /**
     * 法3：BFS 层序遍历 从右到左
     * 最后一个值就是最左侧最
     */
    int findBottomLeftValue3(TreeNode* root) {
        if (root == nullptr) return -1;
        queue<TreeNode*> queue;
        queue.push(root);
        int ans = root->val;
        while (!queue.empty()) {
            TreeNode* front = queue.front();
            queue.pop();
            // 从右向左遍历
            if (front->right) queue.push(front->right);
            if (front->left) queue.push(front->left);
            ans = front->val;
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {
        {2, 1, 3},
        {1, 2, 3, 4, null, 5, 6, null, null, null, null, 7},
        {2, null, 3, null, 4, null, 5, null, 6}};
    for (auto& i : arr) {
        auto ans = s->findBottomLeftValue(new TreeNode(i));
        cout << ans << endl;
    }
}