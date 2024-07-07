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
 * 217: 存在重复元素
 *
 * 给你一个整数数组 nums 。如果任一值在数组中出现 至少两次 ，返回 true；
 * 如果数组中每个元素互不相同，返回 false 。
 *
 * https://leetcode.cn/problems/contains-duplicate/description/
 */

class Solution {
   public:
    /**
     * 法1：排序法 O(nLogN) O(1)
     * 排序后一次遍历查找是否有重复
     */
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) return true;
        }
        return false;
    }

    /**
     * 法2：哈希表法 O(n) O(n)
     * 添加到 set 中看是否有重复
     */
    bool containsDuplicate2(vector<int>& nums) {
        unordered_set<int> set;
        for (int i = 0; i < nums.size(); i++) {
            if (set.find(nums[i]) != set.end()) {
                return true;
            }
            set.insert(nums[i]);
        }
        return false;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {
        {1, 2, 3, 1}, {1, 2, 3, 4}, {1, 1, 1, 3, 3, 4, 3, 2, 4, 2}};

    for (int i = 0; i < list.size(); i++) {
        auto ans = s->containsDuplicate2(list[i]);
        cout << ans << endl;
    }
}