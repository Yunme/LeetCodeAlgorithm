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
 * 746: 使用最小花费爬楼梯
 *
 * 给你一个整数数组 cost ，其中 cost[i] 是从楼梯第 i
 * 个台阶向上爬需要支付的费用。
 * 一旦你支付此费用，即可选择向上爬一个或者两个台阶。
 * 你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。
 * 请你计算并返回达到楼梯顶部的最低花费。
 *
 * https://leetcode.cn/problems/min-cost-climbing-stairs/description/
 */
class Solution {
   public:
    /**
     * 动态规划 O(n) O(n)
     */
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        // dp[i] 表示到达 i 楼梯时的最小花费
        vector<int> dp(n + 1);
        dp[0] = 0;  // 起始就在 0
        dp[1] = 0;  // 起始可以在1，最小花费为 0

        for (int i = 2; i < n + 1; i++) {
            // i 可以从 i-1 花费 cost[i-1] 来，或者从 i-2花费 cost[i-2] 来
            // 取其较小值
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }
        for (int i = 0; i < n + 1; i++) {
            cout << dp[i] << " ";
        }
        cout << endl;
        return dp[n];
    }

    /**
     * 动态规划 O(n) O(1)
     * 空间压缩
     */
    int minCostClimbingStairs2(vector<int>& cost) {
        int n = cost.size();
        // dp[i] 表示到达 i 楼梯时的最小花费

        int a = 0;  // 起始就在 0
        int b = 0;  // 起始可以在1，最小花费为 0
        int c = b;
        for (int i = 2; i < n + 1; i++) {
            // i 可以从 i-1 花费 cost[i-1] 来，或者从 i-2花费 cost[i-2] 来
            // 取其较小值
            c = min(b + cost[i - 1], a + cost[i - 2]);
            a = b;
            b = c;
        }
        return c;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{10, 15, 20},
                                {1, 100, 1, 1, 1, 100, 1, 1, 100, 1}};
    for (auto i : list) {
        int count = s->minCostClimbingStairs2(i);
        cout << count << endl;
    }
}