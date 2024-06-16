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
 * 120:三角形最小路径和
 *
 * 给定一个三角形 triangle ，找出自顶向下的最小路径和。
 * 每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与
 * 上一层结点下标 相同或者等于 上一层结点下标 + 1
 * 的两个结点。也就是说，如果正位于当前行的下标 i ，
 * 那么下一步可以移动到下一行的下标 i 或 i + 1 。
 *
 * 1 <= triangle.length <= 200
 * triangle[0].length == 1
 * triangle[i].length == triangle[i - 1].length + 1
 * -104 <= triangle[i][j] <= 104
 *
 * https://leetcode.cn/problems/triangle/description/
 */
class Solution {
   public:
    /**
     * 动态规划 O(m * n) O(m * n)
     *  (自己实现)
     * dp[i][j] 表示 从顶到 i 行，j个元素的最小路径和
     */
    int minimumTotal(vector<vector<int>>& triangle) {
        int m = triangle.size();
        int n = triangle.back().size();
        if (m == 1) {
            return triangle[0][0];
        }
        // dp[i][j] 表示 从顶到 i 行，j个元素的最短距离加上 此处的值
        vector<vector<int>> dp(m, vector<int>(n));
        // 第一行只有一个数
        dp[0][0] = triangle[0][0];
        // 转移方程为：每行的元素，只能从上一行(i-1)的 j 或者
        // j-1路径来，选取较小的那个
        int ans = INT_MAX;
        for (int i = 1; i < m; i++) {
            int size = triangle[i].size();
            for (int j = 0; j < size; j++) {
                if (j == 0) {
                    // 第一个只能从上一行的第一个来
                    dp[i][j] = dp[i - 1][j] + triangle[i][j];
                } else if (j == size - 1) {
                    // 最后一个只能从上一行的最后一个来
                    dp[i][j] = dp[i - 1][j - 1] + triangle[i][j];
                } else {
                    // 中间的 从上一行的 j 或 j-1来，取小者
                    dp[i][j] =
                        min(dp[i - 1][j], dp[i - 1][j - 1]) + triangle[i][j];
                }
                // 最后一行 记录较小者 返回
                if (i == m - 1) {
                    ans = min(ans, dp[i][j]);
                }
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        return ans;
    }

    /**
     * 动态规划 O(m * n) O(m)
     * 空间压缩， 由于 dp[i][j] 的状态只跟 dp[i-1] 有关。
     * 压缩成一维
     */
    int minimumTotal2(vector<vector<int>>& triangle) {
        int m = triangle.size();
        int n = triangle.back().size();
        if (m == 1) {
            return triangle[0][0];
        }
        // dp[j] 表示上一行的数据 j位置的最短路径
        vector<int> dp(n);
        // 第一行只有一个数
        dp[0] = triangle[0][0];
        // 转移方程为：每行的元素，只能从上一行(i-1)的 j 或者
        // j-1路径来，选取较小的那个
        int ans = INT_MAX;
        for (int i = 1; i < m; i++) {
            int size = triangle[i].size();
            // 每行中依赖前一个元素的值
            // 从前向后遍历会覆盖
            // 从后向前遍历
            for (int j = size - 1; j >= 0; j--) {
                if (j == 0) {
                    // 第一个只能从上一行的第一个来
                    dp[j] = dp[j] + triangle[i][j];
                } else if (j == size - 1) {
                    // 最后一个只能从上一行的最后一个来
                    dp[j] = dp[j - 1] + triangle[i][j];
                } else {
                    // 中间的 从上一行的 j 或 j-1来，取小者
                    dp[j] = min(dp[j], dp[j - 1]) + triangle[i][j];
                }
                // 最后一行 记录较小者 返回
                if (i == m - 1) {
                    ans = min(ans, dp[j]);
                }
                cout << dp[j] << " ";
            }
            cout << endl;
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<vector<int>>> list = {{{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}},
                                        {{-10}}};
    vector<int> answer = {11, -10};
    for (auto i : list) {
        int ans = s->minimumTotal2(i);
        cout << ans << endl;
    }
}