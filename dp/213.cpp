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
 * 213: 打家劫舍 II
 * 你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。
 * 这个地方所有的房屋都 围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。
 * 同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警
 * 。 给定一个代表每个房屋存放金额的非负整数数组，计算你
 * 在不触动警报装置的情况下 ， 今晚能够偷窃到的最高金额。
 *
 * https://leetcode.cn/problems/house-robber-ii/description/
 */
class Solution {
   public:
    /**
     * 动态规划
     * O(n) O(n)
     * 最后一件不能和第一件同时偷
     *
     * 解为：max(偷[0, n-2], 偷[1, n-1])
     */
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]);
        // 偷 [0, n-2] 范围
        // [0, i] 偷到的最大金钱
        vector<int> dp(n - 1);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n - 1; i++) {
            // 偷 i: dp[i - 2] + nums[i]
            // 不偷 i：dp[i-1]
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }

        // 偷 [1, n-1]
        vector<int> dp2(n);
        dp2[0] = 0;
        dp2[1] = nums[1];
        for (int i = 2; i < n; i++) {
            // 偷 i: dp[i - 2] + nums[i]
            // 不偷 i：dp[i-1]
            dp2[i] = max(dp2[i - 2] + nums[i], dp2[i - 1]);
        }

        for (int i = 0; i < n - 1; i++) {
            cout << dp[i] << " ";
        }
        return max(dp[n - 2], dp2[n - 1]);
    }

    /**
     * 动态规划
     * 只跟前两个有关 压缩成滚动数组
     */
    int rob2(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]);
        return max(robRange(nums, 0, n - 2), robRange(nums, 1, n - 1));
    }

    /**
     * 偷指定范围内的房屋
     */
    int robRange(vector<int>& nums, int start, int end) {
        int n = end - start + 1;
        if (n == 0) return 0;
        if (n == 1) return nums[start];
        if (n == 2) return max(nums[start], nums[start + 1]);

        // 偷 [start, end] 范围
        int a = nums[start];
        int b = max(nums[start], nums[start + 1]);
        int c = b;
        for (int i = start + 2; i <= end; i++) {
            // 偷 i: dp[i - 2] + nums[i]
            // 不偷 i：dp[i-1]
            c = max(a + nums[i], b);
            a = b;
            b = c;
        }
        return c;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {
        {2, 3, 2}, {1, 2, 3, 1}, {1, 2, 3}, {1, 2, 1, 1}};
    for (auto i : list) {
        int count = s->rob2(i);
        cout << count << endl << endl;
    }
}