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
 * 1143: 最长公共子序列
 *
 * 定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列
 * 的长度。如果不存在 公共子序列 ，返回 0 一个字符串的 子序列
 * 是指这样一个新的字符串：
 * 它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
 * 例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
 * 两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。
 *
 * https://leetcode.cn/problems/longest-common-subsequence/description/
 */
class Solution {
   public:
    /**
     * 动态规划 O(m*n) O(m*n)
     */
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();
        // dp[i][j]: text1[0, i-1] text2[0, j-1] 最长公共子序列长度
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        // 转移方程为：
        // 如果当前相等 取 dp[i - 1][j - 1] + 1
        // 如果不相等 延续 dp[i - 1][j], dp[i][j - 1] 较大值
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    // 当前相等 取共同的上一位
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    // 当前不相等，取各自上一位的最大值
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        return dp[m][n];
    }

    /**
     * 动态规划 O(m*n) O(n)
     * 空间压缩
     */
    int longestCommonSubsequence2(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();
        // dp[i][j]: text1[0, i-1] text2[0, j-1] 最长公共子序列长度
        vector<int> dp(n + 1);
        // 转移方程为：
        // 如果当前相等 取 dp[i - 1][j - 1] + 1
        // 如果不相等 延续 dp[i - 1][j], dp[i][j - 1] 较大值
        // 依赖上面的、左边的、和左上角的
        for (int i = 1; i <= m; i++) {
            // 暂存 dp[i-1][j-1] 左上角
            int leftTop = 0;
            for (int j = 1; j <= n; j++) {
                // 计算下一位之前 存储当前值，就是上一行的数据
                int temp = dp[j];
                if (text1[i - 1] == text2[j - 1]) {
                    // 当前相等 取共同的上一位
                    dp[j] = leftTop + 1;  // 取上一行的值
                } else {
                    // 当前不相等，取各自上一位的最大值
                    dp[j] = max(dp[j], dp[j - 1]);
                }
                // 保存到外层
                leftTop = temp;
            }
        }
        for (int j = 1; j <= n; j++) {
            cout << dp[j] << " ";
        }
        cout << endl;
        return dp[n];
    }
};

int main() {
    Solution* s = new Solution();
    vector<string> list1 = {"abcde", "abc", "abc", "jmjkbkjkv"};
    vector<string> list2 = {"ace", "abc", "def", "bsbininm"};
    for (int i = 0; i < list1.size(); i++) {
        int count = s->longestCommonSubsequence2(list1[i], list2[i]);
        cout << count << endl;
    }
}