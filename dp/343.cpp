#include <math.h>

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
 * 343: 整数拆分
 * 给定一个正整数 n ，将其拆分为 k 个 正整数 的和（ k >= 2
 * ），并使这些整数的乘积最大化。 返回 你可以获得的最大乘积 。
 *
 * https://leetcode.cn/problems/integer-break/description/
 */
class Solution {
   public:
    /**
     * 动态规划 O(n^2) O(n)
     * dp[i]: i 拆分成至少两个正整数后的最大乘积
     */
    int integerBreak(int n) {
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 0;
        for (int i = 2; i <= n; i++) {
            // 拆分成 j 和 i - j
            for (int j = 1; j < i; j++) {
                // 只拆分成 j, (i - j) => j*(i-j)
                // (i - j) 继续拆分 => j * dp[i-j]
                dp[i] = max({j * (i - j), j * dp[i - j], dp[i]});
            }
            cout << dp[i] << " ";
        }
        cout << endl;
        return dp[n];
    }

    /**
     * 动态规划 O(n) O(n)
     */
    int integerBreak2(int n) {
        if (n <= 3) return n - 1;
        vector<int> dp(n + 1);
        dp[2] = 1;
        for (int i = 3; i <= n; i++) {
            dp[i] =
                max({2 * (i - 2), 2 * dp[i - 2], 3 * (i - 3), 3 * dp[i - 3]});
            cout << dp[i] << " ";
        }
        cout << endl;
        return dp[n];
    }

    /**
     * 数学公式
     */
    int integerBreak3(int n) {
        if (n <= 3) return n - 1;
        int quotient = n / 3;
        int remainder = n % 3;
        if (remainder == 0)
            return (int)pow(3, quotient);
        else if (remainder == 1)
            return (int)pow(3, quotient - 1) * 4;
        else
            return (int)pow(3, quotient) * 2;
    }
};

int main() {
    Solution* s = new Solution();
    vector<int> list = {2, 10};
    for (auto i : list) {
        int count = s->integerBreak3(i);
        cout << count << endl << endl;
    }
}