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
 * 216: 组合总和 III
 * 找出所有相加之和为 n 的 k 个数的组合，且满足下列条件：
 * 只使用数字1到9
 * 每个数字 最多使用一次
 * 返回 所有可能的有效组合的列表
 * 。该列表不能包含相同的组合两次，组合可以以任何顺序返回。
 *
 * https://leetcode.cn/problems/combination-sum-iii/description/
 */
class Solution {
   public:
    /**
     * 回溯 + 剪枝
     */
    void backtracking(int k, int n, int num, int sum, vector<int> &temp,
                      vector<vector<int>> &ans) {
        // cout << sum << " ";
        if (sum == n && temp.size() == k) {
            ans.push_back(temp);
            return;
        }
        // 两种剪枝思路：总和，元素个数
        // 已选择的数字个数
        // 剪枝 剩余可选的要大于等于需要选择的个数
        // if (9 - num + 1 < k - size) return;
        // 当前总和需要小于等于目标值 n
        for (int i = num; i <= 9 - (k - temp.size()) + 1 && sum + i <= n; i++) {
            temp.push_back(i);
            backtracking(k, n, i + 1, sum + i, temp, ans);
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> temp;
        vector<vector<int>> ans;
        backtracking(k, n, 1, 0, temp, ans);
        return ans;
    }
};

int main() {
    Solution *s = new Solution();
    vector<int> k = {3, 3, 4};
    vector<int> n = {7, 9, 1};

    for (int i = 0; i < n.size(); i++) {
        auto ans = s->combinationSum3(k[i], n[i]);
        for (auto &i : ans) {
            for (auto &j : i) {
                cout << j << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}