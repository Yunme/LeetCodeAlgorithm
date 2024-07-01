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
 * 647：回文子串
 * 给你一个字符串 s ，请你统计并返回这个字符串中 回文子串 的数目。
 * 回文字符串 是正着读和倒过来读一样的字符串。
 * 子字符串 是字符串中的由连续字符组成的一个序列。
 *
 * https://leetcode.cn/problems/palindromic-substrings/description/
 */
class Solution {
   public:
    /**
     * 法1：动态规划 O(n^2) O(n^2)
     */
    int countSubstrings(string s) {
        int n = s.length();
        int ans = n;
        // dp[i][j]  s[i, j] 子串是否是回文子串  i >= j
        vector<vector<int>> dp(n, vector<int>(n));
        // 初始化 单个字符是回文
        dp[0][0] = 1;
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        // 状态转移： dp[i][j] = dp[i+1][j-1] && s[i] == s[j]
        // 字符串相等时，小子串回文，大子串也是回文
        // 取决于 左下角，按列遍历
        for (int j = 1; j < n; j++) {
            for (int i = 0; i < j; i++) {
                if (s[i] == s[j]) {
                    // 两边字符相等时： 长度为2和3的子串必是回文
                    if (j - i == 1 || j - i == 2) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                    if (dp[i][j]) ans++;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }

        return ans;
    }

    /**
     * 法2：中心扩展法 O(n^2) O(1)
     */
    int countSubstrings2(string s) {
        int n = s.length();
        int ans = n;  // 单个字符也算
        // 中心可以是单个字符，也可以是双字符
        // 中心单个字符 共 n 个
        for (int i = 0; i < n; i++) {
            // aba  中间 一个字符肯定是回文 从前一个后一个开始
            int left = i - 1;
            int right = i + 1;
            // 向两边扩散
            while (left >= 0 && right < n && s[left] == s[right]) {
                left--;
                right++;
                ans++;
            }
        }

        // 中心双字符 共 n-1 个
        for (int i = 0; i < n - 1; i++) {
            // abba   两个字符不一定是回文 从当前和下一个开始
            int left = i;
            int right = i + 1;
            while (left >= 0 && right < n && s[left] == s[right]) {
                left--;
                right++;
                ans++;
            }
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<string> list = {"abc", "aaa"};
    vector<int> answers = {3, 6};
    for (auto i : list) {
        int count = s->countSubstrings2(i);
        cout << count << endl;
    }
}