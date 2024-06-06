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
 * 45:跳跃游戏II
 * 给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。
 * 数组中的每个元素代表你在该位置可以跳跃的最大长度。
 *
 * 返回到达 nums[n - 1] 的最小跳跃次数。生成的测试用例可以到达 nums[n - 1]。
 *
 * https://leetcode.cn/problems/jump-game-ii/description/
 */
class Solution {
   public:
    /**
     * 法1：动态规划 O(n) O(n)
     * dp数组存储，能1步到达i位置的最小index
     * 解是：从dp最后一个位置出发到达0的步数
     */
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;
        // dp 数组表示 第i个位置 最远能被第几个位置直接1步内到达
        vector<int> dp(n, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            // 当前i处位置能到达的位置 ，接下来几个设置成当前 index
            for (int j = 1; j <= nums[i] && i + j < n; j++) {
                dp[i + j] = min(i, dp[i + j]);  // 取最小值
            }
        }
        // 计算次数
        int i = n - 1, ans = 0;
        while (i > 0) {
            i = dp[i];
            ans++;
        }

        for (auto i : dp) {
            cout << i << " ";
        }
        cout << endl;
        return ans;
    }

    /**
     * 法2：贪心法
     * 正向查找，每次到达最远的位置，记录步数
     */
    int jump2(vector<int>& nums) {
        int ans = 0;
        int start = 0;
        int end = 1;
        while (end < nums.size()) {
            int maxPos = 0;
            for (int i = start; i < end; i++) {
                // 能跳到最远的距离
                maxPos = max(maxPos, i + nums[i]);
            }
            start = end;       // 下一次起跳点范围开始的格子
            end = maxPos + 1;  // 下一次起跳点范围结束的格子
            ans++;             // 跳跃次数
        }
        return ans;
    }
    /**
     * 法3：贪心法 简介版本
     * 正向查找，每次到达最远的位置，记录步数
     */
    int jump3(vector<int>& nums) {
        int n = nums.size();
        // 跳跃次数
        int ans = 0;
        // 目前能到达的最远位置
        int maxPosition = 0;
        // 上次跳跃可达的范围的右边界（下次的起跳点）
        int end = 0;
        for (int i = 0; i < n - 1; i++) {
            maxPosition = max(maxPosition, i + nums[i]);
            // 到达上次跳跃能到达的右边界
            if (i == end) {
                end = maxPosition;
                ans++;
            }
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{2, 3, 1, 1, 4}, {2, 3, 0, 1, 4}};
    for (auto i : list) {
        int ans = s->jump2(i);
        cout << ans << endl;
    }
}