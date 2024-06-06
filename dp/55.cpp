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
using namespace std;

/**
 * 55:跳跃游戏
 * 给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。
 * 数组中的每个元素代表你在该位置可以跳跃的最大长度。
 * 判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。
 *
 * https://leetcode.cn/problems/jump-game/description/
 */
class Solution {
   public:
    /**
     * 法1：动态规划 自己实现
     */
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return true;
        // dp 数组表示 第i个位置 最远能被第几个位置到达 index 值最小
        vector<int> dp(n, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            // 当前步数，接下来几个设置成当前 index
            for (int j = 1; j <= nums[i] && i + j < n; j++) {
                dp[i + j] = min(i, dp[i + j]);  // 取最小值
                // 如果 index 可以更小，则更新
                // 当前 dp 里存储的 index，对应的 index 更小
                if (dp[i + j] < n && dp[i + j] > dp[dp[i + j]]) {
                    dp[i + j] = dp[dp[i + j]];
                }
            }
        }
        for (auto i : dp) {
            cout << i << " ";
        }
        // 最后一个是0 则满足要求
        return dp[n - 1] == 0;
    }

    /**
     * 法2：贪心
     * 从 0 开始维护一个当前能到达的最大值；
     * 遍历每个位置，实时更新最远能够到达的位置，
     * 对于当前位置x，如果在最远能够到达的位置内，则最大位置更新为 x + nums[x],
     * 最远到达的位置大于数组中的最后一个位置 那就满足题意；
     * 否则不满足
     */
    bool canJump2(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return true;
        // 最远能到达的位置
        int maxReachPos = 0;
        for (int i = 0; i < n; i++) {
            // 当前位置在能到达的范围内
            if (i <= maxReachPos) {
                // 尝试更新
                maxReachPos = max(maxReachPos, i + nums[i]);
                // 最远能到达的位置 覆盖了最后一个位置 
                // 返回true
                if (maxReachPos >= n - 1) return true;
            }
        }
        return false;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{2, 3, 1, 1, 4}, {3, 2, 1, 0, 4}};
    for (auto i : list) {
        bool ans = s->canJump(i);
        cout << (ans ? "true" : "false") << endl;
    }
}