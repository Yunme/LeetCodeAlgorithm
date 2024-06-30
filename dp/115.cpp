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
 * 115：不同的子序列
 *
 * 给你两个字符串 s 和 t ，统计并返回在 s 的 子序列 中 t 出现的个数，结果需要对
 * 109 + 7 取模。
 *
 * https://leetcode.cn/problems/distinct-subsequences/description/
 */
class Solution {
   public:
    typedef unsigned long long ull;
    /**
     * 动态规划 O(m n) O(m n)
     * 相当于在 s 中删除字符后等于 t，有多少种删法
     * dp[i][j] : s[0, i-1] 中匹配 t[0, i-1] 的个数
     */
    int numDistinct(string s, string t) {
        int m = s.length();
        int n = t.length();
        if (n > m) return 0;
        // dp[i][j] : s[0, i-1] 中匹配 t[0, i-1] 的个数
        vector<vector<ull>> dp(m + 1, vector<ull>(n + 1));
        // 初始化 第一行 dp[0][j]
        dp[0][0] = 1;  // 空和空匹配个数为 1
        for (int j = 1; j <= n; j++) {
            dp[0][j] = 0;  // s空字符串匹配 t 中非空，个数为 0
        }
        // 第一列 dp[i][1]
        for (int i = 1; i <= m; i++) {
            dp[i][0] = 1;  // s 非空 匹配 t 中空，个数位 1
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    // 相等时，分为 删除当前位 或 不删除
                    // 可以都删除 s[i - 1] : dp[i - 1][j - 1]
                    // 只删除 s[i - 1] : dp[i - 1][j]
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                } else {
                    // 不相等时：只删除 s[i - 1]
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        // int max = pow(10, 9) + 7;
        return dp[m][n];
    }

    /**
     * 动态规划 O(m n) O(n) 空间压缩版本
     * dp[i][j] 只与 dp[i-1][j-1] 和 dp[i-1][j] 有关
     * 相当于在 s 中删除字符后等于 t，有多少种删法
     * dp[i][j] : s[0, i-1] 中匹配 t[0, i-1] 的个数
     */
    int numDistinct2(string s, string t) {
        int m = s.length();
        int n = t.length();
        if (n > m) return 0;
        // dp[i][j] : s[0, i-1] 中匹配 t[0, i-1] 的个数
        vector<ull> dp(n + 1);
        // 初始化 第一行 dp[0][j]
        dp[0] = 1;  // 空和空匹配个数为 1
        for (int j = 1; j <= n; j++) {
            dp[j] = 0;  // s空字符串匹配 t 中非空，个数为 0
        }
        for (int i = 1; i <= m; i++) {
            // 与上一行的 当前个和前一个有关 倒序遍历
            for (int j = n; j >= 1; j--) {
                if (s[i - 1] == t[j - 1]) {
                    // 相等时，分为 删除当前位 或 不删除
                    // 可以都删除 s[i - 1] : dp[i - 1][j - 1]
                    // 只删除 s[i - 1] : dp[i - 1][j]
                    dp[j] = dp[j - 1] + dp[j];
                } else {
                    // // 不相等时：只删除 s[i - 1]
                    // dp[j] = dp[j];
                }
            }
        }
        // int max = pow(10, 9) + 7;
        return dp[n];
    }
};

int main() {
    Solution* s = new Solution();
    vector<string> listS = {"rabbbit", "babgbag"};
    vector<string> listT = {"rabbit", "bag"};
    vector<int> answer = {3, 5};
    for (int i = 0; i < listS.size(); i++) {
        int ans = s->numDistinct2(listS[i], listT[i]);
        cout << ans << endl;
    }
}