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
 * 309：买卖股票的最佳时机含冷冻期
 * 给定一个整数数组prices，其中第  prices[i] 表示第 i 天的股票价格
 * 。​
 * 设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:
 * 卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
 * 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 *
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/
 */
class Solution {
   public:
    /**
     * 动态规划 O(n)
     * 每天交易完成后可能的状态
     * 只跟前一天有关
     */
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) return 0;
        vector<vector<int>> dp(n, vector<int>(3));
        dp[0][0] = -prices[0];  // 某天交易后持有股票
        dp[0][1] = 0;  // 某天交易后处于冷冻期（今天卖出）
        dp[0][2] = 0;  // 某天交易后不持有股票且不处于冷冻期
        for (int i = 1; i < n; i++) {
            // 持有
            // 从前一天延续，或当天买入，但是前一天不能是冷冻期
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][2] - prices[i]);
            // 处于冷冻期
            // 在前一天必须持有，说明今天卖出
            dp[i][1] = dp[i - 1][0] + prices[i];
            // 不持有且不在冷冻期。从前面延续 或 前一天是冷冻期
            dp[i][2] = max(dp[i - 1][2], dp[i - 1][1]);
        }
        return max(dp[n - 1][1], dp[n - 1][2]);
    }

    /**
     * 动态规划 O(n) 空间压缩
     * i 只与 i - 1有关
     */
    int maxProfit2(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) return 0;
        int buy = -prices[0];  // 某天交易后持有股票
        int sell = 0;  // 某天交易后处于冷冻期（今天卖出）
        int free = 0;  // 某天交易后不持有股票且不处于冷冻期
        for (int i = 1; i < n; i++) {
            // 持有
            // 从前一天延续，或当天买入，但是前一天不能是冷冻期
            buy = max(buy, free - prices[i]);
            // 不持有且不在冷冻期。从前面延续 或 前一天是冷冻期
            free = max(free, sell);
            // 在前一天必须持有，说明今天卖出
            // 处于冷冻期
            sell = buy + prices[i];
        }
        return max(sell, free);
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{1, 2, 3, 0, 2}, {1}};
    vector<int> ks = {2, 2, 2};
    for (int i = 0; i < list.size(); i++) {
        int ans = s->maxProfit2(list[i]);
        cout << ans << endl;
    }
}