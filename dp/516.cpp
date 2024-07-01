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
 * 516: 最长回文子序列
 * 给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度。
 * 子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。
 *
 * https://leetcode.cn/problems/longest-palindromic-subsequence/description/
 */
class Solution {
   public:
    /**
     * 动态规划 O(n^2) O(n^2)
     * dp[i][j]：s[i,j]子序列 最长回文长度
     * s[i] == s[j] 时：dp[i][j] = dp[i + 1][j - 1] + 2  加入了两个字符
     *
     * 不相等时，两字符同时加入不能扩大回文长度，所以每个方向单独加入，取最大值:dp[i][j]
     * = max(dp[i+1][j], dp[i][j-1])
     */
    int longestPalindromeSubseq(string s) {
        int n = s.length();
        // dp[i][j] s[i,j]子序列 最长回文长度
        vector<vector<int>> dp(n, vector<int>(n));
        dp[0][0] = 0;
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;  // 单个字符是回文 长度为1
        }
        // 状态转移 根据转移方程：i,j 处值取决于 左下，下，左
        for (int i = n - 1; i >= 0; i--) {  // 逆序遍历
            for (int j = i + 1; j < n; j++) {
                if (s[i] == s[j]) {
                    // 加入了两个字符
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    // 相等时，两字符同时加入不能扩大回文长度，所以每个方向单独加入，取最大值
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][n - 1];
    }
};

int main() {
    Solution* s = new Solution();
    vector<string> list = {"bbbab", "cbbd"};
    vector<int> answers = {3, 6};
    for (auto i : list) {
        int count = s->longestPalindromeSubseq(i);
        cout << count << endl;
    }
}