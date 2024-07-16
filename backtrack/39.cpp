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
 * 39: 组合总和
 * 给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，
 * 找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合
 * 并以列表形式返回。 你可以按 任意顺序 返回这些组合。
 *
 * candidates 中的 同一个数字可以 无限制重复被选取 。
 * 如果至少一个数字的被选数量不同，则两种组合是不同的。
 *
 * 对于给定的输入，保证和为 target 的不同组合数少于 150 个。
 *
 * https://leetcode.cn/problems/combination-sum/description/
 */
class Solution {
   public:
    /**
     * 回溯
     */
    void backtracking(vector<int> &nums, int target, int index,
                      vector<int> &temp, int sum, vector<vector<int>> &ans) {
        // 路径和等于目标 添加到结果集
        if (sum == target) {
            ans.push_back(temp);
            return;
        }
        // 遍历选择集，选择集是 [index, n-1] 当前及之后的元素(可以重复选取)
        // 组合：要么选自己，要么选后面的
        // 并剪枝：当前和不能超过目标，否则无效
        for (int i = index; i < nums.size(); i++) {
            int num = nums[i];
            if (sum + num > target) {
                continue;
            }
            temp.push_back(num);
            // 可以重复选取 i 处还可以选，
            backtracking(nums, target, i, temp, sum + num, ans);
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        vector<int> temp;
        vector<vector<int>> ans;
        backtracking(candidates, target, 0, temp, 0, ans);
        return ans;
    }
};

int main() {
    Solution *s = new Solution();
    vector<vector<int>> list = {{2, 3, 6, 7}, {2, 3, 5}, {2}, {8, 7, 4, 3}};
    vector<int> target = {7, 8, 1, 11};

    for (int i = 0; i < list.size(); i++) {
        auto ans = s->combinationSum(list[i], target[i]);
        for (auto &i : ans) {
            for (auto &j : i) {
                cout << j << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}