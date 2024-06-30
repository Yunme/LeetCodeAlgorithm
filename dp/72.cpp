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
 * 72: 编辑距离
 *
 * 给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数
 * 你可以对一个单词进行如下三种操作：
 * - 插入一个字符
 * - 删除一个字符
 * - 替换一个字符
 * https://leetcode.cn/problems/edit-distance/description/
 */
class Solution {
   public:
    /**
     * 动态规划 O(mn) O(mn)
     */
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        // dp[i][j]: word1[0, i-1] 至少操作多少步 才能变成 word2[0, j-1]
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[0][0] = 0;  // 都为空已经相等 不需要操作j
        // 初始化 第一行 dp[0][j]    word1 为空，需要添加对应的 j 次
        for (int j = 1; j <= n; j++) {
            dp[0][j] = j;
        }
        // 第一列 dp[i][0] word2 为空，需要删除 word 1 i 次
        for (int i = 1; i <= m; i++) {
            dp[i][0] = i;
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    // 相等时 不需要操作
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // 不相等时
                    // 插入：dp[i][j-1]   插入到 word2 中 后取决于前一个
                    // 删除：dp[i-1][j]   删除 word1 中 后取决于 word1 的前一个
                    // 替换：dp[i-1][j-1] 替换 原地替换成一样的，相当于相等了
                    dp[i][j] =
                        min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]}) + 1;
                }
            }
        }
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        return dp[m][n];
    }

    /**
     * 动态规划 O(mn) O(n)
     * 空间压缩
     */
    int minDistance2(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        // dp[i][j]: word1[0, i-1] 至少操作多少步 才能变成 word2[0, j-1]
        vector<int> dp(n + 1);
        dp[0] = 0;  // 都为空已经相等 不需要操作j
        // 初始化 第一行 dp[0][j]    word1 为空，需要添加对应的 j 次
        for (int j = 1; j <= n; j++) {
            dp[j] = j;
        }
        // // 第一列 dp[i][0] word2 为空，需要删除 word 1 i 次
        // for (int i = 1; i <= m; i++) {
        //     dp[i][0] = i;
        // }
        for (int i = 1; i <= m; i++) {
            dp[0] = i;
            int leftTop = i - 1;
            for (int j = 1; j <= n; j++) {
                int temp = dp[j];
                if (word1[i - 1] == word2[j - 1]) {
                    // 相等时 不需要操作
                    dp[j] = leftTop;
                } else {
                    // 不相等时
                    // 插入：dp[i][j-1]   插入到 word2 中 后取决于前一个 相当于删除 j 里的一个元素
                    // 删除：dp[i-1][j]   删除 word1 中 后取决于 word1 的前一个
                    // 替换：dp[i-1][j-1] 替换 原地替换成一样的，相当于相等了
                    dp[j] = min({dp[j - 1], dp[j], leftTop}) + 1;
                }
                leftTop = temp;
            }
        }
        for (int j = 0; j <= n; j++) {
            cout << dp[j] << " ";
        }
        cout << endl;
        return dp[n];
    }
};

int main() {
    Solution* s = new Solution();
    vector<string> list1 = {"horse", "intention", "a"};
    vector<string> list2 = {"ros", "execution", "ab"};

    for (int i = 0; i < list1.size(); i++) {
        int count = s->minDistance2(list1[i], list2[i]);
        cout << count << endl;
    }
}