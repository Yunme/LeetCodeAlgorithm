#include <math.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 392: 判断子序列
 * 给定字符串 s 和 t ，判断 s 是否为 t 的子序列。
 * 字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。
 * （例如，"ace"是"abcde"的一个子序列，而"aec"不是）。
 *
 *
 * 进阶：
 * 如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >=10亿，
 * 你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？
 * https://leetcode.cn/problems/is-subsequence/description/
 */

class Solution {
   public:
    /**
     * 法1：双指针法 O(m + n)
     * 注意子串在主串中可以不是连续的。
     * @param s 子序列
     * @param t 主串
     */
    bool isSubsequence(string s, string t) {
        int i = 0, j = 0;
        // 遍历两个串，
        // 字符相等时 共同前进
        // 不相等时，t 的指针前进
        while (i < t.length() && j < s.length()) {
            if (t[i] == s[j]) {
                j++;
            }
            i++;
        }
        if (j == s.length()) {
            return true;
        }
        return false;
    }

    /**
     * 法2：动态规划 O (m * n) O(m * n) 空间可以压缩
     * 判断两个字符串的最长公共子序列
     * 是否等于 s 串的长度
     */
    bool isSubsequence2(string s, string t) {
        int m = s.length();
        int n = t.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        // 常规公共子序列判断
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n] == s.length();
    }

    /**
     * 法3：动态规划 预处理 t 串法
     * 如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >=10亿，
     * dp[i][j]: t 串中[i, size - 1] 字符j 第一次出现的索引
     * 字符范围：小写字母
     */
    bool isSubsequence3(string s, string t) {
        int m = s.length();
        int n = t.length();
        if (m == 0 && n == 0) return true;
        if (n == 0) return false;

        // 预处理
        // 26个小写字母
        // 默认位置为 n 即超过范围
        vector<vector<int>> dp(n, vector<int>(26, n));
        // 状态转移
        // j == t[i] 时 dp[i][j] = i
        // j != t[i] 时 dp[i][j] = dp[i+1][j]
        // 从后向前遍历
        dp[n - 1][t.back() - 'a'] = n - 1;  // 最后一个字符
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j < 26; j++) {
                if (t[i] == 'a' + j) {
                    dp[i][j] = i;
                } else {
                    dp[i][j] = dp[i + 1][j];
                }
            }
        }

        // for (int i = 0; i < n; i++) {
        //     if (i == 0) {
        //         for (int j = 0; j < 26; j++) {
        //             cout << (char)(j + 'a') << " ";
        //         }
        //         cout << endl;
        //     }
        //     for (int j = 0; j < 26; j++) {
        //         cout << dp[i][j] << " ";
        //     }
        //     cout << endl;
        // }

        // 检查 s 串
        int j = 0;
        for (int i = 0; i < s.length(); i++) {
            // s 中字符位置 index
            int charIndex = s[i] - 'a';
            if (j >= n || dp[j][charIndex] >= n) return false;  // 超出范围 返回false
            j = dp[j][charIndex] + 1;  // t 中下一个起始位置 当前位置已经被占用
        }
        return true;
    }
};

int main() {
    Solution *s = new Solution();

    vector<string> listS = {"abc", "axc", "aaaaaa", "b"};
    vector<string> listT = {"ahbgdc", "ahbgdc", "bbaaaa", "c"};

    for (int i = 0; i < listS.size(); i++) {
        bool ans = s->isSubsequence3(listS[i], listT[i]);
        cout << ans << endl;
    }
}