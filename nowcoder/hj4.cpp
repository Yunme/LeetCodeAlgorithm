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
 * hj4 字符串分割
 * 按长度为8拆分每个输入字符串并进行输出
 * https://www.nowcoder.com/practice/d9162298cb5a437aad722fccccaae8a7
 */

/**
 * 法1：
 * 每8位遍历字符串，如果不足，拼接 '0' 到8位满
 */
vector<string> splitString(string s, int k) {
    vector<string> result;
    int len = s.length();
    for (int i = 0; i < len; i += k) {
        string sub;
        if (i + k > len) {
            sub = s.substr(i, len - i);
            for (int j = 0; j < k - len + i; j++) {
                sub += '0';
            }
        } else {
            sub = s.substr(i, k);
        }
        result.push_back(sub);
    }
    return result;
}

/**
 * 法2：
 * 根据求余算出，整个字符串差多少位满 k 的整数倍，补齐0，
 * 每 k 位输出
 */
void splitString2(string s, int k) {
    int len = s.length();
    int less = k - s.length() % k;
    while (less > 0 && less < k) {
        s += '0';
        less--;
    }
    for (int i = 0; i < s.length(); i += k) {
        cout << s.substr(i, k) << endl;
    }
}

int main() {
    string a("12345678");
    cin >> a;
    // for (string &s : splitString(a, 8)) {
    //     cout << s << endl;
    // }

    splitString2(a, 8);
}