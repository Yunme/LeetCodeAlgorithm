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
#include <sstream>
#include <stack>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * hj13 句子逆序
 * 将一个句子按单词为单位逆序输出
 * https://www.nowcoder.com/practice/48b3cb4e3c694d9da5526e6255bb73c3
 */

/**
 * 法1：
 * 自己实现 split 空格，将结果逆序输出
 */
string reverseSentence(string &s) {
    vector<string> list;
    string r;

    // 按空格分割存储到 list 里
    int start = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            list.push_back(s.substr(start, i - start));
            start = i + 1;
        } else if (i == s.length() - 1) {
            list.push_back(s.substr(start, i - start + 1));
        }
    }
    // 逆序输出list，中间添加空格
    for (auto i = list.rbegin(); i != list.rend(); i++) {
        r += *i;
        if (i < list.rend()) {
            r += ' ';
        }
    }
    return r;
}

/**
 * 法2：
 * 倒序遍历，碰到非空格 入栈
 * 碰到空格，全部出栈
 * 遍历结束后，再出栈
 */
void reverseSentence2(string &s) {
    stack<char> stack;
    for (int i = s.length() - 1; i >= 0; i--) {
        char c = s[i];
        if (c == ' ') {
            while (!stack.empty()) {
                cout << stack.top();
                stack.pop();
            }
            cout << c;
        } else {
            stack.push(c);
        }
    }
    while (!stack.empty()) {
        cout << stack.top();
        stack.pop();
    }
}

int main() {
    string a;
    while (getline(cin, a)) {
        // cout << reverseSentence(a) << endl;
        reverseSentence2(a);
    }
    return 0;
}