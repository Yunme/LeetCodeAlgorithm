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
 * 70: 爬楼梯
 * 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
 * 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
 *
 * https://leetcode.cn/problems/climbing-stairs/description/
 */
class Solution {
   public:
    /**
     * 法1：动态规划 O(n) O(n)
     * dp 数组表示，爬到第i阶楼梯的方法数
     * 由于每次爬一或二阶，转移方程为dp[i] = dp[i-1] + dp[i-2]
     * 等于两部分的和
     */
    int climbStairs(int n) {
        vector<int> dp(n + 1);
        dp[0] = 1;  // 0 设为 1种
        dp[1] = 1;  // 1 设为 1种
        for (int i = 2; i <= n; i++) {
            // 状态转移
            dp[i] = dp[i - 1] + dp[i - 2];
            cout << dp[i] << " ";
        }
        cout << endl;
        return dp[n];
    }

    /**
     * 法2：动态规划 空间压缩
     * 因为 dp[i] 只跟前两位有关
     * 滚边数组
     */
    int climbStairs2(int n) {
        int a = 1;  // 0 设为 1种
        int b = 1;  // 1 设为 1种
        int c = 1;
        for (int i = 2; i <= n; i++) {
            // 状态转移 
            c = a + b;
            a = b; 
            b = c;
            cout << c << " ";
        }
        cout << endl;
        return c;
    }
};

int main() {
    Solution* s = new Solution();
    vector<int> list = {1, 2, 3, 4};
    for (auto i : list) {
        int count = s->climbStairs2(i);
        cout << count << endl;
    }
}