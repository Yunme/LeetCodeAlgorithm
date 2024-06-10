#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 209: 长度最小的子数组
 *
 * 给定一个含有 n 个正整数的数组和一个正整数 target 。
 * 找出该数组中满足其总和
 * 大于等于 target
 * 的长度最小的子数组 [numsl, numsl+1, ..., numsr-1, numsr]， 并返回其长度。
 * 如果不存在符合条件的子数组，返回 0 。
 *
 * https://leetcode.cn/problems/minimum-size-subarray-sum/description/
 */
class Solution {
   public:
    /**
     * 法1：滑动窗口寻找 O(n)
     * 思路是对的，代码不太简洁（自己实现）
     */
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MAX;
        int i = 0, j = 1;
        int sum = nums[i];
        // i 左边界，j右边界，不包含 j本身
        while (i < n && j <= n) {
            if (j >= n && sum < target) break;
            if (sum == target) {        // 等于目标
                ans = min(ans, j - i);  // 记录结果
                // 整体右移
                sum -= nums[i];  // 减去左边出去的
                i++;
                sum += nums[j];  // 加上右边进来的
                j++;
                continue;
            }
            // 窗口变大 并累加
            while (j < n && sum < target) {
                sum += nums[j];
                j++;
            }
            if (sum > target) {  // 大于目标 更新结果
                ans = min(ans, j - i);
                // 总和大于 target，
                sum -= nums[i];  // 左侧值出窗口，值减去
                i++;             // 窗口左边前进
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }

    /**
     * 滑动窗口 简洁代码
     */
    int minSubArrayLen2(int target, vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        int ans = INT_MAX;
        // start 窗口开始
        // end 窗口结束 包含 end
        int start = 0, end = 0;
        int sum = 0;  // 窗口内数之和
        while (end < n) {
            sum += nums[end];                     // 窗口变大，右侧移动
            while (sum >= target) {               // 大于等于
                ans = min(ans, end - start + 1);  // 更新结果
                sum -= nums[start];               // 左边出窗口
                start++;
            }
            // 直到小于 end 一直变大
            end++;
        }
        return ans == INT_MAX ? 0 : ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> array = {{2, 3, 1, 2, 4, 3},
                                 {1, 4, 4},
                                 {1, 1, 1, 1, 1, 1, 1, 1},
                                 {1, 2, 3, 4, 5}};
    vector<int> target = {7, 4, 11, 11};

    for (size_t i = 0; i < array.size(); i++) {
        vector<int> arr = array[i];
        cout << s->minSubArrayLen2(target[i], arr) << endl;
    }
}