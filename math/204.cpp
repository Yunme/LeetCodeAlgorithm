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
 * 204: 计数质数
 * 给定整数 n，返回所有小于非负整数 n 的质数的数量
 * https://leetcode.cn/problems/count-primes/description/
 */

class Solution {
   public:
    bool isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return true;
    }
    /**
     * 暴力查找
     * 速度较慢，复杂度为 O(N*Sqrt(N))
     */
    int countPrimes(int n) {
        int ans = 0;
        for (int i = 2; i < n; i++) {
            if (isPrime(i)) {
                cout << i << endl;
                ans++;
            }
        }
        return ans;
    }

    /**
     * 埃氏筛法 厄拉多塞筛法
     * 如果 x 是质数，那么大于 x 的 2x,3x... 等都是合数;
     * 可以用标记法，如果 i 是质数，那么标记2i,3i... 等都不是质数;
     *
     * 为什么从 i * i 开始标记呢；
     * 因为对于 2*i,3*i 都被小于i的质数标记过了
     */
    int countPrimes2(int n) {
        // 默认都认为是质数
        vector<int> isPrime(n, 1);
        int ans = 0;
        // 从 2 开始，2是第一个质数：
        // 标记2的整数倍都不是质数
        for (int i = 2; i < n; i++) {
            if (isPrime[i]) {
                ans++;
                if ((long long)i * i < n) {
                    for (int j = i * i; j < n; j += i) {
                        isPrime[j] = 0;
                    }
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution* solution = new Solution();
    int n = 5000000;
    // int n = 20;
    int ans = solution->countPrimes2(n);
    cout << ans << endl;
}