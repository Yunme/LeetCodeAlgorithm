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
 * 63: 不同路径 II
 * 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
 * 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为
 * “Finish”）。
 * 现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
 * 网格中的障碍物和空位置分别用 1 和 0 来表示。
 *
 * https://leetcode.cn/problems/unique-paths-ii/description/
 */
class Solution {
   public:
    /**
     * 动态规划：O(m*n) O(m*n)
     * （自己实现）
     */
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        // dp[i][j] 表示到达 i，j处的不同路径数
        vector<vector<int>> dp(m, vector<int>(n));
        int start = obstacleGrid[0][0];
        if (start == 1) {
            return 0;
        }
        dp[0][0] = 1;
        // 第一行 只能从左边来
        for (int j = 1; j < n; j++) {
            if (obstacleGrid[0][j]) {
                dp[0][j] = 0;
            } else {
                dp[0][j] = dp[0][j - 1];
            }
        }
        // 第一列 只能从上面来
        for (int i = 1; i < m; i++) {
            if (obstacleGrid[i][0]) {
                dp[i][0] = 0;
            } else {
                dp[i][0] = dp[i - 1][0];
            }
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                // 如果是障碍物，则不能到达 为0
                if (obstacleGrid[i][j]) {
                    dp[i][j] = 0;
                } else {
                    // 路径数 = 从左来的路径数 + 从上来的路径数
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
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
     * 动态规划：O(m*n) O(n)
     * 状态压缩
     */
    int uniquePathsWithObstacles2(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        // dp [j] 表示到达上一行 j 处的不同路径数
        vector<int> dp(n);
        int start = obstacleGrid[0][0];
        if (start == 1) {
            return 0;
        }
        dp[0] = 1;
        // 第一行 只能从左边来
        for (int j = 1; j < n; j++) {
            if (obstacleGrid[0][j]) {
                dp[j] = 0;
            } else {
                dp[j] = dp[j - 1];
            }
        }

        for (int i = 1; i < m; i++) {
            // 第一列 只能从上面来
            if (obstacleGrid[i][0]) {
                dp[0] = 0;
            }
            for (int j = 1; j < n; j++) {
                // 如果是障碍物，则不能到达 为0
                if (obstacleGrid[i][j]) {
                    dp[j] = 0;
                } else {
                    // 路径数 = 从左来的路径数 + 从上来的路径数
                    // dp[j]：上一行的当前值，dp[i-1] 当前行的左边值
                    dp[j] = dp[j] + dp[j - 1];
                }
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
    vector<vector<vector<int>>> list = {{{0, 0, 0}, {0, 1, 0}, {0, 0, 0}},
                                        {{0, 1}, {0, 0}}};
    vector<int> answers = {2, 1};
    for (auto i : list) {
        int count = s->uniquePathsWithObstacles2(i);
        cout << count << endl;
    }
}