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
 * hj2 计算某字符出现次数
 * 不区分大小写
 * https://www.nowcoder.com/practice/a35ce98431874e3a820dbe4b2d0508b1
 */
class Solution {
   public:
    /**
     * @param s 输入字符串
     * @param c 查找的字符
     * @return 返回 c 在 s 中出现的次数 不区分大小写
     * 系统函数 tolower()
     */
    int countCharIgnoreCase(string s, char c) {
        int len = s.length();
        int count = 0;
        for (int i = 0; i < len; i++) {
            bool equal = isEqualIgnoreCase(s[i], c);
            // equal = tolower(s[i]) == tolower(c);
            // equal = toupper(s[i]) == toupper(c);
            if (equal) {
                count++;
            }
        }
        return count;
    }

    /**
     * 判断两个字符是否相等 忽略其大小写
     */
    bool isEqualIgnoreCase(char c1, char c2) {
        // 全部转为大写 比较
        if (c1 >= 'a' && c1 <= 'z') {
            // 小写
            c1 = 'A' + c1 - 'a';
        }
        if (c2 >= 'a' && c2 <= 'z') {
            // 小写
            c2 = 'A' + c2 - 'a';
        }
        return c1 == c2;
    }
};

int main() {
    Solution* s = new Solution();
    string a("a ");
    a = "   fly me   to   the moon  ";
    a = "luffy is still joyboy";
    a = "8 8 8  8A i i OOI              IIIaa";
    int len = s->countCharIgnoreCase(a, 'a');
    cout << len << endl;

    while (true) {
        char b;
        // cin 碰到空格 会隔断字符串
        getline(cin, a);
        b = getchar();
        cout << s->countCharIgnoreCase(a, b) << endl;
    }
}