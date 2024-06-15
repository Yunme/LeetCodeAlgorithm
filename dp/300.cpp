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
 * 300: 最长递增子序列
 * 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
 * 子序列
 * 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。
 * 例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列
 *
 * 子序列
 * 是可以通过从另一个数组删除或不删除某些元素，但不更改其余元素的顺序得到的数组。
 *
 * https://leetcode.cn/problems/longest-increasing-subsequence/description
 */
class Solution {
   public:
    /**
     * 动态规划 O(n^2)
     * dp[i] = 0~i中间小于 nums[i] 的 dp 最大值，它的dp值 +1
     */
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        // 以 i 为结尾的最长递增子序列, 默认是1，自己本身算1个
        vector<int> dp(n, 1);

        // 状态转移方程为：
        // dp[i] = 0~i中间小于 nums[i] 的 dp 最大值，它的dp值 +1
        // 找出 dp 数组中的最大值
        int ans = dp[0];
        for (int i = 1; i < n; i++) {
            int maxJ = -1;
            // 区间中 小于 i处数的 dp最大值
            int maxDp = -1;
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j] && dp[j] > maxDp) {
                    maxDp = dp[j];
                    maxJ = j;
                }
            }
            // cout << maxDp << " ";
            if (maxJ > -1) {
                dp[i] = dp[maxJ] + 1;
            }
            ans = max(ans, dp[i]);
            cout << dp[i] << " ";
        }
        cout << endl;
        return ans;
    }

    /**
     * 动态规划 简洁版
     */
    int lengthOfLIS2(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        int ans = dp[0];
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                // 比 i 处数要小
                if (nums[i] > nums[j]) {
                    // 找出最大dp + 1
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }

    /**
     * 法2：二分查找 + 贪心 O(nLogN)
     * 蜘蛛纸牌 排法
     */
    int lengthOfLIS3(vector<int>& nums) {
        int n = nums.size();
        // 看作是很多个桶，每个桶里是从大到小的

        // tails[i] 表示：长度是 i+1
        // 的子序列最小的尾。尾尽可能小，才可以让更多的元素可以跟在后面
        vector<int> tails(n + 1);  // 桶最多n个，nums里数全是递增的话，n个桶占满
        // 放置时，要小于桶顶元素，如果大于，放置到下个桶里
        // 遍历数组，放置到桶里，
        int ans = 0;  // 计数占了几个桶
        for (int i = 0; i < n; i++) {
            int target = nums[i];
            // 桶顶肯定是递增的
            // 二分查找 找到放置的位置。如果没有则放到下一位
            int left = 0, right = ans;  // 左必右开区间
            // 要找的是 nums[i] < 桶顶的，且尽可能靠左
            // 也就是第一个 >= 要找的元素的位置
            while (left < right) {
                int mid = (left + right) / 2;
                if (tails[mid] < target) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            cout << left << "," << right << endl;
            // 左右相等
            tails[left] = target;
            if (right == ans) {
                ans++;
            }
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{10, 9, 2, 5, 3, 7, 101, 18, 1},
                                {0, 1, 0, 3, 2, 3},
                                {7, 7, 7, 7, 7, 7, 7}};
    vector<int> answers = {4, 4, 1};
    for (int i = 0; i < list.size(); i++) {
        int ans = s->lengthOfLIS3(list[i]);
        cout << ans << endl;
        assert(ans == answers[i]);
    }
}