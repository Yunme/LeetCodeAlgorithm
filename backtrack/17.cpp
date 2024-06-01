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
 * 17: 电话号码的字母组合
 * 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按
 * 任意顺序 返回。 给出数字到字母的映射如下（与电话按键相同）。注意 1
 * 不对应任何字母。
 *
 * https://leetcode.cn/problems/letter-combinations-of-a-phone-number/description/
 */
class Solution {
   private:
    unordered_map<char, vector<string>> map = {
        {'2', {"a", "b", "c"}}, {'3', {"d", "e", "f"}},
        {'4', {"g", "h", "i"}}, {'5', {"j", "k", "l"}},
        {'6', {"m", "n", "o"}}, {'7', {"p", "q", "r", "s"}},
        {'8', {"t", "u", "v"}}, {'9', {"w", "x", "y", "z"}},
    };

   public:
    /**
     * 回溯法 自己实现（回溯树结构）
     * @param startIdx, 当前取的 index
     * @param temp 临时组合，每个组合收集完后放入 ans
     */
    void backtrack(string &digits, int startIdx, string &temp,
                   vector<string> &ans) {
        // 每个组合收集完
        if (startIdx > digits.length() || temp.length() == digits.length()) {
            ans.push_back(temp);
            return;
        }
        // 当前列表
        vector<string> list = map[digits[startIdx]];
        for (size_t i = 0; i < list.size(); i++) {
            // 当前字符放入
            temp += list[i];
            // cout << temp << " ";
            // 下一个字符
            backtrack(digits, startIdx + 1, temp, ans);
            // 当前字符去掉，回溯
            temp.pop_back();
            // cout << temp << " ";
        }
    }
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        vector<string> ans;
        string temp;
        backtrack(digits, 0, temp, ans);
        return ans;
    }
};

int main() {
    Solution *s = new Solution();
    vector<string> list = {"23", "", "2", "654"};
    for (auto &i : list) {
        auto ans = s->letterCombinations(i);
        for (auto &str : ans) {
            cout << str << " ";
        }
        cout << endl;
    }
}