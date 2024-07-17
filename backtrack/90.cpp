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
 * 90: 子集 II
 * 给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的
 * 子集（幂集）. 解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序
 * 排列。
 *
 * https://leetcode.cn/problems/subsets-ii/description/
 */
class Solution {
   public:
    /**
     * 回溯
     */
    void backtracking(vector<int> &nums, int index, vector<int> &temp,
                      vector<vector<int>> &ans) {
        if (index > nums.size()) return;

        // 回溯树中的每个结点都加入
        ans.push_back(temp);
        // 选择集 剩下的元素
        for (int i = index; i < nums.size(); i++) {
            // 去重
            if (i > index && nums[i] == nums[i - 1]) continue;
            
            temp.push_back(nums[i]);
            // 回溯树向下
            backtracking(nums, i + 1, temp, ans);
            // 回溯
            temp.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        vector<int> temp;
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        backtracking(nums, 0, temp, ans);
        return ans;
    }
};

int main() {
    Solution *s = new Solution();
    vector<vector<int>> list = {{1, 2, 2}, {0}};

    for (int i = 0; i < list.size(); i++) {
        auto ans = s->subsetsWithDup(list[i]);
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