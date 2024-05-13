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
 * hj23 删除字符串中出现次数最少的字符
 * 实现删除字符串中出现次数最少的字符，若出现次数最少的字符有多个，则把出现次数最少的字符都删除。
 * 输出删除这些单词后的字符串，字符串中其它字符保持原来的顺序。
 * https://www.nowcoder.com/practice/05182d328eb848dda7fdd5e029a56da9
 */

string deleteTheLeast(string s) {
    // 字符串中出现的字符 个数统计
    unordered_map<char, int> map;
    for (char c : s) {
        map[c]++;
    }
    // 找出出现次数最少的字符加到 set 中。
    int min = INT_MAX;
    unordered_set<char> minC;
    for (auto &[k, v] : map) {
        if (v < min) {
            min = v;
            minC.clear();
            minC.insert(k);
        } else if (v == min) {
            minC.insert(k);
        }
    }

    // 遍历字符串删除在 set 中的字符
    auto i = s.begin();
    while (i != s.end()) {
        char c = *i;
        auto pos = minC.find(c);
        if (pos != minC.end()) {
            s.erase(i);
        } else {
            i++;
        }
    }

    return s;
}

int main() {
    string s = "aabcddd";
    // cout << deleteTheLeast(s) << endl;
    while (cin >> s) {
        cout << deleteTheLeast(s) << endl;
    }

    return 0;
}