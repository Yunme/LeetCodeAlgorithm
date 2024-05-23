#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
/**
 * Honor
 * 寻找素数对
 *
 * 寻找和等于给定偶数的两个素数，
 * 并要求这两个素数尽可能接近。
 * 输入：素数n
 * 输出：a + b = n， a 和 b都是素数，并且最接近。
 */

/**
 * 自己实现：
 * 最接近的，其中某个肯定是小于 n/2的。
 * 从 n/2 开始递减的找，i 和 n-i 都是素数的返回
 */
bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int m = 0;
    cin >> m;
    //  不是偶数
    if (m % 2 != 0) {
        cout << 0 << endl;
        return 0;
    }
    for (int i = m / 2; i >= 1; --i) {
        if (isPrime(i) && isPrime(m - i)) {
            cout << i << " " << m - i << endl;
            break;
        }
    }
    return 0;
}
