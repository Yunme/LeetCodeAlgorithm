#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/**
 * 27:解密犯罪时间
 * OJ：100%
 * 警察在侦破一个案件时，得到了线人给出的可能犯罪时间，形如“HH:MM”表示的时刻。
 * 根据警察和线人的约定，为了隐蔽，该时间是修改过的解密规则为:
 * 利用当前出现过的数字，构造下一个距离
 * 当前时间只最近的时刻，则该时间为可能的犯罪时间。
 * 每个出现数字都可以被无限次使用。
 * 输入：形如HH:MM的字符串
 * 输出：
 * 推理出的可能的犯罪时间
 */
#include <climits>
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
    int num = 51;
    //    cout << isPrime(num) << endl;
    //    for (int i = 1; i <= 223m / 2; ++i) {
    //        if (isPrime(i) && isPrime(m - i)) {
    //            cout << i << " " << m - i << endl;
    //        }
    //    }

    for (int i = m / 2; i >= 1; --i) {
        if (isPrime(i) && isPrime(m - i)) {
            cout << i << " " << m - i << endl;
            break;
        }
    }

    return 0;
}
