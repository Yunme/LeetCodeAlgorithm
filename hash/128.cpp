#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 128: 最长连续序列
 *
 * 给定一个未排序的整数数组 nums
 * ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
 *
 * 请你设计并实现时间复杂度为 O(n) 的算法解决此问题。
 *
 * https://leetcode.cn/problems/longest-consecutive-sequence/description/
 */

class Solution {
   public:
    /**
     * 哈希表法 O(n) O(n)
     * set 存储元素
     * 直接遍历 set 最坏 O(n^2)
     * 需要找的是 序列开始的第一个，也就是 num - 1不在 set 中
     * 在 set 中找 当前数字 + 1,
     * 如果存在 长度 + 1
     * 如果不存在 最长长度
     */
    int longestConsecutive2(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        unordered_set<int> set;
        for (int i = 0; i < n; i++) {
            set.insert(nums[i]);
        }
        int ans = 0;
        // 遍历 set
        for (int num : set) {
            // 当前元素的 -1 存在，所以当前元素不是序列开始的第一个数字
            // 跳过，不重复计算
            if (set.find(num - 1) != set.end()) {
                continue;
            }
            int next = num + 1;
            int len = 1;  // 当前 nums[i] 算一个元素
            while (set.find(next) != set.end()) {
                len++;
                next++;
            }
            // 更新长度
            ans = max(ans, len);
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{100, 4, 200, 1, 3, 2},
                                {0, 3, 7, 2, 5, 8, 4, 6, 0, 1},
                                {1, 2, 3, 1, 2, 3}};

    for (int i = 0; i < list.size(); i++) {
        auto ans = s->longestConsecutive2(list[i]);
        cout << ans << endl;
    }
}