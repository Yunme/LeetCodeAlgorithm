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
 * 58: 最后一个单词的长度
 * 单词前后用若干空格字符隔开
 * https://leetcode.cn/problems/length-of-last-word/description/
 */
class Solution {
   public:
    /**
     * 倒序 找到最后一个非空格字符减 下一个空格
     */
    int lengthOfLastWord(string s) {
        int sLength = s.length();
        // 记录最后一个非空格字符的index
        int lastCharNonBlank = -1;

        for (int i = sLength - 1; i >= 0; i--) {
            if (s[i] != ' ' && lastCharNonBlank < 0) {
                lastCharNonBlank = i;
            }
            // 跟下一个空格位置相减
            if (s[i] == ' ' && lastCharNonBlank >= 0) {
                return lastCharNonBlank - i;
            }
        }
        // 没有下一个空格，0..lastCharNonBlank 就是一个单词
        return lastCharNonBlank + 1;
    }

    /**
     * 简洁版
     * 倒序循环
     * 当 s[i] 不为空时 计数，不为空时
     * 如果 计数大于0 那么length >0 length 就是最后一个单词长度。
     */
    int lengthOfLastWord2(string s) {
        int length = 0;
        int i = s.length() - 1;
        while (i >= 0) {
            if (s[i] != ' ') {
                length++;
            } else if (length > 0) {
                return length;
            }
            i--;
        }
        return length;
    }
};

int main() {
    Solution* s = new Solution();
    string a("a ");
    a = "   fly me   to   the moon  ";
    a = "luffy is still joyboy";
    a = "Hello";
    int len = s->lengthOfLastWord2(a);
    cout << len << endl;

    while (getline(cin, a)) {
        cout << a << endl;
        cout << s->lengthOfLastWord2(a) << endl;
    }
}