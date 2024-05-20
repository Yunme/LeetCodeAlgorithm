#include <math.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * https://blog.csdn.net/weixin_48157259/article/details/138087531
 *
 * 12. 密码输入检测
 * 给定用户密码输入流 input，输入流中字符'<'表示退格，可以清除前一个输入的字符
 * 密码安全要求如下：
 * 1. 密码长度>=8.
 * 2. 密码至少需要包含 1 个大写字母;
 * 3. 密码至少需要包含 1 个小写字母;
 * 4. 密码至少需要包含 1 个数字;
 * 5. 密码至少需要包含 1 个字母和数字以外的非空白特殊字符
 * 6. 注意空串退格后仍然为空串，且用户输入的字符串不包含'<'字符和空白字符。
 * https://blog.csdn.net/weixin_48157259/article/details/138138171
 *
 * 输入:
 * 要检测的密码
 * 输出：
 * 输出经过程序处理后，输出的实际密码字符串，并输出改密码字符串是否满足密码安全要求。两者间由','分隔，
 * 例如：ABc89%00,true
 */

/**
 * < 可以连续输入，代表删除前n个
 */
bool validPassword(string &password) {
    stack<char> stack;
    for (char c : password) {
        if (c == '<') {
            if (!stack.empty()) {
                stack.pop();
            }
        } else {
            stack.push(c);
        }
    }
    string temp;
    while (!stack.empty()) {
        temp = stack.top() + temp;
        stack.pop();
    }
    password = temp;
    if (password.length() < 8) return false;
    int upper = 0, lower = 0, num = 0, ch = 0;
    for (char c : password) {
        if (isupper(c))
            upper = 1;
        else if (islower(c))
            lower = 1;
        else if (c >= '0' && c <= '9')
            num = 1;
        else
            ch = 1;
    }
    if (!upper || !lower || !num || !ch) {
        return false;
    }
    return true;
}

int main() {
    // string s = "ABC<c89%000<";
    string s = "ABC<c89%000<";
    // cin >> s;

    bool ans = validPassword(s);
    cout << s << "," << (ans ? "true" : "false") << endl;
}