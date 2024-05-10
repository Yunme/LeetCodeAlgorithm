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
 * hj12 字符串反转
 * 反转字符串
 * https://www.nowcoder.com/practice/e45e078701ab4e4cb49393ae30f1bb04
 */

/**
 * 两种逆序遍历过程
 */
string reverseStr(string s) {
    string r;
    for (auto t = s.rbegin(); t != s.rend(); t++) {
        r += *t;
    }

    // for (int i = s.length() - 1; i >= 0; i--) {
    //     r += s[i];
    // }
    return r;
}

int main() {
    string a;
    while (getline(cin, a)) {
        cout << reverseStr(a) << endl;
    }
    return 0;
}