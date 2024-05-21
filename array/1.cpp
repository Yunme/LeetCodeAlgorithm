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
 * 1.两数之和
 * 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值
 * target  的那 两个 整数，并返回它们的数组下标。
 *
 * 只会存在一个有效答案
 * https://leetcode.cn/problems/two-sum/description/
 */
class Solution {
   public:
    /**
     * 法1：hashMap O(n)
     * 问题是要找索引
     * 所以 map 存储元素和元素的索引
     */
    vector<int> twoSum(vector<int>& nums, int target) {
        // map 中 key 是数组元素，value 是索引
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            // 如果 map 中已经存了另一个加数
            if (map.count(target - nums[i]) > 0) {
                // 那么 当前index 和 那个元素的索引 就是答案。
                return {map[target - nums[i]], i};
            }
            map[nums[i]] = i;
        }
        return {};
    }

    /**
     * 法2：暴力
     */
    vector<int> twoSum2(vector<int>& nums, int target) {
        // map 中 key 是数组元素，value 是索引
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> array = {{2, 7, 11, 15}, {3, 2, 4}, {3, 3}};
    vector<int> target = {9, 6, 6};

    for (size_t i = 0; i < array.size(); i++) {
        vector<int> arr = array[i];
        auto ans = s->twoSum2(arr, target[i]);
        cout << ans[0] << "," << ans[1] << endl;
    }
}