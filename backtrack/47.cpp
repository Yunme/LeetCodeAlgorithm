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
 * 47: 全排列II
 * 给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。
 *
 * https://leetcode.cn/problems/permutations-ii/description/
 */
class Solution {
   public:
    /**
     * 法1：回溯
     * 使用 used 数组来存储当前元素是否访问过
     */
    void backtrack(vector<int> &nums, vector<int> &used, vector<int> &temp,
                   vector<vector<int>> &ans) {
        if (temp.size() == nums.size()) {
            ans.push_back(temp);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            // 用过了
            if (used[i]) continue;
            // 相同元素去重
            if (i > 0 && used[i - 1] && nums[i] == nums[i - 1]) continue;
            used[i] = 1;
            temp.push_back(nums[i]);
            backtrack(nums, used, temp, ans);
            used[i] = 0;
            temp.pop_back();
        }
    }
    vector<vector<int>> permuteUnique(vector<int> &nums) {
        vector<vector<int>> ans;
        vector<int> permute;
        vector<int> used(nums.size());
        sort(nums.begin(), nums.end());
        backtrack(nums, used, permute, ans);
        return ans;
    }
};

int main() {
    Solution *s = new Solution();
    vector<vector<int>> list = {{1, 1, 2}, {1, 2, 3}};
    for (auto &i : list) {
        auto ans = s->permuteUnique(i);
        for (auto &j : ans) {
            for (auto &k : j) {
                cout << k << " ";
            }
            cout << ",";
        }
        cout << endl;
    }
}