#include <math.h>

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
 * 377: 组合总和 IV
 * 给你一个由 不同 整数组成的数组 nums ，和一个目标整数 target 。请你从 nums
 * 中找出并返回总和为 target 的元素组合的个数。 题目数据保证答案符合 32
 * 位整数范围。
 *
 * https://leetcode.cn/problems/combination-sum-iv/description/
 */
class Solution {
   public:
    /**
     * 转换为 完全背包问题
     * 求排列数, 强调顺序
     */
    int combinationSum4(vector<int>& nums, int target) {
        int n = nums.size();
        // dp[i][j]: 选[0,i)之间的数，和为 j 的组合数
        vector<vector<int>> dp(n + 1, vector<int>(target + 1));
        // 初始化 i = 0
        dp[0][0] = 1;
        for (int j = 1; j <= target; j++) {
            dp[0][j] = 0;
        }
        // 转移方程为：选i和不选i的组合数累加n
        for (int j = 0; j <= target; j++) {
            for (int i = 1; i <= n; i++) {
                if (j >= nums[i - 1]) {
                    // 足够
                    dp[i][j] = dp[i - 1][j] + dp[n][j - nums[i - 1]];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= target; j++) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        return dp[n][target];
    }
    /**
     * 转换为 完全背包问题
     * 空间压缩版本
     * 求排列数, 强调顺序 先遍历背包 否则先遍历物品
     *
     * 与爬楼梯一致
     */
    int combinationSum4_2(vector<int>& nums, int target) {
        int n = nums.size();
        // dp[j]: 和为j 的组合数
        vector<int> dp(target + 1);

        // 转移方程为：
        // dp[j] = 累加 {dp[j - nums[i]]}
        dp[0] = 1;
        for (int j = 0; j <= target; j++) {
            for (int i = 0; i < n; i++) {
                if (j >= nums[i]) {
                    // 累加
                    dp[j] = dp[j] + dp[j - nums[i]];
                }
            }
        }
        for (int j = 0; j <= target; j++) {
            cout << dp[j] << " ";
        }
        cout << endl;
        return dp[target];
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{1, 2, 3}, {9}};
    vector<int> target = {4, 3};
    for (int i = 0; i < list.size(); i++) {
        int count = s->combinationSum4(list[i], target[i]);
        cout << count << endl << endl;
    }
}