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
 * hj11 数字颠倒
 * 将输入的整数，以字符串形式逆序输出
 * https://www.nowcoder.com/practice/ae809795fca34687a48b172186e3dafe
 */

/**
 * 简单版：
 * 转成字符串 再将字符串逆序输出
 */
string reverseInt(int num) {
    string s = to_string(num);
    reverse(s.begin(), s.end());
    return s;
}

/**
 * 除10求余 获取最后一位
 * 使用 stringstream 拼接成字符串
 */
string reverseInt2(int num) {
    if (num == 0) {
        return "0";
    }

    stringstream s;
    while (num > 0) {
        s << num % 10;
        // string + to_string(num);
        num /= 10;
    }
    return s.str();
}

int main() {
    int a = 1200;
    while (cin >> a) {
        cout << reverseInt2(a) << endl;
    }
    return 0;
}