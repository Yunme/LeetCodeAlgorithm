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
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 1047：删除字符串中的所有相邻重复项
 *
 * 给出由小写字母组成的字符串
 * S，重复项删除操作会选择两个相邻且相同的字母，并删除它们。 在 S
 * 上反复执行重复项删除操作，直到无法继续删除。
 * 在完成所有重复项删除操作后返回最终的字符串。答案保证唯一。
 *
 * https://leetcode.cn/problems/remove-all-adjacent-duplicates-in-string/description/
 */
class Solution {
   public:
    /**
     * 栈实现
     */
    string removeDuplicates(string s) {
        int n = s.length();
        stack<char> stack;
        for (int i = 0; i < n; i++) {
            char c = s[i];
            if (!stack.empty()) {
                if (c == stack.top()) {
                    stack.pop();
                } else {
                    stack.push(c);
                }
            } else {
                stack.push(c);
            }
        }
        string ans;
        while (!stack.empty()) {
            ans = stack.top() + ans;
            stack.pop();
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();

    vector<string> list = {"abbaca"};
    for (int i = 0; i < list.size(); i++) {
        auto ans = s->removeDuplicates(list[i]);
        cout << ans << endl;
    }
}