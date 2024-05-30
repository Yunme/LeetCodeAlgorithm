#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 10: 正则表达式匹配
 * 给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*'
 * 的正则表达式匹配。
 * '.' 匹配任意单个字符
 * '*' 匹配零个或多个前面的那一个元素
 * 所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。
 * https://leetcode.cn/problems/regular-expression-matching/description/
 */
class Solution {
   public:
    /**
     * 动态规划
     */
    bool isMatch(string s, string p) {
        int len1 = s.length();
        int len2 = p.length();
        // 二维 dp 数组表示
        //  dp[i][j] s 的前i个能否被 p 的前j个匹配 不包含i和j
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));
        dp[0][0] = 1;  // 空串可以匹配
        // s 为空，p 包含* 有可能匹配
        for (int j = 1; j < len2 + 1; j++) {
            // 前一位为*，其前面的可以出现0次 那么干掉一个字符
            if (p[j - 1] == '*') dp[0][j] = dp[0][j - 2];
        }
        // p为空，那么都不匹配
        for (int i = 1; i < len1 + 1; i++) {
            for (int j = 1; j < len2 + 1; j++) {
                // 当前末尾都相等 或者 p 末尾是.
                if (s[i - 1] == p[j - 1] || p[j - 1] == '.') {
                    // 那么前 i 和 j 跟之前相等
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*') {
                    // 当前 p 末尾是 *
                    // 当前 s 末尾 == * 前面那个 或者 它是.
                    if (s[i - 1] == p[j - 2] || p[j - 2] == '.') {
                        // * 匹配 0 次 dp[i][j-2]
                        // * 匹配1次或多次 dp[i-1][j]
                        dp[i][j] = dp[i][j - 2] || dp[i - 1][j];
                    } else {
                        // 当前 s 末尾 与 * 前面那个无法匹配
                        // 只能匹配 0 次
                        dp[i][j] = dp[i][j - 2];
                    }
                }
            }
        }

        cout << endl;
        for (int i = 0; i < len1 + 1; i++) {
            for (int j = 0; j < len2 + 1; j++) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        return dp[len1][len2];
    }
};

int main() {
    Solution* solution = new Solution();
    vector<string> arr = {
        "aa", "aaaaab", "absdasdasdsdas", "accccdef", "aab", "ab", "aaa",
        "a",  "",       "bbbba"};
    vector<string> arrP = {"a",   "a*b", ".*",  "a.c*d.f", "c*a*b",
                           ".*c", "a*a", "ab*", "z*",      ".*a*a"};
    for (int i = 0; i < arr.size(); i++) {
        cout << arrP[i] << " match " << arr[i] << ": ";
        int ans = solution->isMatch(arr[i], arrP[i]);
        if (ans)
            cout << "true" << endl;
        else
            cout << "false" << endl;
    }
    return 0;
}