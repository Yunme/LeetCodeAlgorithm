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
 * 198：打家劫舍
 * 你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
 *
 * 给定一个代表每个房屋存放金额的非负整数数组，计算你
 * 不触动警报装置的情况下，一夜之内能够偷窃到的最高金额。
 *
 * https://leetcode.cn/problems/house-robber/description/
 */
class Solution {
   public:
    /**
     * 法1：动态规划 O(n) O(n)
     * dp[i] 表示前 i 间房能偷盗到的最大金额
     */
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        // 表示前 i 间房能偷盗到最大金额
        vector<int> dp(n + 1);
        dp[0] = 0;        // 前 0 间房 为 0
        dp[1] = nums[0];  // 前 1 间房 为 nums[0]
        // 对于大于 1 的第 i 家，要么偷要么不偷
        // 偷，第 i-1 家不能偷了
        // 不偷，
        for (int i = 2; i <= n; i++) {
            // 前 i 间房的 =
            // 最大值
            // 偷第i家 = dp[i-2] + nums[i - 1]  i-1不能偷
            // 不偷第i家 = dp[i-1]
            dp[i] = max(dp[i - 2] + nums[i - 1], dp[i - 1]);
            cout << dp[i] << " ";
        }
        cout << endl;
        return dp[n];
    }

    /**
     * 法2：动态规划 O(n) O(n)
     * dp[i] 表示前 i 间房能偷盗到的最大金额
     * 包含 i
     */
    int rob2(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        // 表示前 i 间房能偷盗到最大金额
        vector<int> dp(n + 1);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[n - 1];
    }

    /**
     * 法3：动态规划 空间压缩 O(n) O(1)
     * 由于 i 只跟 i-1 或 i-2  有关，
     * 滚动数组
     */
    int rob3(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        int a = nums[0];
        int b = max(nums[0], nums[1]);
        int c = b;
        for (int i = 2; i < n; i++) {
            c = max(a + nums[i], b);
            a = b;  // 前移
            b = c;
        }
        return c;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{1, 2, 3, 1}, {2, 7, 9, 3, 1},
                                {1, 2, 3, 4}, {0},
                                {2, 1, 1, 2}, {1, 3, 1, 3, 100}};
    for (auto i : list) {
        int count = s->rob3(i);
        cout << count << endl << endl;
    }
}