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
 * 3: 整数转罗马数字
 *
 * 七个不同的符号代表罗马数字，其值如下：
 * I	1
 * V	5
 * X	10
 * L	50
 * C	100
 * D	500
 * M	1000
 * 罗马数字是通过添加从最高到最低的小数位值的转换而形成的。将小数位值转换为罗马数字有以下规则：
 * 1. 如果该值不是以 4 或 9
 * 开头，请选择可以从输入中减去的最大值的符号，将该符号附加到结果，减去其值，然后将其余部分转换为罗马数字。
 * 2. 如果该值以 4 或 9 开头，使用 减法形式，表示从以下符号中减去一个符号，
 * 例 4 是 5 (V) 减 1 (I): IV ，9 是 10 (X) 减 1 (I)：IX。仅使用以下减法形式：4
 * (IV)，9 (IX)，40 (XL)，90 (XC)，400 (CD) 和 900 (CM)。
 * 3. 只有 10 的次方（I, X, C, M）最多可以连续附加 3 次以代表 10
 * 的倍数。你不能多次附加 5 (V)，50 (L) 或 500
 * (D)。如果需要将符号附加4次，请使用 减法形式
 * 。
 * 给定一个整数，将其转换为罗马数字。 1 <= num <= 3999
 * https://leetcode.cn/problems/integer-to-roman/description/
 */
class Solution {
   public:
    /**
     * 法1：自己实现
     * 代码较复杂
     */
    string intToRoman(int num) {
        unordered_map<int, string> map = {{1, "I"},   {5, "V"},   {10, "X"},
                                          {50, "L"},  {100, "C"}, {500, "D"},
                                          {1000, "M"}};
        string ans;
        int divider = 1000;
        // 从1000开始试除
        // 找到最高位 比如千位数 还是 1000，百位数 就是100
        while (num / divider == 0) {
            divider /= 10;
        }
        // 从高到低逐层除下去
        // 比如 1994 依次拿到 1000 900 90 4
        while (divider > 0 && num / divider > 0) {
            int quot = num / divider;
            cout << num << " " << quot * divider << endl;
            // 当前位数字
            if (quot != 4 && quot != 9) {  // 不是4不是9
                if (quot >= 5) {           // 大于5的 要从5开始加 7=5+2
                    ans += map[5 * divider];  // 当前位*所在位数 7 * 100
                    // 拼接剩下的
                    for (int i = 0; i < quot - 5; i++) {
                        ans += map[divider];
                    }
                } else {
                    // 小于5的 直接拼接当前位数
                    for (int i = 0; i < quot; i++) {
                        ans += map[divider];
                    }
                }
            } else {
                // 等于 4 或 9 的
                // 拼接 4=IV 然后拼接 4+1的如：40+10、900+100
                ans += map[divider];
                ans += map[quot * divider + divider];
            }
            // 得到下一位
            num -= quot * divider;
            // 中间有可能是 0，一直除直到那一位
            while (divider > 0 && num / divider == 0) {
                divider /= 10;
            }
        }
        return ans;
    }

    /**
     * 法2：模拟简洁版本
     * 寻找不超过 num 的最大值符号，num 减去该符号值，继续寻找，直到为0
     */
    string intToRoman2(int num) {
        vector<pair<int, string>> array = {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
            {90, "XC"},  {50, "L"},   {40, "XL"}, {10, "X"},   {9, "IX"},
            {5, "V"},    {4, "IV"},   {1, "I"}};
        string ans;
        for (auto& [k, v] : array) {
            while (num >= k) {
                num -= k;
                ans += v;
                cout << num << " " << ans << endl;
            }
            if (num == 0) break;
        }
        return ans;
    }

    /**
     * 法3：硬编码数字
     * 分为 千位 百位 十位 个位
     * 依次拼接
     */
    string intToRoman3(int num) {
        // 千位4种可能 空，1000，2000，3000
        const string thousands[] = {"", "M", "MM", "MMM"};
        // 百位 空，100~900
        const string hundreds[] = {"",  "C",  "CC",  "CCC",  "CD",
                                   "D", "DC", "DCC", "DCCC", "CM"};
        // 十位 空，10~90
        const string tens[] = {"",  "X",  "XX",  "XXX",  "XL",
                               "L", "LX", "LXX", "LXXX", "XC"};
        // 个位 空，1~9
        const string ones[] = {"",  "I",  "II",  "III",  "IV",
                               "V", "VI", "VII", "VIII", "IX"};
        // 千位：num / 1000
        // 百位：num % 1000 / 100
        // 十位：num % 100 / 10
        // 个位: num % 10
        return thousands[num / 1000] + hundreds[num % 1000 / 100] +
               tens[num % 100 / 10] + ones[num % 10];
    }
};

int main() {
    Solution* solution = new Solution();
    vector<int> arr = {3749, 58, 1994, 666, 321, 101};
    for (auto i : arr) {
        cout << i << ":";
        auto ans = solution->intToRoman3(i);
        cout << ans << endl;
    }
    return 0;
}