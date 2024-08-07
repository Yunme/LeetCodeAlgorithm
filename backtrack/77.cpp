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
 * 77: 组合
 * 给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。
 * 你可以按 任何顺序 返回答案。
 *
 * https://leetcode.cn/problems/combinations/description/
 */
class Solution {
   public:
    /**
     * 回溯 组合问题 （组合不在意顺序）
     */
    void backtracking(int n, int k, int index, vector<int> &temp,
                      vector<vector<int>> &ans) {
        cout << index << " ";
        // 收集到了 k 个 添加到结果集
        if (temp.size() == k) {
            ans.push_back(temp);
            return;
        }
        // 做选择，从当前向后选择
        for (int i = index; i <= n; i++) {
            // 当前值放入
            temp.push_back(i);
            // 下一个值
            backtracking(n, k, i + 1, temp, ans);
            // 回溯
            temp.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        // 结果集
        vector<vector<int>> ans;
        // 每个组合
        vector<int> temp;
        backtracking2(n, k, 1, temp, ans);
        return ans;
    }

    /**
     * 剪枝
     */
    void backtracking2(int n, int k, int index, vector<int> &temp,
                       vector<vector<int>> &ans) {
        cout << index << " ";
        // 收集到了 k 个 添加到结果集
        if (temp.size() == k) {
            ans.push_back(temp);
            return;
        }
        // 做选择，从当前向后选择
        // 如果当前待选择个数小于目标个数，则直接返回
        int size = temp.size();  // 当前已选择个数
        int remain = k - size;   // 还需要选择的个数
        // 剩余可选的：n - index + 1
        // 剩余可选的 小于 还需要选择的 直接return
        if (n - index + 1 < remain) return;
        // 或 i <= n - (k - temp.size()) + 1
        for (int i = index; i <= n; i++) {
            // 当前值放入
            temp.push_back(i);
            // 下一个值
            backtracking2(n, k, i + 1, temp, ans);
            // 回溯
            temp.pop_back();
        }
    }
};

int main() {
    Solution *s = new Solution();
    vector<int> n = {4, 1, 4};
    vector<int> k = {2, 1, 4};

    for (int i = 0; i < n.size(); i++) {
        auto ans = s->combine(n[i], k[i]);
        for (auto &i : ans) {
            for (auto &j : i) {
                cout << j << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}