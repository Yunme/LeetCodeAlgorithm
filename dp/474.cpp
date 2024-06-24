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
 * 474：一和零
 * 给你一个二进制字符串数组 strs 和两个整数 m 和 n 。
 * 请你找出并返回 strs 的最大子集的长度，该子集中 最多 有 m 个 0 和 n 个 1 。
 * 如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集 。
 *
 * https://leetcode.cn/problems/ones-and-zeroes/description/
 */
class Solution {
   public:
    /**
     * 转换为 0-1背包问题
     * 前[0,i]个 0的数量不超过j ，1的数量不超过k 的最大元素个数
     */
    int findMaxForm(vector<string>& strs, int m, int n) {
        int size = strs.size();
        // dp[i][j][k] 前[0,i]个 0的数量不超过j ，1的数量不超过k 的最大元素个数
        vector<vector<vector<int>>> dp(
            size, vector<vector<int>>(m + 1, vector<int>(n + 1)));
        // 缓存每个元素的 0 的个数
        // 1的个数 = 总长 - 0 的个数
        vector<int> zeroCounts(size);
        for (int i = 0; i < size; i++) {
            int count = 0;
            for (int j = 0; j < strs[i].length(); j++) {
                if (strs[i][j] == '0') {
                    count++;
                }
            }
            zeroCounts[i] = count;
        }
        dp[0][0][0] = 0;
        // i = 0 时初始化
        // 第一个加入时长度大
        for (int j = zeroCounts[0]; j < m + 1; j++) {
            for (int k = strs[0].length() - zeroCounts[0]; k < n + 1; k++) {
                dp[0][j][k] = 1;
            }
        }
        // for (int j = 0; j < m + 1; j++) {
        //     for (int k = 0; k < n + 1; k++) {
        //         cout << dp[0][j][k] << " ";
        //     }
        //     cout << endl;
        // }
        for (int i = 1; i < size; i++) {
            int zeroCount = zeroCounts[i];
            int oneCount = strs[i].length() - zeroCount;
            for (int j = 0; j < m + 1; j++) {
                for (int k = 0; k < n + 1; k++) {
                    // 当前 i 不加入时，长度还是 i-1 的
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k]);
                    if (j >= zeroCount && k >= oneCount) {
                        // 当前 i 加入时，长度从 i-1计算得来，类似背包
                        dp[i][j][k] =
                            max(dp[i][j][k],
                                dp[i - 1][j - zeroCount][k - oneCount] + 1);
                    }
                }
            }
        }

        // for (int i = 0; i < size; i++) {
        //     for (int j = 0; j < m + 1; j++) {
        //         for (int k = 0; k < n + 1; k++) {
        //             cout << dp[i][j][k] << " ";
        //         }
        //     }
        //     cout << endl;
        // }

        return dp[size - 1][m][n];
    }

    /**
     * 动态规划 空间压缩
     * i 只和 i-1有关
     */
    int findMaxForm2(vector<string>& strs, int m, int n) {
        int size = strs.size();
        // dp[j][k] 前[0,i]个 0的数量不超过j ，1的数量不超过k 的最大元素个数
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        // 缓存每个元素的 0 的个数
        // 1的个数 = 总长 - 0 的个数
        vector<int> zeroCounts(size);
        for (int i = 0; i < size; i++) {
            int count = 0;
            for (int j = 0; j < strs[i].length(); j++) {
                if (strs[i][j] == '0') {
                    count++;
                }
            }
            zeroCounts[i] = count;
        }
        dp[0][0] = 0;
        // i = 0 时初始化
        // 第一个加入时长度大
        for (int j = zeroCounts[0]; j < m + 1; j++) {
            for (int k = strs[0].length() - zeroCounts[0]; k < n + 1; k++) {
                dp[j][k] = 1;
            }
        }

        for (int i = 1; i < size; i++) {
            int zeroCount = zeroCounts[i];
            int oneCount = strs[i].length() - zeroCount;
            for (int j = m; j >= zeroCount; j--) {
                for (int k = n; k >= oneCount; k--) {
                    // 当前 i 不加入时，长度还是 i-1 的
                    // 当前 i 加入时，长度从 i-1计算得来，类似背包
                    dp[j][k] =
                        max(dp[j][k], dp[j - zeroCount][k - oneCount] + 1);
                }
            }
        }
        return dp[m][n];
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<string>> list = {{"10", "0001", "111001", "1", "0"},
                                   {"10", "0", "1"}};
    vector<int> target1 = {5, 1};
    vector<int> target2 = {3, 1};
    for (int i = 0; i < list.size(); i++) {
        int ans = s->findMaxForm2(list[i], target1[i], target2[i]);
        cout << ans << endl;
    }
}