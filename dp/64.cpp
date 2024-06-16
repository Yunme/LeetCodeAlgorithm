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
 * 64:最小路径和
 *
 * 给定一个包含非负整数的 m x n 网格 grid
 * ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
 * 说明：每次只能向下或者向右移动一步。
 *
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 200
 * 0 <= grid[i][j] <= 200
 *
 * https://leetcode.cn/problems/minimum-path-sum/description/
 */
class Solution {
   public:
    /**
     * 动态规划 O(m*n) O(m*n)
     * 自己实现
     * dp[i][j] 表示从左上角到 i,j 处的最小路径。
     */
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        // dp[i][j] 表示从左上角到 i,j 处的最小路径。
        // dp[m-1][n-1] 就是答案
        vector<vector<int>> dp(m, vector<int>(n));
        // 初始化
        dp[0][0] = grid[0][0];
        // 第一行 只能从左来
        for (int j = 1; j < n; j++) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }
        // 第一列 只能从上来
        for (int i = 1; i < m; i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                // 只能向下或向右，所以当前只能从左(i,j-1) 或上(i-1,j) 来
                // 从上或左较小者来
                dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + grid[i][j];
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        return dp[m - 1][n - 1];
    }

    /**
     * 动态规划 O(m*n) O(n)
     * 空间压缩
     */
    int minPathSum2(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        // dp[j] 表示从左上角到上一行 j 处的最小路径。
        // dp[n-1] 就是答案
        vector<int> dp(n);
        // 初始化
        dp[0] = grid[0][0];
        // 第一行 只能从左来
        for (int j = 1; j < n; j++) {
            dp[j] = dp[j - 1] + grid[0][j];
        }

        for (int i = 1; i < m; i++) {
            dp[0] = dp[0] + grid[i][0];
            for (int j = 1; j < n; j++) {
                // 只能向下或向右，所以当前只能从左(i,j-1) 或上(i-1,j) 来
                // 从上或左较小者来
                // dp[j-1]：左边    dp[j] 上一行的 j
                dp[j] = min(dp[j - 1], dp[j]) + grid[i][j];
            }
        }

        for (int j = 0; j < n; j++) {
            cout << dp[j] << " ";
        }
        cout << endl;
        return dp[n - 1];
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<vector<int>>> list = {{{1, 3, 1}, {1, 5, 1}, {4, 2, 1}},
                                        {{1, 2, 3}, {4, 5, 6}}};
    vector<int> answer = {7, 12};
    for (auto i : list) {
        int ans = s->minPathSum2(i);
        cout << ans << endl;
    }
}