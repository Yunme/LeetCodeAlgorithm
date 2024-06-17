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
 * 509：斐波那契数列
 * 斐波那契数 （通常用 F(n) 表示）形成的序列称为 斐波那契数列 。该数列由 0 和 1
 * 开始，后面的每一项数字都是前面两项数字的和。也就是：
 *
 * F(0) = 0，F(1) = 1
 * F(n) = F(n - 1) + F(n - 2)，其中 n > 1
 * 给定 n ，请计算 F(n) 。
 *
 * https://leetcode.cn/problems/fibonacci-number/description/
 */
class Solution {
   public:
    /**
     * 法1：递归实现
     * 直接根据定义写
     */
    int fib(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        return fib(n - 1) + fib(n - 2);
    }

    /**
     * 法2: 动态规划 O(n) O(n)
     * dp 数组缓存
     */
    int fib2(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        // dp[i] 表示 i 的斐波那契数
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            // 状态转移
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }

    /**
     * 法3: 动态规划 空间压缩 O(n) O(1)
     * 只跟前两个值有关 滚边数组
     */
    int fib3(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        int a = 0;
        int b = 1;
        int c = 1;
        for (int i = 2; i <= n; i++) {
            // 状态转移
            c = a + b;
            a = b;
            b = c;
        }
        return c;
    }
};

int main() {
    Solution* s = new Solution();
    vector<int> list = {2, 3, 4, 12};
    for (auto i : list) {
        int ans = s->fib3(i);
        cout << ans << endl;
    }
}