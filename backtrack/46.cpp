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
 * 46: 全排列
 * 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。
 * 你可以 按任意顺序 返回答案。
 * https://leetcode.cn/problems/permutations/description/
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
            if (!used[i]) {
                used[i] = 1;
                temp.push_back(nums[i]);
                backtrack(nums, used, temp, ans);
                used[i] = 0;
                temp.pop_back();
            }
        }
    }
    vector<vector<int>> permute(vector<int> &nums) {
        vector<vector<int>> ans;
        vector<int> permute;
        vector<int> used(nums.size());
        backtrack(nums, used, permute, ans);
        return ans;
    }
};

int main() {
    Solution *s = new Solution();
    vector<vector<int>> list = {{1, 2, 3}, {0, 1}, {1}};
    for (auto &i : list) {
        auto ans = s->permute(i);
        for (auto &j : ans) {
            for (auto &k : j) {
                cout << k << " ";
            }
            cout << ",";
        }
        cout << endl;
    }
}