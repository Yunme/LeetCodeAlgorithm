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
 * 20：有效的括号
 * 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
 * 有效字符串需满足：
 * 1. 左括号必须用相同类型的右括号闭合。
 * 2. 左括号必须以正确的顺序闭合。
 * 3. 每个右括号都有一个对应的相同类型的左括号。。
 *
 * https://leetcode.cn/problems/valid-parentheses
 */
class Solution {
   public:
    /**
     * 使用栈
     */
    bool isValid(string s) {
        stack<char> stack;
        int n = s.length();
        for (int i = 0; i < n; i++) {
            char c = s[i];
            if (!stack.empty()) {
                // 栈不为空，尝试匹配
                char top = stack.top();
                if (top == '(' && c == ')' || top == '{' && c == '}' ||
                    top == '[' && c == ']')
                    // 栈顶跟当前元素匹配，栈顶出栈
                    stack.pop();
                else
                    // 不匹配入栈
                    stack.push(c);
            } else
                // 栈为空 入栈
                stack.push(c);
        }
        return stack.empty();
    }
};

int main() {
    Solution* s = new Solution();

    vector<string> list = {"{}", "()[]{}", "(]"};
    for (int i = 0; i < list.size(); i++) {
        bool ans = s->isValid(list[i]);
        cout << ans << endl;
    }
}