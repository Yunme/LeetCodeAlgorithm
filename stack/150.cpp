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
 * 150：逆波兰表达式求值
 * 给你一个字符串数组 tokens ，表示一个根据 逆波兰表示法 表示的算术表达式。
 * 请你计算该表达式。返回一个表示表达式值的整数。
 * 注意：
 * 有效的算符为 '+'、'-'、'*' 和 '/' 。
 * 每个操作数（运算对象）都可以是一个整数或者另一个表达式。
 * 两个整数之间的除法总是 向零截断 。
 * 表达式中不含除零运算。
 * 输入是一个根据逆波兰表示法表示的算术表达式。
 * 答案及所有中间计算结果可以用 32 位 整数表示。
 *
 * https://leetcode.cn/problems/evaluate-reverse-polish-notation/description
 * 逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。
 */

class Solution {
   public:
   /**
    * 直接栈操作
    * 遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中
    */
    int evalRPN(vector<string> &tokens) {
        int n = tokens.size();
        stack<int> stack;
        for (int i = 0; i < n; i++) {
            string s = tokens[i];
            // 运算符 出栈顶两个数字计算
            if (s == "+" || s == "-" || s == "*" || s == "/") {
                int top1 = stack.top();
                stack.pop();
                int top2 = stack.top();
                stack.pop();
                int ans = 0;
                if (s == "+") {
                    ans = top2 + top1;
                } else if (s == "-") {
                    ans = top2 - top1;
                } else if (s == "*") {
                    ans = top2 * top1;
                } else {
                    ans = top2 / top1;
                }
                // 计算后 入栈
                stack.push(ans);
            } else {
                // 数字直接入栈
                stack.push(stoi(s));
            }
        }
        return stack.top();
    }
};

int main() {
    Solution *s = new Solution();
    vector<vector<string>> list = {
        {"2", "1", "+", "3", "*"},
        {"4", "13", "5", "/", "+"},
        {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"}};
    for (auto &i : list) {
        auto ans = s->evalRPN(i);
        cout << ans << endl;
    }
}