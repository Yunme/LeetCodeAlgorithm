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
 * 29: 两数相除
 * 给你两个整数，被除数 dividend 和除数 divisor。将两数相除，要求 不使用
 * 乘法、除法和取余运算。
 * 整数除法应该向零截断，也就是截去（truncate）其小数部分。例如，8.345
 * 将被截断为 8 ，-2.7335 将被截断至 -2 。 返回被除数 dividend 除以除数 divisor
 * 得到的 商 。
 *
 * 注意：假设我们的环境只能存储 32 位 有符号整数，其数值范围是 [−231,  231 − 1]
 * 本题中，如果商 严格大于 231 − 1 ，则返回 231 − 1 ；如果商 严格小于 -231
 * ，则返回 -231
 * https://leetcode.cn/problems/container-with-most-water/description/
 */

class Solution {
   public:
    // 题目要求只能使用 32 位整数
    // 但 64位会更方便
    /**
     * 法1: 使用 64位 (超时)
     * 除法的本质：被除数 - 除数，看能减几次
     * 比如：20 /
     * 6：20-6=14，14-6=8，8-6=2；2<6停止，减了3次。20/6=3，但是这样减复杂度很高
     * 负数最小值再减 可能越界，转换为 long 64位
     */
    int divide(int dividend, int divisor) {
        if (divisor == 1) return dividend;
        if (dividend == divisor) return 1;
        // 判断符号
        int sign = 1;
        if (dividend < 0 && divisor > 0 ||
            dividend > 0 && divisor < 0)  // 直接判断
            sign = -1;
        // 或者使用位运算 异或：对应位相同：0，不同：1
        // sign = (dividend ^ divisor) >> 31 ? -1 : 1;
        long long dividend_long = abs((long long)dividend);
        long long divisor_long = abs((long long)divisor);
        long long ans = 0;
        while (dividend_long >= divisor_long) {
            dividend_long -= divisor_long;
            ans++;
        }
        ans *= sign;
        if (ans > INT_MAX || ans < INT_MIN) ans = INT_MAX;
        return ans;
    }

    /**
     * 法2: 使用 64位 法1：每次只减一个，减的太少，超时
     * 除法的本质：被除数 - 除数，看能减几次
     * 每次减的加倍
     * 比如：20 / 6：20-6=14，14-12=2，减了1+2=3次。20/6=3
     * 负数最小值再减 可能越界，转换为 long 64位
     */
    int divide2(int dividend, int divisor) {
        if (divisor == 1) return dividend;
        if (dividend == divisor) return 1;
        // 判断符号
        int sign = 1;
        // if (dividend < 0 && divisor > 0 ||
        //     dividend > 0 && divisor < 0)  // 直接判断
        //     sign = -1;
        // 或者使用位运算 异或：对应位相同：0，不同：1
        sign = (dividend ^ divisor) >> 31 ? -1 : 1;
        long long dividend_long = abs((long long)dividend);
        long long divisor_long = abs((long long)divisor);
        long long ans = 0;
        // 每次递减的翻倍，不能使用乘法，使用左移一位
        while (dividend_long >= divisor_long) {
            long long step = 1;
            long long temp = divisor_long;
            // 7 / 3: 7 - 3 = 4, 4 < 3*2, 4 - 3 = 1;
            // 里层递减，外层除数不变
            while (dividend_long >= temp) {
                dividend_long -= temp;
                ans += step;
                temp <<= 1;
                step <<= 1;
            }
        }
        ans *= sign;
        if (ans > INT_MAX || ans < INT_MIN) ans = INT_MAX;
        return ans;
    }

    /**
     * 法3：只使用 32 位 int
     * 为避免溢出，特殊情况判断
     * 再在 1~INT_MAX 内根据除法的定义二分查找满足
     * Z * Y >= X > (Z + 1) * Y 其中 Z 为商，X为被除数，Y为除数；
     */
    int divide3(int dividend, int divisor) {
        // 边界情况判断
        // 被除数为 int 最小值
        if (dividend == INT_MIN) {
            if (divisor == 1) return INT_MIN;  // 除数为1，返回本身
            if (divisor == -1)
                return INT_MAX;  // 除数为-1，INT_MIN 绝对值 = INT_MAX + 1, 返回
                                 // max
        }
        // 商为 int 最小值
        if (divisor == INT_MIN) {
            // 被除数也是 最小值，则是1
            // 否则其他数绝对值都比他小，则是0，
            return dividend == INT_MIN ? 1 : 0;
        }
        // 被除数为0，返回0
        if (dividend == 0) return 0;
        //  -2^31 取反，2^31 溢出了
        // 为了避免溢出，正数都变成负数,
        bool reverse = false;
        if (dividend > 0) {
            dividend = -dividend;
            reverse = !reverse;
        }
        if (divisor > 0) {
            divisor = -divisor;
            reverse = !reverse;
        }

        // 二分查找
        int left = 1, right = INT_MAX, ans = 0;
        while (left <= right) {
            // (left + right) / 2 可能会溢出
            int mid = left + ((right - left) >> 1);  // 不能使用除法，右移 除以2
            bool check = quickAnd(divisor, mid, dividend);
            if (check) {
                ans = mid;
                if (mid == INT_MAX) break;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return reverse ? -ans : ans;
    }
    // 不使用乘法，计算 y * z >= x 是否成立。
    // 速乘: 利用累加法
    bool quickAnd(int y, int z, int x) {
        // x y 是负数，z是正数
        int result = 0, add = y;
        while (z) {
            // 偶数二进制最低位是0，奇数为1，
            if (z & 1) {  // 奇数
                // 保证 result + add >= x;
                if (result < x - add) return false;
                result += add;  // 从 0 累加y
            }
            if (z != 1) {
                if (add < x - add) return false;
                add += add;
            }
            z >>= 1;
        }
        return true;
    }
};

int main() {
    Solution* solution = new Solution();
    vector<int> dividend = {10, 7, -1, -2147483648, 100};
    vector<int> divisor = {3, -3, 1, -1, 3};
    for (int i = 0; i < dividend.size(); i++) {
        cout << dividend[i] << "/" << divisor[i] << ":";
        int ans = solution->divide3(dividend[i], divisor[i]);
        cout << ans << endl;
    }
}