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
 * 714：买卖股票的最佳时机含手续费
 * 给定一个整数数组 prices，其中 prices[i]表示第 i 天的股票价格 ；整数 fee
 * 代表了交易股票的手续费用。
 * 你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
 * 返回获得利润的最大值。
 * 注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。。
 *
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/description/
 */
class Solution {
   public:
    /**
     * 动态规划
     */
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        if (n <= 1) return 0;
        vector<vector<int>> dp(n, vector<int>(2));
        // 第 i 天交易结束后 持有股票
        dp[0][0] = -prices[0];
        // 第 i 天交易结束后 不持有股票
        dp[0][1] = 0;
        for (int i = 1; i < n; i++) {
            // 持有 从前一天转移，或买入
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            // 不持有，从前一天转移，或卖出 减去手续费
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i] - fee);
        }

        for (int i = 0; i < n; i++) {
            cout << dp[i][0] << " " << dp[i][1] << endl;
        }
        return dp[n - 1][1] > 0 ? dp[n - 1][1] : 0;
    }

     /**
     * 动态规划 空间压缩
     */
    int maxProfit2(vector<int>& prices, int fee) {
        int n = prices.size();
        if (n <= 1) return 0;
        // 第 i 天交易结束后 持有股票
        int buy = -prices[0];
        // 第 i 天交易结束后 不持有股票
        int sell = 0;
        for (int i = 1; i < n; i++) {
            // 持有 从前一天转移，或买入
            int lastBuy = buy;
            buy = max(buy, sell - prices[i]);
            // 不持有，从前一天转移，或卖出 减去手续费
            sell = max(sell, lastBuy + prices[i] - fee);
        }

        return sell;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{1, 3, 2, 8, 4, 9},
                                {1, 3, 7, 5, 10, 3},
                                {9, 8, 7, 1, 2},
                                {2, 1, 4, 4, 2, 3, 2, 5, 1, 2}};
    vector<int> frees = {2, 3, 3, 1};
    for (int i = 0; i < list.size(); i++) {
        int ans = s->maxProfit2(list[i], frees[i]);
        cout << ans << endl;
    }
}