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
 * 121: 买卖股票的最佳时机
 * 给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i
 * 天的价格。 你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子
 * 卖出该股票。设计一个算法来计算你所能获取的最大利润。
 * 返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/description/
 */
class Solution {
   public:
    /**
     * 法1：暴力求解 O(n^2)
     * 遍历每天买出，在后面的每一天卖出，求收益计算最大值。
     */
    int maxProfit(vector<int>& prices) {
        int count = prices.size();
        int maxProfit = 0;
        for (int i = 0; i < count; i++) {
            for (int j = i + 1; j < count; j++) {
                if (prices[j] > prices[i]) {
                    maxProfit = max(maxProfit, prices[j] - prices[i]);
                }
            }
        }
        return maxProfit;
    }

    /**
     * 法2：动态规划 时间 O(n), 空间 O(n)
     * 前面暴力法中 对于第 i 天之后的最大价格计算重复了。
     * 可以考虑使用 dp 数组缓存
     */
    int maxProfit2(vector<int>& prices) {
        int count = prices.size();
        if (count <= 1) return 0;

        // dp 数组元素：第 i 天之后的最大价格, 最后一天买入没法卖出，不计算
        int m = count - 1;
        vector<int> dp(m);
        int maxProfit = 0;
        // 倒数第二天之后的最大价格，只能是倒数第一天的价格
        dp[m - 1] = prices[m];
        for (int i = m - 2; i >= 0; i--) {
            // 第 i 天之后的最大价格 = max(第i+1天之后的最大价格,
            // 第i+1天当天价格)
            dp[i] = max(dp[i + 1], prices[i + 1]);
        }

        // max(每天之后最大的价格 - 当天的价格)
        for (size_t i = 0; i < m; i++) {
            cout << dp[i] << " ";
            maxProfit = max(dp[i] - prices[i], maxProfit);
        }

        cout << endl;
        return maxProfit;
    }

    /**
     * 动态规划 O(n) O(n)
     */
    int maxProfit3(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) return 0;
        // dp[i][0] 第i天交易结束后持有股票的利润
        // dp[i][1] 第i天交易结束后不持有股票的利润
        vector<vector<int>> dp(n, vector<int>(2));
        // 初始化
        dp[0][0] = -prices[0];  // 第一天买入后利润为负的
        dp[0][1] = 0;
        // 状态转移
        for (int i = 1; i < n; i++) {
            // 第 i 天持有，i - 1天就持有，或者第 i 天买入
            dp[i][0] = max(dp[i - 1][0], -prices[i]);

            // 第 i 天不持有 i - 1天就不持有，
            // 或者第 i 天卖出 = i - 1天持有时 + i 天的价格
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2; j++) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        // 肯定是不持有多，即卖出
        return dp[n - 1][1];
    }

    /**
     * 动态规划压缩空间 O(n) O(1)
     */
    int maxProfit4(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) return 0;
        // dp[i][0] 第i天交易结束后持有股票的利润
        // dp[i][1] 第i天交易结束后不持有股票的利润
        // 初始化
        int hold = -prices[0];  // 第一天买入后利润为负的
        int nonHeld = 0;
        // 状态转移
        for (int i = 1; i < n; i++) {
            // 第 i 天持有，i - 1天就持有，或者第 i 天买入
            int lastHold = hold;
            hold = max(hold, -prices[i]);

            // 第 i 天不持有 i - 1天就不持有，
            // 或者第 i 天卖出 = i - 1天持有时 + i 天的价格
            nonHeld = max(nonHeld, lastHold + prices[i]);
        }
        // 肯定是不持有多，即卖出
        return nonHeld;
    }

    /**
     * 法3：贪心思想 一次遍历，时间：O(n), 空间 O(1)
     * 找到最低价格买入，在后面的最高价出卖出
     */
    int maxProfit5(vector<int>& prices) {
        int minPrice = INT_MAX;
        int maxProfit = 0;
        for (int i = 0; i < prices.size(); i++) {
            int price = prices[i];
            // 最低价格
            if (price < minPrice) {
                minPrice = price;
            } else if (price - minPrice > maxProfit) {
                // 最大利润
                maxProfit = price - minPrice;
            }
        }
        return maxProfit;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{7, 1, 5, 3, 6, 4}, {7, 6, 4, 3, 1}};
    for (auto i : list) {
        int count = s->maxProfit4(i);
        cout << count << endl;
    }
}