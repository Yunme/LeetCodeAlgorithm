#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
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
 * 674: 最长连续递增子序列
 * 给定一个未经排序的整数数组，找到最长且 连续递增的子序列，并返回该序列的长度。
 * 连续递增的子序列 可以由两个下标 l 和 r（l < r）确定，如果对于每个 l <= i <
 * r，都有 nums[i] < nums[i + 1] ， 那么子序列 [nums[l], nums[l + 1], ...,
 * nums[r - 1], nums[r]] 就是连续递增子序列。
 *
 * https://leetcode.cn/problems/longest-continuous-increasing-subsequence/description/
 */
class Solution {
   public:
    /**
     * 法1：双指针法
     * 一次遍历
     */
    int findLengthOfLCIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return 1;

        int ans = 0;
        int start = 0;
        for (int i = 1; i < n; i++) {
            // 寻找连续递增
            if (nums[i] > nums[i - 1]) {
                continue;
            } else {
                // 不再递增 记录结果
                ans = max(ans, i - start);
                start = i;
            }
        }
        // 最后一段
        ans = max(ans, n - start);
        return ans;
    }

    /**
     * 法2：动态规划 O(n) O(n)
     */
    int findLengthOfLCIS2(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return 1;
        int ans = 0;
        // dp[i] 以 i 为结尾的 最长连续递增子序列长度
        vector<int> dp(n, 1);
        // 转移方程：
        // 因为连续，所以必须是比前一个大，在前一个的基础上 +1
        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1]) {
                dp[i] = dp[i - 1] + 1;
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }

    /**
     * 法3：动态规划 O(n) O(1)
     * i 只跟 i - 1有关
     * 空间压缩版本
     */
    int findLengthOfLCIS3(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return 1;
        int ans = 0;
        // dp[i] 以 i 为结尾的 最长连续递增子序列长度
        int a = 1;
        // 转移方程：
        // 因为连续，所以必须是比前一个大，在前一个的基础上 +1
        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1]) {
                a = a + 1;
            } else {
                a = 1;
            }
            ans = max(ans, a);
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{1, 3, 5, 4, 7}, {2, 2, 2, 2, 2}, {1, 3, 5, 7}};
    vector<int> answers = {3, 1, 4};
    for (int i = 0; i < list.size(); i++) {
        int ans = s->findLengthOfLCIS3(list[i]);
        cout << ans << endl;
        assert(ans == answers[i]);
    }
}