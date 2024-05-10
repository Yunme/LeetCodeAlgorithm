#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * hj7 取近似值
 * 输入一个浮点数，输出就近取整
 * https://www.nowcoder.com/practice/3ab09737afb645cc82c35d56a5ce802a
 */

int round(float num) {
    // 整数位
    int a = (int)num;
    // 小数位
    float b = num - a;
    // 如果小数位 >= 0.5 a + 1
    // < 0.5 a + 0
    return a + (b >= 0.5);
}

/**
 * 加 0.5 直接取整数位
 */
int round2(float num) { return int(num + 0.5); }

int main() {
    float num = 6.32;
    while (cin >> num) {
        cout << round2(num) << endl;
    }
}