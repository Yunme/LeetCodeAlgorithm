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
 * 349: 两个数组的交集
 *
 * 给定两个数组 nums1 和 nums2 ，返回 它们的交集 。
 * 输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序 。
 *
 * https://leetcode.cn/problems/intersection-of-two-arrays/description/
 */

class Solution {
   public:
    /**
     * 哈希表
     * set 存储其中一个
     */
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set;
        for (int i : nums1) {
            set.insert(i);
        }
        unordered_set<int> ans;
        for (int j : nums2) {
            if (set.find(j) != set.end()) {
                // 或者在 set 中找到了后 remove set 中的元素。结果集就可以是
                // vector
                ans.insert(j);
            }
        }
        return vector<int>(ans.begin(), ans.end());
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list1 = {{1, 2, 2, 1}, {4, 9, 5}};
    vector<vector<int>> list2 = {{2, 2}, {9, 4, 9, 8, 4}};

    for (int i = 0; i < list1.size(); i++) {
        auto ans = s->intersection(list1[i], list2[i]);
        for (auto j : ans) {
            cout << j << " ";
        }
        cout << endl;
    }
}