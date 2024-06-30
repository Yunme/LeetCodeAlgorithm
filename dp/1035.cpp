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
 * 1035: 不相交的线
 *
 * 在两条独立的水平线上按给定的顺序写下 nums1 和 nums2 中的整数。
 * 现在，可以绘制一些连接两个数字 nums1[i] 和 nums2[j]
 * 的直线，这些直线需要同时满足： nums1[i] == nums2[j]
 * 且绘制的直线不与任何其他连线（非水平线）相交。
 * 请注意，连线即使在端点也不能相交：每个数字只能属于一条连线。
 * 以这种方法绘制线条，并返回可以绘制的最大连线数。
 *
 * https://leetcode.cn/problems/uncrossed-lines/description/
 */
class Solution {
   public:
    /**
     * 动态规划
     * 本质就是 1143.最长公共子序列问题
     * 连线就是相等，不相交代表相对顺序不变
     */
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        if (m == 0 || n == 0) return 0;
        // dp[i][j] [0, i-1] [0, j-1]的连线数
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        // 转移方程为：
        // 如果当前相等 取 dp[i - 1][j - 1] + 1
        // 如果不相等 延续 dp[i - 1][j], dp[i][j - 1] 较大值
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }

    /**
     * 动态规划 空间压缩
     * 本质就是 1143.最长公共子序列问题
     * 连线就是相等，不相交代表相对顺序不变
     */
    int maxUncrossedLines2(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        if (m == 0 || n == 0) return 0;
        // dp[i][j] [0, i-1] [0, j-1]的连线数
        vector<int> dp(n + 1);
        // 转移方程为：
        // 如果当前相等 取 dp[i - 1][j - 1] + 1
        // 如果不相等 延续 dp[i - 1][j], dp[i][j - 1] 较大值
        for (int i = 1; i <= m; i++) {
            // 存储 左上角的值
            int leftTop = 0;
            for (int j = 1; j <= n; j++) {
                int temp = dp[j];  // 暂存上一个 不会被覆盖
                if (nums1[i - 1] == nums2[j - 1]) {
                    // 每次取上一个
                    dp[j] = leftTop + 1;
                } else {
                    dp[j] = max(dp[j], dp[j - 1]);
                }
                // 更新上一个
                leftTop = temp;
            }
        }
        return dp[n];
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list1 = {
        {1, 4, 2}, {2, 5, 1, 2, 5}, {1, 3, 7, 1, 7, 5}};
    vector<vector<int>> list2 = {
        {1, 2, 4}, {10, 5, 2, 1, 5, 2}, {1, 9, 2, 5, 1}};
    for (int i = 0; i < list1.size(); i++) {
        int count = s->maxUncrossedLines2(list1[i], list2[i]);
        cout << count << endl;
    }
}