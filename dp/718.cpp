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
 * 718: 最长重复子数组
 * 给两个整数数组 nums1 和 nums2 ，返回 两个数组中 公共的
 * 、长度最长的子数组的长度 。
 *
 * https://leetcode.cn/problems/maximum-length-of-repeated-subarray/description/
 */
class Solution {
   public:
    /**
     * 法1：暴力法 O(n^3)
     */
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        if (m == 0 || n == 0) return 0;
        int ans = 0;
        for (int i = 0; i < m; i++) {
            // 对每个 nums1 元素，在 nums2 中 判断
            for (int j = 0; j < n; j++) {
                int k = 0;
                while (i + k < m && j + k < n && nums1[i + k] == nums2[j + k]) {
                    k++;
                }
                ans = max(ans, k);
            }
        }
        return ans;
    }

    /**
     * 法2：动态规划
     * dp[i][j]: nums1[0,i] 与 nums2[0,j] 最长公共子数组长度
     */
    int findLength2(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        if (m == 0 || n == 0) return 0;
        int ans = 0;
        // dp[i][j]: nums1[0,i] 与 nums2[0,j] 最长公共子数组长度
        vector<vector<int>> dp(m, vector<int>(n));
        // 初始化第0行 nums1[0]
        // i = 0
        for (int j = 0; j < n; j++) {
            if (nums1[0] == nums2[j]) {
                dp[0][j] = 1;
            } else {
                dp[0][j] = 0;
            }
            ans = max(ans, dp[0][j]);
        }
        // 初始化第 0 列 nums2[0]
        // j = 0
        for (int i = 0; i < m; i++) {
            if (nums1[i] == nums2[0]) {
                dp[i][0] = 1;
            } else {
                dp[i][0] = 0;
            }
            ans = max(ans, dp[i][0]);
        }
        // 转移方程
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                // 当两个元素相等时 dp[i][j] = dp[i - 1][j - 1] + 1;
                if (nums1[i] == nums2[j]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                ans = max(ans, dp[i][j]);
            }
        }
        return ans;
    }

    /**
     * 法2：动态规划
     * 修改dp数组含义，不包含 i
     * dp[i][j]: nums1[0,i-1] 与 nums2[0,j-1] 最长公共子数组长度
     */
    int findLength3(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        if (m == 0 || n == 0) return 0;
        int ans = 0;
        // dp[i][j]: nums1[0,i-1] 与 nums2[0,j-1] 最长公共子数组长度
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        // 不需要额外初始化 都是 0

        // 转移方程
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // 当两个元素相等时 dp[i][j] = dp[i - 1][j - 1] + 1;
                if (nums1[i - 1] == nums2[j - 1]) {  // 比较的是 前一个数
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                ans = max(ans, dp[i][j]);
            }
        }
        return ans;
    }

    /**
     * 法2：动态规划 空间压缩 O(m * n) O (n)
     * 修改dp数组含义，不包含 i
     * dp[i][j]: nums1[0,i-1] 与 nums2[0,j-1] 最长公共子数组长度
     * 只跟左上角有关 上一行的上一个
     */
    int findLength4(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        if (m == 0 || n == 0) return 0;
        int ans = 0;
        // dp[i][j]: nums1[0,i-1] 与 nums2[0,j-1] 最长公共子数组长度
        vector<int> dp(n + 1);
        // 不需要额外初始化 都是 0

        // 转移方程
        for (int i = 1; i <= m; i++) {
            // 需要倒序  否则会被覆盖
            for (int j = n; j >= 1; j--) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[j] = dp[j - 1] + 1;
                } else {
                    dp[j] = 0;
                }
                ans = max(ans, dp[j]);
            }
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list1 = {{1, 2, 3, 2, 1},
                                 {0, 0, 0, 0, 0},
                                 {0, 1, 1, 1, 1},
                                 {0, 0, 0, 0, 0, 0, 1, 0, 0, 0}};
    vector<vector<int>> list2 = {{3, 2, 1, 4, 7},
                                 {0, 0, 0, 0, 0},
                                 {1, 0, 1, 0, 1},
                                 {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}};
    for (int i = 0; i < list1.size(); i++) {
        int ans = s->findLength4(list1[i], list2[i]);
        cout << ans << endl;
    }
}