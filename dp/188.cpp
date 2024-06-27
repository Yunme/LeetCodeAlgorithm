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
 * 188: 买卖股票的最佳时机 IV
 * 给你一个整数数组 prices 和一个整数 k ，其中 prices[i] 是某支给定的股票在第 i
 * 天的价格。 设计一个算法来计算你所能获取的最大利润。你最多可以完成 k
 * 笔交易。也就是说，你最多可以买 k 次，卖 k 次。
 * 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 *
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iv/
 */
class Solution {
   public:
    /**
     * 动态规划 ，空间压缩略
     */
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) return 0;
        // n 天最多只能进行 n / 2 次交易
        k = min(k, n / 2);
        // 第 i 天
        // 第 k 次交易 买
        vector<vector<int>> buy(n, vector<int>(k, -prices[0]));
        // 第 k 次交易 卖
        vector<vector<int>> sell(n, vector<int>(k));

        for (int i = 1; i < n; i++) {
            // 首次交易
            buy[i][0] = max(buy[i - 1][0], -prices[i]);
            sell[i][0] =
                max(sell[i - 1][0], buy[i - 1][0] + prices[i]);  // 当天卖出
            // 第 j 次交易
            for (int j = 1; j < k; j++) {
                // 一买一卖算一次交易
                // 这次买 用上次卖后的余额
                buy[i][j] = max(buy[i - 1][j], sell[i - 1][j - 1] - prices[i]);
                sell[i][j] = max(sell[i - 1][j], buy[i - 1][j] + prices[i]);
            }
        }
        return sell[n - 1][k - 1];
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {
        {3, 3, 5, 0, 0, 3, 1, 4}, {2, 4, 1}, {3, 2, 6, 5, 0, 3}};
    vector<int> ks = {2, 2, 2};
    for (int i = 0; i < list.size(); i++) {
        int ans = s->maxProfit(ks[i], list[i]);
        cout << ans << endl;
    }
}