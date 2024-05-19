#include <math.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 392: 判断子序列
 * 给定字符串 s 和 t ，判断 s 是否为 t 的子序列。
 * 字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。
 * （例如，"ace"是"abcde"的一个子序列，而"aec"不是）。
 * https://leetcode.cn/problems/is-subsequence/description/
 */

class Solution {
   public:
    /**
     * 注意子串在主串中可以不是连续的。
     * @param s 子序列
     * @param t 主串
     */
    bool isSubsequence(string s, string t) {
        int i = 0, j = 0;
        while (i < t.length() && j < s.length()) {
            if (t[i] == s[j]) {
                j++;
            }
            i++;
        }
        if (j == s.length()) {
            return true;
        }
        return false;
    }
};

int main() {
    Solution *s = new Solution();
    string sub = "abc";
    string main = "ahbgdc";

    bool ans = s->isSubsequence(sub, main);
    cout << ans << endl;
}