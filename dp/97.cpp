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
 * 97：交错字符串
 * 给定三个字符串 s1、s2、s3，请你帮忙验证 s3 是否是由 s1 和 s2 交错 组成的。
 * 两个字符串 s 和 t 交错 的定义与过程如下，其中每个字符串都会被分割成若干 非空
 * 子字符串：
 *
 * s = s1 + s2 + ... + sn
 * t = t1 + t2 + ... + tm
 * |n - m| <= 1
 * 交错 是 s1 + t1 + s2 + t2 + s3 + t3 + ... 或者 t1 + s1 + t2 + s2 + t3 + s3 +
 * ... 注意：a + b 意味着字符串 a 和 b 连接。
 *
 * https://leetcode.cn/problems/interleaving-string/description/
 */
class Solution {
   public:
    /**
     * 动态规划 类似于 62：不同路径
     * O(m*n) O(m*n)
     * dp[i][j]：s1中的 前i个、 s2中的 前j个，能组成 s3中的前 i+j个
     */
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.length();
        int n = s2.length();
        if (s3.length() != m + n) {
            return false;
        }
        // dp[i][j]：s1中的 前i个、 s2中的 前j个，能组成 s3中的前 i+j个
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        // 初始化 空和空 能组成空
        dp[0][0] = 1;
        // 当前位置相同，且前一个能组成 那么当前也能组成
        // s2作为行，第一行
        for (int j = 1; j <= n; j++) {
            // 前j个，最后一个index为 j-1
            if (s2[j - 1] == s3[j - 1] && dp[0][j - 1]) {
                dp[0][j] = 1;
            }
        }
        // s1作为列，第一列
        for (int i = 1; i <= m; i++) {
            // 前i个，最后一个index为 i-1
            if (s1[i - 1] == s3[i - 1] && dp[i - 1][0]) {
                dp[i][0] = 1;
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // 当于 i-1 相同时 且 i-1和j能组成，那么就能组成
                if (s3[i + j - 1] == s1[i - 1] && dp[i - 1][j]) {
                    dp[i][j] = 1;
                }
                // 当于 j-1相同时，且 i 和j-1能组成，那么就能组成
                if (s3[i + j - 1] == s2[j - 1] && dp[i][j - 1]) {
                    dp[i][j] = 1;
                }

                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        return dp[m][n];
    }
};

int main() {
    Solution* s = new Solution();
    vector<pair<string, string>> list = {{"aabcc", "dbbca"},
                                         {"aabcc", "dbbca"},
                                         {"a", ""}};
    vector<string> target = {"aadbbcbcac", "aadbbbaccc", "a"};
    for (int i = 0; i < list.size(); i++) {
        bool ans = s->isInterleave(list[i].first, list[i].second, target[i]);
        cout << ans << endl;
    }
}