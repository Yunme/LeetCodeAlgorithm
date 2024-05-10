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
 * hj15 求int整数在内存中存储1的个数
 * 10进制转成二进制中1的个数
 * https://www.nowcoder.com/practice/440f16e490a0404786865e99c6ad91c9
 */

/**
 * 法1：
 * 库函数 biset
 */
int countOne(int num) {
    bitset<32> binary(num);
    int count = 0;

    for (char c : binary.to_string()) {
        if (c == '1') {
            count++;
        }
    }

    // 或者直接返回这个 count 是设置过的位的个数
    // binary.count();
    return count;
}

/**
 * 法2：
 * 短除法，转换成二进制
 * 数除以2取余 就是当前位的二进制数
 */
int countOne2(int num) {
    int count = 0;
    while (num > 0) {
        int remainder = num % 2;
        if (remainder == 1) {
            count++;
        }
        num /= 2;
    }
    return count;
}

/**
 * 法3：位运算
 */
int countOne3(int num) {
    int count = 0;

    while (num != 0) {
        // 与 1
        if (num & 1) {
            count++;
        }
        // 右移一位
        num >>= 1;
    }
    return count;
}

int main() {
    int n = 8;
    while (cin >> n) {
        cout << countOne3(n) << endl;
    }
    return 0;
}