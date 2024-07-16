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
 * 40: 组合总和 II
 * 给定一个候选人编号的集合 candidates 和一个目标数 target ，找出 candidates
 * 中所有可以使数字和为 target 的组合。 candidates
 * 中的每个数字在每个组合中只能使用 一次 。
 *
 * 注意：解集不能包含重复的组合。
 *
 * https://leetcode.cn/problems/combination-sum-ii/description/
 */
class Solution {
   public:
    /**
     * 回溯
     */
    void backtracking(vector<int> &nums, int target, int index, int sum,
                      vector<int> &temp, vector<vector<int>> &ans) {
        if (sum == target) {
            ans.push_back(temp);
            return;
        }
        // 做选择
        // 剪枝 保证当前总和小于等于 target
        for (int i = index; i < nums.size() && sum + nums[i] <= target; i++) {
            int num = nums[i];
            // 去重 同一层的结点，从 index 开始如果相等的话，之前一定遍历到了
            if (i > index && nums[i] == nums[i - 1]) continue;
            temp.push_back(num);
            backtracking(nums, target, i + 1, sum + num, temp, ans);
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
        vector<vector<int>> ans;
        vector<int> temp;
        // 排序后方便去重
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0, 0, temp, ans);
        return ans;
    }
};

int main() {
    Solution *s = new Solution();
    vector<vector<int>> list = {{10, 1, 2, 7, 6, 1, 5}, {2, 5, 2, 1, 2}};
    vector<int> target = {8, 5};

    for (int i = 0; i < list.size(); i++) {
        auto ans = s->combinationSum2(list[i], target[i]);
        for (auto &i : ans) {
            for (auto &j : i) {
                cout << j << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}