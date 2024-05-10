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
 * hj6 质数因子
 * 输出一个正整数的质数因子
 * https://www.nowcoder.com/practice/196534628ca6490ebce2e336b47b3607
 */
bool isPrime(int num);
vector<int> primeFactor(int num) {
    std::vector<int> factors;
    if (num <= 1) {
        return factors;  // 质因数要求大于1
    }
    for (int i = 2; i * i <= num; ++i) {
        while (num % i == 0) {
            // 找到一个质因数
            factors.push_back(i);
            // 更新 num，继续找质因数
            num /= i;
        }
    }
    // 如果最后剩下一个大于1的数，则也是质因数
    if (num > 1) {
        factors.push_back(num);
    }
    return factors;
}

bool isPrime(int num) {
    // 能被 大于1 的数和小于 此数的数整除，说明不是质数。
    // 可以优化成只判断 小于 num 平方根的数，
    // 因为如果能被大于平方根的数整除，那么商必然小于平方根，而这个商已经试过了。
    for (int i = 2; i * i < num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int num = 180;
    while (cin >> num) {
        for (int i : primeFactor(num)) {
            cout << i << " ";
        }
        cout << endl;
    }
}