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
 * 169：多数元素
 * 给定一个大小为 n 的数组 nums
 * 返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。
 * 你可以假设数组是非空的，并且给定的数组总是存在多数元素
 *
 * 题目保证众数个数超过 n/2 个
 *
 * https://leetcode.cn/problems/majority-element/
 */
class Solution {
   public:
    /**
     * 法1：map 存储判断
     * 时间 O(n), 空间 O(n)
     */
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> map;
        // 存储每个元素出现的次数
        for (int i : nums) {
            map[i]++;
        }
        int count = 0;
        int ans = nums[0];
        // 遍历 map 找出次数最大的
        for (auto& [k, v] : map) {
            if (v > count) {
                count = v;
                ans = k;
            }
        }
        return ans;
    }
    /**
     * 法2 排序法 时间 O(nLogN)
     * 题目保证众数个数超过 n/2 个
     * 所以排序后，n/2处的数必是众数
     */
    int majorityElement2(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }

    /**
     * 法3 摩尔投票法 时间 O(n) 空间 O(1)
     * 相消法
     */
    int majorityElement3(vector<int>& nums) {
        // 票数
        int count = 1;
        // 候选者
        int candidate = nums[0];
        // 遍历数组，如果票数为0，则更换候选人为当前
        // 如果 候选人是当前人，票数+1
        // 否则票数-1；
        for (int i = 1; i < nums.size(); i++) {
            if (count == 0) candidate = nums[i];
            if (candidate == nums[i]) {
                count++;
            } else {
                count--;
            }
        }
        return candidate;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> array = {
        {3, 2, 3}, {2, 2, 1, 1, 1, 2, 2}, {1, 5, 2, 5, 3, 4, 5, 5}};

    for (size_t i = 0; i < array.size(); i++) {
        cout << s->majorityElement3(array[i]) << endl;
    }
}