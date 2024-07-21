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
 * 1005：K次取反后最大化的数组和
 * 给你一个整数数组 nums 和一个整数 k ，按以下方法修改该数组：
 * 选择某个下标 i 并将 nums[i] 替换为 -nums[i] 。
 * 重复这个过程恰好 k 次。可以多次选择同一个下标 i 。
 * 以这种方式修改数组后，返回数组 可能的最大和 。
 *
 * https://leetcode.cn/problems/maximize-sum-of-array-after-k-negations/description/
 */
class Solution {
   public:
    /**
     * 贪心思想
     * 尽可能取反小的数
     */
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        int n = nums.size();
        // 按绝对值大小进行排序
        auto compare = [](int a, int b) { return abs(a) > abs(b); };
        sort(nums.begin(), nums.end(), compare);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            // 所有负数变正数
            if (nums[i] < 0 && k > 0) {
                nums[i] = -nums[i];
                k--;
            }
        }
        // 此时 k 是奇数 数组里的最小值需要反复消耗取反
        if (k % 2 == 1) {
            // 最小值为 nums[n - 1]
            nums[n - 1] = -nums[n - 1];
        }
        // k 消耗完 累加
        for (int i : nums) {
            sum += i;
        }
        return sum;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {
        {4, 3, 2}, {3, -1, 0, 2}, {2, -3, -1, 5, -4}, {-8, 3, -5, -3, -5, -2}};
    vector<int> ks = {1, 3, 2, 6};
    for (int i = 0; i < list.size(); i++) {
        int ans = s->largestSumAfterKNegations(list[i], ks[i]);
        cout << ans << endl;
    }
}