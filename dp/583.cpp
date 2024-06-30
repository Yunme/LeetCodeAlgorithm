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
 * 583:两个字符串的删除操作
 *
 * 给定两个单词 word1 和 word2 ，返回使得 word1 和  word2 相同所需的最小步数。
 * 每步 可以删除任意一个字符串中的一个字符。
 *
 * https://leetcode.cn/problems/delete-operation-for-two-strings/description/
 */
class Solution {
   public:
    /**
     * 动态规划 O(m n) O(m n)
     * dp[i][j] word1[0, i-1] word2[0, j-1] 最少删除多少步使其相等
     * 对应字符
     * 相等时 不需要删除 延续 dp[i-1][j-1]
     * 不相等时 取删除 word1 还是 word2 中的较小值 + 1: min(dp[i - 1][j],
     * dp[i][j - 1]) + 1;
     */
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        // dp[i][j] word1[0, i-1] word2[0, j-1] 最少删除多少步使其相等
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[0][0] = 0;  // 都为空 不需要删除
        // 初始化 dp[0][j]  // word1 为空时，需要删除  word2.length 步
        for (int j = 1; j <= n; j++) {
            dp[0][j] = j;
        }
        // 初始化 dp[i][0]  // word2 为空时，需要删除 word1.length 步
        for (int i = 1; i <= m; i++) {
            dp[i][0] = i;
        }

        // 状态转移
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // 相等时 当前不需要删除
                if (word1[i - 1] == word2[j - 1]) {
                    // 取决于各自前面一位
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // 不相等时，取 删除 word1 中和 word2 中的较小值
                    // 删除了一个 需要 + 1次
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;
                }
            }
        }
        return dp[m][n];
    }

    /**
     * 动态规划 O(m n) O(n) 空间压缩
     * dp[i][j] word1[0, i-1] word2[0, j-1] 最少删除多少步使其相等
     * 对应字符
     * 相等时 不需要删除 延续 dp[i-1][j-1]
     * 不相等时 取删除 word1 还是 word2 中的较小值 + 1: min(dp[i - 1][j],
     * dp[i][j - 1]) + 1;
     */
    int minDistance2(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        // dp[i][j] word1[0, i-1] word2[0, j-1] 最少删除多少步使其相等
        vector<int> dp(n + 1);
        dp[0] = 0;  // 都为空 不需要删除
        // 初始化 dp[0][j]  // word1 为空时，需要删除  word2.length 步
        for (int j = 1; j <= n; j++) {
            dp[j] = j;
        }
        // // 初始化 dp[i][0]  // word2 为空时，需要删除 word1.length 步
        // for (int i = 1; i <= m; i++) {
        //     dp[i][0] = i;
        // }
        // 状态转移 从 左上，左，上 转移而来
        for (int i = 1; i <= m; i++) {
            dp[0] = i;            // 第一个元素
            int leftTop = i - 1;  // 初始化 左上
            for (int j = 1; j <= n; j++) {
                // 相等时 当前不需要删除
                int temp = dp[j];
                if (word1[i - 1] == word2[j - 1]) {
                    // 取决于各自前面一位
                    dp[j] = leftTop;
                } else {
                    // 不相等时，取 删除 word1 中和 word2 中的较小值
                    // 删除了一个 需要 + 1次
                    dp[j] = min(dp[j], dp[j - 1]) + 1;
                }
                leftTop = temp;
            }
        }
        return dp[n];
    }
};

int main() {
    Solution* s = new Solution();
    vector<string> list1 = {"sea", "leetcode", "a"};
    vector<string> list2 = {"eat", "etco", "b"};
    vector<int> answer = {2, 4};
    for (int i = 0; i < list1.size(); i++) {
        int ans = s->minDistance2(list1[i], list2[i]);
        cout << ans << endl;
    }
}