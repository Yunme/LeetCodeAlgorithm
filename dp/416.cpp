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
 * 416: 分割等和子集
 * 给你一个 只包含正整数 的 非空 数组 nums
 * 请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
 *
 * https://leetcode.cn/problems/partition-equal-subset-sum/description/
 */
class Solution {
   public:
    /**
     * 动态规划 O(n^2) O(n^2)
     * dp[i][j] 从 [0,i] 范围内选取若干个，是否存在一种方案使得选取的和等于j
     */
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        // 数组元素个数小于2  没法被分割成两个子集
        if (n < 2) return false;

        // 先计算整个数组的累加和
        int sum = 0;
        int maxVal = 0;
        for (int i : nums) {
            sum += i;
            maxVal = max(maxVal, i);
        }
        // 由于要分成两个子集的和 说明总和需要是偶数
        if (sum % 2 != 0) return false;  // 和为奇数返回
        int target = sum / 2;
        if (maxVal > target)
            return false;  // 数组中最大元素大于目标，说明不能分割
        // 转化为 0-1背包问题
        // dp[i][j] 从 [0,i] 范围内选取若干个，是否存在一种方案使得选取的和等于j
        vector<vector<int>> dp(n, vector<int>(target + 1));
        // 初始化
        // j 为 0 时，[0,i] 内不选取，那么和 = 0
        for (int i = 0; i < n; i++) {
            dp[i][0] = 1;
        }
        // i = 0 时，只有一个元素可以被选取
        dp[0][nums[0]] = 1;  // j：和为 nums[0];

        // 转移方程：
        // j >= nums[i] 时，i可以选也可以不选, 有一个为 true 则为 true
        // j < nums[j] 时，没法选，其值 = dp[i-1][j]
        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= target; j++) {
                if (j >= nums[i]) {
                    // 选了i: dp[i-1][j-nums[i]]
                    // 不选i：dp[i-1][j]
                    dp[i][j] = dp[i - 1][j - nums[i]] || dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= target; j++) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        return dp[n - 1][target];
    }

    /**
     * 动态规划 空间压缩
     * 由于 dp[i][j] 的值之和 i-1 行有关，可以压缩成一维数组
     */
    bool canPartition2(vector<int>& nums) {
        int n = nums.size();
        // 数组元素个数小于2  没法被分割成两个子集
        if (n < 2) return false;

        // 先计算整个数组的累加和
        int sum = 0;
        int maxVal = 0;
        for (int i : nums) {
            sum += i;
            maxVal = max(maxVal, i);
        }
        // 由于要分成两个子集的和 说明总和需要是偶数
        if (sum % 2 != 0) return false;  // 和为奇数返回
        int target = sum / 2;
        if (maxVal > target)
            return false;  // 数组中最大元素大于目标，说明不能分割

        // 当前 [0, i] 取若干个之和 是否有一种方案等于 target
        vector<int> dp(target + 1);
        dp[0] = 1;  // 不取时和为0 满足 true
        // 转移：j >= nums[i] 可选可不选 dp[j] = dp[j] || dp[j - nums[i]]
        // j < nums[j] 不选
        for (int i = 0; i < n; i++) {
            // 一行里，j 大于 j - nums[i] 依赖上一行前面的值，
            // 所以，只能从后向前遍历，否则上一行的值被这一行的值覆盖了

            // j < nums[i] 时，保持不变 dp[j] = dp[j]
            // 大于等于时才需要更新，直接遍历 target 到 nums[i] 之间的数
            for (int j = target; j >= nums[i]; j--) {
                dp[j] = dp[j] || dp[j - nums[i]];
            }
        }

        for (int j = 0; j <= target; j++) {
            cout << dp[j] << " ";
        }
        cout << endl;
        return dp[target];
    }

    /**
     * 法2：纯粹的 0-1背包应用
     * 背包容量为 target 时，装满的最大价值是否为 target
     * 价值和重量相等
     * 空间压缩版本
     */
    bool canPartition3(vector<int>& nums) {
        int n = nums.size();
        // 数组元素个数小于2  没法被分割成两个子集
        if (n < 2) return false;
        // 先计算整个数组的累加和
        int sum = 0;
        int maxVal = 0;
        for (int i : nums) {
            sum += i;
            maxVal = max(maxVal, i);
        }
        // 由于要分成两个子集的和 说明总和需要是偶数
        if (sum % 2 != 0) return false;  // 和为奇数返回
        int target = sum / 2;
        if (maxVal > target)
            return false;  // 数组中最大元素大于目标，说明不能分割
        vector<int> dp(target + 1);
        for (int i = 0; i < n; i++) {
            for (int j = target; j >= nums[i]; j--) {
                dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
            }
        }
        return dp[target] == target;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{1, 5, 11, 5}, {1, 2, 3, 5}};
    for (auto i : list) {
        int ans = s->canPartition3(i);
        cout << ans << endl;
    }
}