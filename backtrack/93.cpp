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
 * 93：复原 IP 地址
 * 有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导
 * 0），整数之间用 '.' 分隔。 例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP
 * 地址，但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效 IP
 * 地址。
 *
 * 给定一个只包含数字的字符串 s ，用以表示一个 IP
 * 地址，返回所有可能的有效 IP 地址，这些地址可以通过在 s 中插入 '.' 来形成。 你
 * 不能 重新排序或删除 s 中的任何数字。你可以按 任何 顺序返回答案。
 *
 * https://leetcode.cn/problems/restore-ip-addresses/description/
 */
class Solution {
   public:
    /**
     * 检查子串是否符合 ip 地址
     */
    bool checkNum(string &s, int start, int end) {
        if (start > end) return false;
        int n = end - start + 1;
        // 检查前导 0
        if (n > 1 && s[start] == '0') return false;
        // 最多 255 三位
        if (n >= 4) return false;
        // 转成 整型
        int num = stoi(s.substr(start, n));
        // [0, 255]
        return num <= 255 && num >= 0;
    }
    void backtracking(string &s, int index, int &dotCount,
                      vector<string> &ans) {
        // 合法的 IP 点的数量为3
        if (dotCount == 3) {
            // 检查最后一段的合法性
            if (checkNum(s, index, s.length() - 1)) {
                // 如果合法 加入结果集
                ans.push_back(s);
            }
            return;
        }
        // 剪枝 子串长度小于等于 3.
        // 当前层最多循环 3 次
        for (int i = index; i < s.length() && i <= index + 3; i++) {
            if (!checkNum(s, index, i)) {
                continue;
            }
            // [index, i] 满足合法条件
            // 在源字符串 i + 1 处插入 .
            s.insert(s.begin() + i + 1, '.');
            dotCount++;
            // 已经加了一个 . 下一步递归要 + 2
            backtracking(s, i + 2, dotCount, ans);
            dotCount--;
            s.erase(s.begin() + i + 1);
        }
    }
    vector<string> restoreIpAddresses(string s) {
        int dotCount = 0;
        vector<string> ans;
        backtracking(s, 0, dotCount, ans);
        return ans;
    }
};

int main() {
    // string a = "1";
    // string b = "333";
    // a.append(b);
    // cout << a << endl;
    // a.erase(a.length() - 3, 3);
    // cout << a << endl;

    Solution *s = new Solution();
    vector<string> list = {{"25525511135", "0000", "101023"}};

    for (int i = 0; i < list.size(); i++) {
        auto ans = s->restoreIpAddresses(list[i]);
        for (auto &s : ans) {
            cout << s << " ";
        }
        cout << endl;
    }
}