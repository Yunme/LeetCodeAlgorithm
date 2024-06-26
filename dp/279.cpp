#include <math.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
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
 * 279：完全平方数
 *
 * 给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。
 * 完全平方数是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。
 * 例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。
 * https://leetcode.cn/problems/perfect-squares/description/
 *
 */
class Solution {
   public:
    /**
     * 转化为动态规划问题
     * 完全背包
     * n: 背包容量
     * 完全平方数为物品
     */
    int numSquares(int n) {
        // dp[j] 当 和为 j 时，完全平方数的最小数量
        // 初始化为 n，最大为 n 个 1 相加等于n
        vector<int> dp(n + 1, n);
        dp[0] = 0;
        // n 本身可能是完全平方数
        for (int i = 1; i <= n; i++) {
            double sq = sqrt(i);
            if (sq != floor(sq)) {
                continue;
            }
            // cout << i << " ";
            for (int j = i; j <= n; j++) {
                // 取较小值
                dp[j] = min(dp[j - i] + 1, dp[j]);
            }
        }
        for (int j = 0; j <= n; j++) cout << dp[j] << " ";
        cout << endl;
        return dp[n];
    }

    /**
     * 动规 优化写法
     */
    int numSquares2(int n) {
        // dp[j] 当 和为 j 时，完全平方数的最小数量
        // 初始化为 n，最大为 n 个 1 相加等于n
        vector<int> dp(n + 1, n);
        dp[0] = 0;
        // n 本身可能是完全平方数
        for (int i = 1; i * i <= n; i++) {
            // cout << i << " ";
            for (int j = i * i; j <= n; j++) {
                // 取较小值
                dp[j] = min(dp[j - i * i] + 1, dp[j]);
            }
        }
        return dp[n];
    }
};

int main() {
    double a = sqrt(4);
    // bool b = a == floor(a)
    // cout << (a == floor(a)) << endl;
    Solution* s = new Solution();
    vector<int> list = {12, 13, 1, 4};
    for (int i = 0; i < list.size(); i++) {
        int ans = s->numSquares2(list[i]);
        cout << ans << endl;
    }
}