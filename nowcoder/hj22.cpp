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
 * hj22 汽水瓶
 * 某商店规定：三个空汽水瓶可以换一瓶汽水，允许向老板借空汽水瓶（但是必须要归还）。
 * 小张手上有n个空汽水瓶，她想知道自己最多可以喝到多少瓶汽水。
 * https://www.nowcoder.com/practice/fe298c55694f4ed39e256170ff2c205f
 */

/**
 * 递归版本
 * @param n 手里的空瓶数
 */
int drinkCount(int n) {
    cout << n << " " << endl;
    // 手里 1个没法换
    if (n <= 1) {
        return 0;
    }
    // 手里2个再借1个，换1个
    if (n == 2) {
        return 1;
    }
    // 大于2个，能换 n / 3 个，剩下 n % 3 个。
    // 比如3个，换完手里还有1个空瓶。
    // 购买个数 + n / 3;
    return n / 3 + drinkCount(n % 3 + n / 3);
}

/**
 * 迭代版本
 */
int drinkCount2(int n) {
    int count = 0;
    while (n > 1) {
        if (n == 2) {
            count++;
            n = 0;
        } else {
            count += n / 3;
            n = n % 3 + n / 3;
        }
    }
    return count;
}

/**
 * 简单版本：数学方法：
 * 分析得知：自己2个加上借的1个就能换一个。
 * 所以每2个就能换一个 = n / 2;
 */
int drinkCount3(int n) { return n / 2; }

int main() {
    int s;
    while (cin >> s) {
        if (s > 0) {
            cout << drinkCount3(s) << endl;
        }
    }

    return 0;
}