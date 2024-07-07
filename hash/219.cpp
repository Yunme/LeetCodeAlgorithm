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
 * 219: 存在重复元素 II
 *
 * 给你一个整数数组 nums 和一个整数 k ，判断数组中是否存在两个 不同的索引 i 和
 * j, 满足 nums[i] == nums[j] 且 abs(i - j) <= k 。 如果存在，返回 true，
 * 否则，返回 false 。
 *
 * https://leetcode.cn/problems/contains-duplicate-ii/description
 */

class Solution {
   public:
    /**
     * 法1：map 法 O(n) O(n)
     * map 记录每个元素和索引
     */
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            int num = nums[i];
            // 如果已有 且 索引差值绝对值 <= k 则返回 true
            if (map.find(num) != map.end() && abs(i - map[num]) <= k) {
                return true;
            }
            map[num] = i;
        }
        return false;
    }

    /**
     * 法2：滑动窗口 O(n) O(1)
     */
    bool containsNearbyDuplicate2(vector<int>& nums, int k) {
        // 窗口内元素
        unordered_set<int> set;
        int start = 0, end = 0;
        while (end < nums.size()) {
            // 不包含 窗口扩张
            if (set.find(nums[end]) == set.end()) {
                set.insert(nums[end]);
                end++;
            } else {
                // 包含 窗口缩小 直到不包含
                if (end - start <= k) {
                    return true;
                }
                set.erase(nums[start]);
                start++;
            }
        }
        return false;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{1, 2, 3, 1}, {1, 0, 1, 1}, {1, 2, 3, 1, 2, 3}};
    vector<int> ks = {3, 1, 2};

    for (int i = 0; i < list.size(); i++) {
        auto ans = s->containsNearbyDuplicate2(list[i], ks[i]);
        cout << ans << endl;
    }
}