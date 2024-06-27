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
 * 123: 买卖股票的最佳时机 III
 * 给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
 * 设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。
 * 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 *
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii/description/
 */
class Solution {
   public:
    /**
     * 动态规划思想 O(n) O(n)
     * 每天交易后的状态
     */
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) return 0;
        // 每天交易完后可能的状态
        // 不持有，持有1笔，持有一笔后卖出完成交易，在完成一次交易后买入第二笔；完成两笔交易
        // 第一次持有1笔，第一次不持有，第二次持有；第二次不持有
        // dp[i][j] 第 i 天交易结束后对应上面状态的最大利润
        vector<vector<int>> dp(n, vector<int>(5));
        dp[0][0] = -prices[0];  // 买入一笔
        dp[0][1] = 0;           // 当天买入卖出 收益 0
        dp[0][2] = -prices[0];  // 当天买入卖出，再买入
        dp[0][3] = 0;           // 当天买入卖出买入卖出，收益0
        for (int i = 1; i < n; i++) {
            // 第 i 天持有，前一天就持有 还是当天买入
            dp[i][0] = max(dp[i - 1][0], -prices[i]);
            // 第 i 天完成交易，前一天就完成 还是这天卖出：前一天买入 + 当天价格
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
            // 第 i 天买入持有第二笔
            dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] - prices[i]);
            // 第 i 天完成第二笔交易
            dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] + prices[i]);
        }
        return dp[n - 1][3];
    }

    /**
     * 动态规划思想 空间压缩 O(n) O(1)
     * 每天交易后的状态
     */
    int maxProfit2(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) return 0;
        // 每天交易完后可能的状态 不持有肯定无利润，所以忽略
        // 第一次持有1笔，第一次不持有，第二次持有；第二次不持有
        int buy1 = -prices[0];  // 买入一笔
        int sell1 = 0;          // 当天买入卖出 收益 0
        int buy2 = -prices[0];  // 当天买入卖出，再买入
        int sell2 = 0;          // 当天买入卖出买入卖出，收益0
        for (int i = 1; i < n; i++) {
            // 第 i 天持有，前一天就持有 还是当天买入
            buy1 = max(buy1, -prices[i]);
            // 第 i 天完成交易，前一天就完成 还是这天卖出：前一天买入 + 当天价格
            sell1 = max(sell1, buy1 + prices[i]);
            // 第 i 天买入持有第二笔
            buy2 = max(buy2, sell1 - prices[i]);
            // 第 i 天完成第二笔交易
            sell2 = max(sell2, buy2 + prices[i]);
        }
        return sell2;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {
        {3, 3, 5, 0, 0, 3, 1, 4}, {1, 2, 3, 4, 5}, {7, 6, 4, 3, 1}, {1}};
    for (auto i : list) {
        int ans = s->maxProfit2(i);
        cout << ans << endl;
    }
}