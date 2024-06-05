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
 * 125: 验证回文串
 * 如果在将所有大写字符转换为小写字符、并移除所有非字母数字字符之后，短语正着读和反着读都一样。
 * 则可以认为该短语是一个回文串 。 字母和数字都属于字母数字字符。
 * https://leetcode.cn/problems/valid-palindrome/description/
 */

class Solution {
   public:
    /**
     * 简单字符串操作
     */
    bool isPalindrome(string s) {
        int n = s.length();
        // 先移除 非字母数字
        for (int i = n - 1; i >= 0; i--) {
            char c = s[i];
            // if (!isdigit(c) && !isalpha(c)) {
            if (!isalnum(c)) {
                s.erase(i, 1);
            } else if (isupper(c)) {
                s[i] = tolower(c);
            }
        }
        cout << s << endl;
        // 双指针验证回文
        int i = 0, j = s.length() - 1;
        while (i < j) {
            if (s[i] != s[j]) {
                return false;
            }
            i++;
            j--;
        }
        return true;
    }

    /**
     * 直接验证，跳过非字母数字
     */
    bool isPalindrome2(string s) {
        int n = s.length();
        // 双指针验证回文
        int i = 0, j = s.length() - 1;
        while (i < j) {
            if (!isalnum(s[i])) {
                i++;
            } else if (!isalnum(s[j])) {
                j--;
            } else if (tolower(s[i]) != tolower(s[j])) {
                return false;
            } else {
                i++;
                j--;
            }
        }
        return true;
    }
};

int main() {
    Solution* solution = new Solution();
    vector<string> arr = {"A man, a plan, a canal: Panama", "race a car", " "};
    for (string& s : arr) {
        bool ans = solution->isPalindrome2(s);
        cout << (ans ? "true" : "false") << endl;
    }
    return 0;
}