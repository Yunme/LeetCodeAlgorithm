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
 * 122: 买卖股票的最佳时机 II
 * 给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。
 * 在每一天，你可以决定是否购买和/或出售股票。
 * 你在任何时候 最多 只能持有 一股股票。
 * 你也可以先购买，然后在 同一天 出售。 返回 你能获得的 最大 利润 。
 *
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/description/
 */
class Solution {
   public:
    /**
     * 法1：贪心（自己实现）
     * 在低价买入，高价卖出
     */
    int maxProfit(vector<int>& prices) {
        int buyPrice = INT_MAX;
        int profit = 0;
        // 遍历数组
        for (int i = 0; i < prices.size(); i++) {
            int price = prices[i];
            // 低价买入
            if (price < buyPrice) {
                buyPrice = price;
            } else if (price > buyPrice) {
                // 价格大于买入价
                // 再按当天价买入
                profit += price - buyPrice;
                buyPrice = price;
            }
        }
        return profit;
    }

    /**
     * 法2：贪心，简洁写法
     * 因为不限制交易次数
     * 最大收益 就是上升趋势的收益总和
     */
    int maxProfit2(vector<int>& prices) {
        int profit = 0;
        for (int i = 1; i < prices.size(); i++) {
            // 只要价格上升就买入 卖出
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }
    /**
     * 法3：动态规划
     * 不能参与多笔交易，每天交易完后要么持有要么不持有股票
     */
    int maxProfit3(vector<int>& prices) {
        int n = prices.size();
        // dp 数组表示：i 从0开始
        // dp[i][0] 第i天交易后手里没有股票的最大利润
        // dp[i][1] 第i天交易后手里有股票的最大利润
        // 问题的解为 dp[n-1][0]  最后一天不持有的收益 比大于dp[n-1][1]
        vector<vector<int>> dp(n, vector<int>(2));
        // 初始化
        dp[0][0] = 0;           // 第0天只能买入，没法卖出，收益0
        dp[0][1] = -prices[0];  // 第0天只能买入，持有后，收益为 -prices[0]
        for (int i = 1; i < n; i++) {
            // 第i天交易后没有股票，要么是前一天就没有股票
            // 要么是前一天持有，今天卖出 = dp[i-1][1] + prices[i]
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);

            // 第i天交易后持有股票，要么是前一天就持有
            // 要么是前一天不持有，今天买入 当前收益减去买入价格
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        }
        return dp[n - 1][0];
    }
    /**
     * 法3：动态规划 空间压缩
     * 上述中 dp[i] 的状态只于前一天有关
     * 不使用数组就能完成状态转移
     */
    int maxProfit4(vector<int>& prices) {
        int n = prices.size();
        int dp0 = 0;           // 当前天交易完成不持有的最大收益
        int dp1 = -prices[0];  // 当前天交易完成持有的最大收益
        for (int i = 1; i < n; i++) {
            // 第i天交易后没有股票，要么是前一天就没有股票
            // 要么是前一天持有，今天卖出 = dp[i-1][1] + prices[i]
            int newDp0 = max(dp0, dp1 + prices[i]);
            // 第i天交易后持有股票，要么是前一天就持有
            // 要么是前一天不持有，今天买入 当前收益减去买入价格
            int newDp1 = max(dp1, dp0 - prices[i]);
            dp0 = newDp0;
            dp1 = newDp1;
        }
        return dp0;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {
        {7, 1, 5, 3, 6, 4}, {1, 2, 3, 4, 5}, {7, 6, 4, 3, 1}};
    for (auto i : list) {
        int ans = s->maxProfit4(i);
        cout << ans << endl;
    }
}