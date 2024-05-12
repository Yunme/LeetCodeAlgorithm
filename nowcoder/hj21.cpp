#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <fstream>
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
 * hj21 简单密码
 * 现在有一种密码变换算法。
 * 九键手机键盘上的数字与字母的对应： 1--1， abc--2, def--3, ghi--4, jkl--5,
 * mno--6, pqrs--7, tuv--8,
 * wxyz--9,0--0，把密码中出现的小写字母都变成九键键盘对应的数字，
 * 如：a 变成 2，x 变成 9.
 * 大写字母则变成小写之后往后移一位，如：X，先变成小写，再往后移一位，变成了y
 * ，例外：Z 往后移是 a 。 数字和其它的符号都不做变换。
 * https://www.nowcoder.com/practice/7960b5038a2142a18e27e4c733855dac
 */
string encode(string &password) {
    string result;
    for (char c : password) {
        char d = c;
        if (c >= 'a' && c <= 'z') {
            if (c < 'd')
                d = '2';
            else if (c < 'g')
                d = '3';
            else if (c < 'j')
                d = '4';
            else if (c < 'm')
                d = '5';
            else if (c < 'p')
                d = '6';
            else if (c < 't')
                d = '7';
            else if (c < 'w')
                d = '8';
            else
                d = '9';
        } else if (c >= 'A' && c <= 'Z') {
            // 库函数：tolower(c)
            char lower = 'a' + c - 'A';
            if (lower == 'z')
                d = 'a';
            else
                d = lower + 1;
        }
        result += d;
    }
    return result;
}

int main() {
    string s;
    while (cin >> s) {
        cout << encode(s) << endl;
    }

    return 0;
}