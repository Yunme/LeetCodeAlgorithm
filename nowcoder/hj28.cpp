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
 * hj27 素数伴侣
 * 素数伴侣为：两个正整数的和为素数，那么这两个正整数就是素数伴侣
 *
 * 在一组数中，找出最多的素数伴侣个数。
 *
 * 输入：
 * 输入1个正整数n，后面输入n个待挑选数字。
 * 输出：
 * 最多的素数伴侣的对数
 * https://www.nowcoder.com/practice/b9eae162e02f4f928eac37d7699b352e
 */

/**
 * 指派问题：
 * 
 * 素数，除了2是偶数，其他全是奇数
 * 2个数的和是奇数，那么一定是奇数 + 偶数。
 * 所以此问题就是从一堆奇数 和 一堆偶数中相连，堆内部不会相连。就叫二分图
 * 二分图的匹配，称为：匈牙利算法，
 */

/**
 * 判断是否是素数
 */
bool isPrime(int num) {
    if (num <= 1) {
        return false;
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

/**
 * 寻找 与奇数x相匹配的偶数
 * @param x 当前奇数
 * @param evens 偶数列表
 * @param used 查找过的偶数列表，查找过的标记为1
 * @param evenMatch 跟偶数列表一一对应，对应位置存储的是与当前偶数匹配的奇数
 */
bool find(int x, vector<int> &evens, vector<int> &used,
          vector<int> &evenMatch) {
    // 遍历偶数，寻找哪些与当前传入的奇数相匹配。
    for (int i = 0; i < evens.size(); i++) {
        // 如果当前偶数与传入的奇数相匹配，
        // 并且当前偶数尚未匹配过奇数
        if (isPrime(x + evens[i]) && used[i] == 0) {
            // 设置标记位
            used[i] = 1;
            // 当前偶数还未匹配到奇数
            // 或
            // 当前偶数匹配到过奇数了，并且匹配的奇数也能找到匹配的偶数。
            // 那么，奇数 x 是偶数 i 的伴侣
            if (evenMatch[i] == 0 ||
                find(evenMatch[i], evens, used, evenMatch)) {
                evenMatch[i] = x;
                return true;
            }
        }
    }
    return false;
}

int findPrimePartner(vector<int> &nums) {
    vector<int> evens, odds;
    // 偶数、奇数分组
    for (int i : nums) {
        if (i % 2 == 0) {
            evens.push_back(i);
        } else {
            odds.push_back(i);
        }
    }
    // 遍历奇数和偶数匹配
    int result = 0;
    // 记录匹配的奇数
    vector<int> evenMatch(evens.size());
    for (int i : odds) {
        vector<int> used(evens.size());
        if (find(i, evens, used, evenMatch)) {
            result++;
        }
    }
    return result;
}

int main() {
    int n = 4;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int count = findPrimePartner(nums);
    cout << count << endl;
    return 0;
}