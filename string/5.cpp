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
 * 5: 最长回文子串
 * 给定一个字符串，求其无重复字符的最长子串。
 * https://leetcode.cn/problems/longest-substring-without-repeating-characters/description
 */

/**
 * 滑动窗口
 */
class Solution {
   public:
    /**
     * 法1：暴力查找 耗时 O(n^3)
     * 双重循环找到所有子串 O(n^2), 检查每个字符串是否是回文 O(n)
     * 查找每个子串，检查它是否是回文串
     * 找到最长的返回
     */
    bool isPalindrome(string& s) {
        int i = 0, j = s.length() - 1;
        while (i <= j) {
            if (s[i] != s[j]) {
                return false;
            }
            i++;
            j--;
        }
        return true;
    }
    string longestPalindrome(string s) {
        int count = s.length();
        int maxLength = 0;
        string ans;
        for (int i = 0; i < count; i++) {
            for (int j = i; j < count; j++) {
                string sub = s.substr(i, j - i + 1);
                // cout << sub << " ";
                if (isPalindrome(sub) && sub.length() > maxLength) {
                    ans = sub;
                    maxLength = sub.length();
                }
            }
        }
        return ans;
    }

    /**
     * 法2：动态规划 耗时 O(n^2) 空间 O(n^2)
     *
     * 思路：dp[i][j] 表示 i~j 的子串是否是回文字符串
     * 如果 i~j 的子串是回文串，且 s[i-1] == s[j+1], 那么 i-1~j+1
     * 的串也比是回文串
     *
     * 当 j-i>=2时 那么状态转移方程就是：
     * dp[i][j] = dp[i+1][j-1] && s[i] == s[j];
     * i,j处的值依赖于后一行(i+1)和前一列(j-1)（左下方向）所以按列构建 dp 数组
     *
     * 当 j-i = 0时，同一个字符必是回文。
     * 当 j-i = 1时，两个字符如果相等，那也是回文，如果不等，那就不是。
     */
    string longestPalindrome2(string s) {
        int count = s.length();
        int maxLength = 1;
        int startIndex = 0;
        // dp 数组
        // 表示 i~j 的子串是否是回文字符串
        vector<vector<int>> dp(count, vector<int>(count));
        // 子串长度为1的，必是回文串，初始化
        for (int i = 0; i < count; i++) {
            dp[i][i] = 1;
        }
        // 递推
        // 根据子串长度，从2个开始
        // 按列构建
        for (int subLen = 2; subLen <= count; subLen++) {
            // i 是左边界
            for (int i = 0; i < count; i++) {
                int j = i + subLen - 1;  // j 是右边界 [i, j]
                if (j >= count) break;   // 右边界越界
                if (s[i] != s[j]) {
                    // 子串长度 >=2 时，不相等，肯定不是回文串
                    dp[i][j] = 0;
                } else {
                    // s[i] == s[j]
                    // 长度为2或3时 必是回文
                    if (subLen == 2 || subLen == 3) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }

                // 当前是回文，比较更大值
                if (dp[i][j] && subLen > maxLength) {
                    maxLength = subLen;
                    startIndex = i;
                }
            }
        }

        // cout << endl;
        // for (int i = 0; i < count; i++) {
        //     for (int j = 0; j < count; j++) {
        //         cout << dp[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        return s.substr(startIndex, maxLength);
    }

    /**
     * 法3：中心扩展法 时间 O(n^2) 空间 O(1)
     * 根据回文的定义，可以从一个位置向两边进行扩展，比如从 s[i+1]~s[j-1]扩展到
     * s[i]~s[j]， 如果 s[i] == s[j]，那么i~j的子串就是回文，
     * 如果不相等，那就不再是回文，以当前为中心的最大回文长度也就计算出来了。
     * 遍历所有的字符，就能算出最大值。
     */
    /**
     * 从left处，向左扩展
     * 从right处，向右扩展
     * 直到 left 和 right 处字符不相等，返回前一个相等时 left 和 right 值
     * [left, right]
     */
    pair<int, int> expandAroundCenter(const string& s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        return {left + 1, right - 1};
    }

    string longestPalindrome3(string s) {
        int count = s.length();
        int start, end = 0;
        for (int i = 0; i < count; i++) {
            // 奇数个回文串扩展
            auto [left1, right1] = expandAroundCenter(s, i, i);
            // 偶数个回文串扩展
            auto [left2, right2] = expandAroundCenter(s, i, i + 1);

            // 更新最长值。
            if (right1 - left1 > end - start) {
                start = left1;
                end = right1;
            }
            if (right2 - left2 > end - start) {
                start = left2;
                end = right2;
            }
        }
        return s.substr(start, end - start + 1);
    }
};

int main() {
    Solution* solution = new Solution();
    vector<string> arr = {"babad", "cbbd", "abbbba", "abbcbba", "a"};
    // vector<string> arr = {"babad"};
    for (string& s : arr) {
        cout << s << ":";
        string ans = solution->longestPalindrome3(s);
        // bool ans = solution->isPalindrome(s);
        cout << ans << endl;
    }
    return 0;
}