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
 * 494：目标和
 * 给你一个非负整数数组 nums 和一个整数 target 。
 * 向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式
 * ： 例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-'
 * ，然后串联起来得到表达式 "+2-1" 。 返回可以通过上述方法构造的、运算结果等于
 * target 的不同 表达式 的数目。
 *
 * https://leetcode.cn/problems/partition-equal-subset-sum/description/
 */
class Solution {
   public:
    /**
     * 分解为：加法部分之和为 x，减法部分和为 y
     * 有 x + y = sum; x - y = target;
     * x = (sum + target) / 2
     * 转换为 0-1背包问题
     * 转换为 选若干个数其和为 x，求方案数
     */
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        int sum = 0;
        for (int i : nums) {
            sum += i;
        }
        if (sum < target) return 0;
        // 和为奇数 无解
        // 需要是偶数
        if ((sum + target) % 2 != 0) return 0;

        int ansTarget = (sum + target) / 2;

        // [0,i] 选若干个和等于 j 的方案数
        vector<int> dp(ansTarget + 1);
        dp[0] = 1;  // 选 0个其和为0 的方案数是1
        for (int i = 0; i < n; i++) {
            for (int j = ansTarget; j >= nums[i]; j--) {
                // 不选 i, 维持 dp[j]
                // 选 i
                // 总的方案数 = 不选 + 选
                dp[j] = dp[j] + dp[j - nums[i]];
            }
        }
        return dp[ansTarget];
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{1, 1, 1, 1, 1}, {1}};
    vector<int> target = {3, 1};
    for (int i = 0; i < list.size(); i++) {
        int ans = s->findTargetSumWays(list[i], target[i]);
        cout << ans << endl;
    }
}