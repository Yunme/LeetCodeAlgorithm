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
 * 22：括号生成
 * 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且
 * 有效的 括号组合。
 *
 * https://leetcode.cn/problems/generate-parentheses/description/
 */
class Solution {
   public:
    /**
     * 回溯法
     * @param left 当前串左括号个数
     * @param right 当前串有括号个数
     */
    void backtrack(int n, int left, int right, string &temp,
                   vector<string> &ans) {
        // 个数够了
        if (temp.length() == 2 * n) {
            ans.push_back(temp);
            return;
        }

        // 左括号个数小于n
        if (left < n) {
            // 拼接左括号
            temp += "(";
            // 下一位
            backtrack(n, left + 1, right, temp, ans);
            // 回溯 去掉
            temp.pop_back();
        }
        // 右括号个数小于n，且右括号个数小于左括号个数
        if (right < n && right < left) {
            // 拼接右括号
            temp += ")";
            // 下一位
            backtrack(n, left, right + 1, temp, ans);
            // 回溯
            temp.pop_back();
        }
    }
    vector<string> generateParenthesis(int n) {
        string temp;
        vector<string> ans;
        backtrack(n, 0, 0, temp, ans);
        return ans;
    }
};

int main() {
    Solution *s = new Solution();
    vector<int> list = {3, 1, 2};
    // list = {2};
    for (auto &i : list) {
        auto ans = s->generateParenthesis(i);
        for (auto &str : ans) {
            cout << str << ", ";
        }
        cout << endl;
    }
}