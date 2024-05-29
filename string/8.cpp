#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
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
 * 8: 字符串转换整数(atoi)
 *
 * 请你来实现一个 myAtoi(string s) 函数，使其能将字符串转换成一个 32
 * 位有符号整数。
 * 函数 myAtoi(string s) 的算法如下：
 * 空格：读入字符串并丢弃无用的前导空格（" "）
 * 符号：检查下一个字符（假设还未到字符末尾）为 '-'
 * 还是'+'。如果两者都不存在，则假定结果为正。
 * 转换：通过跳过前置零来读取该整数，直到遇到非数字字符或到达字符串的结尾。如果没有读取数字，则结果为0。
 * 舍入：如果整数数超过 32 位有符号整数范围 [−2^31,  2^31 −
 * 1]，需要截断这个整数，使其保持在这个范围内。具体来说，小于 −2^31
 * 的整数应该被舍入为 −2^31 ，大于 2^31 − 1 的整数应该被舍入为 2^31 − 1 。
 * 返回整数作为最终结果。
 * https://leetcode.cn/problems/zigzag-conversion/description/
 */

/**
 * 法2：自动状态机
 * 	         ' '	+/-	    number	    other
 * start	 start	signed	in_number	end
 * signed	 end	end	    in_number	end
 * in_number end	end	    in_number	end
 * end	     end	end	    end	        end
 */
class Automaton {
   private:
    string state = "start";
    unordered_map<string, vector<string>> table = {
        {"start", {"start", "signed", "in_number", "end"}},
        {"signed", {"end", "end", "in_number", "end"}},
        {"in_number", {"end", "end", "in_number", "end"}},
        {"end", {"end", "end", "end", "end"}}};

    int get_col(char c) {
        if (isspace(c)) return 0;
        if (c == '+' or c == '-') return 1;
        if (isdigit(c)) return 2;
        return 3;
    }

   public:
    int sign = 1;
    long long ans = 0;

    void get(char c) {
        state = table[state][get_col(c)];
        if (state == "in_number") {
            ans = ans * 10 + c - '0';
            ans = sign == 1 ? min(ans, (long long)INT_MAX)
                            : min(ans, -(long long)INT_MIN);
        } else if (state == "signed")
            sign = c == '+' ? 1 : -1;
    }
};

class Solution {
   public:
    int myAtoi(string s) {
        int count = s.length();
        int sign = 1;
        int ans = 0;

        int i = 0;
        while (s[i] == ' ' && i < count) i++;
        if (s[i] == '-') {
            sign = -1;
            i++;
        } else if (s[i] == '+') {
            sign = 1;
            i++;
        } else if (!(s[i] >= '0' && s[i] <= '9')) {
            return ans;
        }
        while (i < count && s[i] >= '0' && s[i] <= '9') {
            int digit = s[i] - '0';
            // 判断是否溢出
            // 最简单的判断溢出，用long 来表示
            if (ans > (INT_MAX - digit) / 10) {
                return sign == 1 ? INT_MAX : INT_MIN;
            }
            ans = ans * 10 + digit;
            i++;
        }
        ans *= sign;
        return ans;
    }
    int myAtoi2(string s) {
        Automaton automaton;
        for (char c : s) automaton.get(c);
        return automaton.sign * automaton.ans;
    }
};

int main() {
    Solution* solution = new Solution();
    cout << INT_MAX << endl;
    cout << INT_MIN << endl;
    cout << endl;
    vector<string> arr = {"42",         "-31",          " -042",
                          "1337c0d3",   "0-1",          "words and 987",
                          "2147483649", "-91283472332", "-2147483650"};
    for (int i = 0; i < arr.size(); i++) {
        int ans = solution->myAtoi2(arr[i]);
        cout << ans << endl;
    }
    return 0;
}