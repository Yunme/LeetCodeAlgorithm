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
 * 9.有效子字符串
 * 输入两个字符串S和L，都只包含小写字母，len(S) <= 100，len(L) <=
 * 500000。判断S是否是L的有效子字符串。
 * 判定规则：S中的每个字符在L中都能找到（可以不连续），且S在L中字符的前后顺序与S中顺序要保持一致。
 *
 * https://blog.csdn.net/weixin_48157259/article/details/138081767
 *
 *
 * 输入:
 * 第一行：字符串S
 * 第二行：字符串L
 * 输出：
 * S串最后一个有效字符在 L 中的位置，首位从0开始，找不到返回-1.
 */

/**
 * 注意子串在主串中可以不是连续的。
 */
int validString(string &main, string &sub) {
    int i = 0, j = 0;
    while (i < main.length() && j < sub.length()) {
        if (main[i] == sub[j]) {
            j++;
        }
        i++;
    }
    if (j == sub.length()) {
        return i - 1;
    }
    return -1;
}

int main() {
    string sub;
    getline(cin, sub);
    string main;
    getline(cin, main);

    int ans = validString(main, sub);
    cout << ans << endl;
}