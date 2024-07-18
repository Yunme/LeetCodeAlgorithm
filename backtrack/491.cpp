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
 * 491：非递减子序列
 * 给你一个整数数组 nums ，找出并返回所有该数组中不同的递增子序列，递增子序列中
 * 至少有两个元素 。你可以按 任意顺序 返回答案。
 * 数组中可能含有重复元素，如出现两个整数相等，也可以视作递增序列的一种特殊情况。
 *
 * https://leetcode.cn/problems/non-decreasing-subsequences/description/
 */
class Solution {
   public:
    /**
     * 回溯
     * 结果在结点上
     */
    void backtracking(vector<int> &nums, int index, vector<int> &temp,
                      vector<vector<int>> &ans) {
        if (index > nums.size()) return;
        // 大于等于2个的结果
        if (temp.size() >= 2) {
            ans.push_back(temp);
            // 不能返回，要取所有结点的结果
        }
        // 回溯树 一层去重
        unordered_set<int> used;
        for (int i = index; i < nums.size(); i++) {
            // 非递减序列 当前与路上的最后一个值比较
            if (!temp.empty() && nums[i] < temp.back()) continue;
            // 当前层去重 相同的只能取一个
            if (used.find(nums[i]) != used.end()) continue;
            used.insert(nums[i]);
            temp.push_back(nums[i]);
            // 下一层
            backtracking(nums, i + 1, temp, ans);
            // 向上回溯
            temp.pop_back();
        }
    }
    vector<vector<int>> findSubsequences(vector<int> &nums) {
        vector<int> temp;
        vector<vector<int>> ans;
        backtracking(nums, 0, temp, ans);
        return ans;
    }
};

int main() {
    Solution *s = new Solution();
    vector<vector<int>> list = {
        {4, 6, 7, 7}, {4, 4, 3, 2, 1}, {8, 9, 10, 1, 1}};

    for (int i = 0; i < list.size(); i++) {
        auto ans = s->findSubsequences(list[i]);
        cout << "count:" << ans.size() << endl;
        for (auto &i : ans) {
            for (auto &j : i) {
                cout << j << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}