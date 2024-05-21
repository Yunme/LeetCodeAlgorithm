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
 * 62: 不同路径
 * 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
 * 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为
 * “Finish” ）。 问总共有多少条不同的路径？
 *
 * https://leetcode.cn/problems/unique-paths/description/
 */
class Solution {
   public:
    /**
     * 法1：自己实现 动态规划思路
     *
     * 由于只能向下或向右。
     * 所以第一行的格子都只有一种路径到达。（一直向右）
     * 同理，第一列的格子也是只有一种路径到达 （一直向下）
     *
     * 而除了第一行和第一列的其他格子
     * 到达此格子的路径为：
     * 到达邻近的上面格子的路径数 + 到达邻近的左边格子的路径数
     * 因为此格子既可以从左边到达，也可以从上面到达。
     */
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n));

        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }
        for (int j = 0; j < n; j++) {
            dp[0][j] = 1;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
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
     * 法2：动态规划 空间优化
     * 由于 第 i 行的状态 只和 i-1 行有关
     * 所以再计算时：
     * 当前的值dp[i] = 已有的当前的值(即上一行的值) dp[i] + dp[i-1]
     */
    int uniquePaths2(int m, int n) {
        vector<int> dp(n, 1);

        // 计算次数还是没变，
        // 上一行的作用就是为了推出下一行，
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[j] = dp[j] + dp[j - 1];
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
    vector<pair<int, int>> list = {{3, 7}, {3, 2}, {7, 3}, {3, 3}};
    for (auto i : list) {
        int count = s->uniquePaths2(i.first, i.second);
        cout << count << endl;
        cout << endl;
    }
}