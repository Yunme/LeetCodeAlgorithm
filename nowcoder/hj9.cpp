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
#include <utility>
#include <vector>
using namespace std;

/**
 * hj9 提取不重复的整数
 * 整数，从右向左阅读，返回不包含重复数字的新的整数
 * https://www.nowcoder.com/practice/253986e66d114d378ae8de2e6c4577c1
 */

/**
 * 法1：转成字符串
 * 每位转换成数字，存储在数组中，代表该位数字出现次数
 * 逆序遍历，出现了则拼接，并将次数设成 0
 */
int reverseInt(int num) {
    string s = to_string(num);
    int arr[10] = {0};
    for (char i : s) {
        arr[i - '0']++;
    }
    string r;
    for (int i = s.length() - 1; i >= 0; i--) {
        int index = s[i] - '0';
        if (arr[index] > 0) {
            r += s[i];
            arr[index] = 0;
        }
    }
    // 转成 int
    return stoi(r);
}

/**
 * 法2：不转字符串
 * 通过除以10取余法 获得个位，再除以10，缩小一位。
 * 累加余数
 */
int reverseInt2(int num) {
    int arr[10] = {0};
    int r = 0;
    while (num != 0) {
        // 个位
        int mod = num % 10;
        arr[mod]++;
        // 只有当 mod 出现一次才累加
        if (arr[mod] <= 1) {
            r = r * 10 + mod;
        }
        // 缩小一位
        num /= 10;
    }
    return r;
}

int main() {
    int num;
    while (cin >> num) {
        cout << reverseInt2(num) << endl;
    }
    return 0;
}