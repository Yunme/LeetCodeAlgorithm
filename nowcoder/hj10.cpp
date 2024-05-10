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
#include <stack>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * hj10 字符个数统计
 * 统计字符串中出现的不同字符的个数
 * https://www.nowcoder.com/practice/eb94f6a5b2ba49c6ac72d40b5ce95f50
 */

/**
 * set 用于保存出现过的字符
 */
int countChar(const string &str) {
    unordered_set<char> set;
    int count = 0;
    for (char c : str) {
        if (set.find(c) == set.end()) {
            // 没出现 则+1
            set.insert(c);
            count++;
        }
    }
    return count;
}

int main() {
    string s;
    while (getline(cin, s)) {
        cout << countChar(s) << endl;
    }
    return 0;
}