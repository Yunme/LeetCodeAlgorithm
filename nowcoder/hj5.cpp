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
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * hj5 进制转换
 * 输入16进制数，输出十进制数
 * https://www.nowcoder.com/practice/8f3df50d2b9043208c5eed283d1d4da6
 */
int hexToDecimal(string s) {
    if (s.length() < 3) return 0;
    if (s.substr(0, 2) != "0x") return 0;
    s = s.substr(2, s.length() - 2);
    int n = 0;
    int j = 1;
    // 倒序 计算
    for (int i = s.length() - 1; i >= 0; i--) {
        char a = s[i];
        int k = a;
        // 0 - 9
        if (a >= '0' && a <= '9') {
            k = a - '0';
        } else if (a >= 'A' && a <= 'F') {
            // A - F
            k = 10 + a - 'A';
        } else if (a >= 'a' && a <= 'f') {
            // a - f
            k = 10 + a - 'a';
        }
        // 当前位累加
        n += j * k;
        // 下一位 *16
        j *= 16;
    }
    return n;
}

int main() {
    string a("0xaa");
    cin >> a;
    cout << hexToDecimal(a) << endl;
}