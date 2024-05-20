#include <math.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
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
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

/**
 * https://blog.csdn.net/weixin_48157259/article/details/138087531
 *
 * 16：变换最小字符串
 * 给定一个字符串s，最多只能进行一次变换，返回变换后能得到的最小字符串（按照字典序进行比较）
 *  变换规则： 交换字符串中任意两个不同位置的字符。
 * https://blog.csdn.net/weixin_48157259/article/details/138228501
 *
 * 输入:
 * 一串小写字母组成的字符串s
 * 输出：
 * 按照要求进行变换得到的最小字符串
 */

/**
 * 法1：自己实现
 * 从第2个开始向后找最小的，找到最后。
 * a. 如果 小于第1个则与第一个交换。
 * b. 如果 大于等于第1个，则与下一个第2个相比 重走a；
 * 一直重复
 */
string transform(string &str) {
    int j = 0;
    // 从第一个开始 作为判断基准
    while (j < str.length()) {
        char a = str[j];
        char minC = 'z';
        int minPos = -1;
        // 找尽可能靠后的最小的元素
        for (size_t i = j + 1; i < str.size(); i++) {
            char c = str[i];
            if (c <= minC) {
                minC = c;
                minPos = i;
            }
        }
        // 最小的元素 小于基准，直接交换后跳出
        if (minC < a) {
            swap(str[j], str[minPos]);
            break;
        } else {
            // 最小的元素 >= 基准，基准后移一位。
            j++;
        }
    }
    return str;
}

/**
 * 法2：贪心法
 * 思路跟法1，基本一致。用栈实现。
 */
string transform2(string &str) {
    stack<int> stack;

    // 逆序遍历字符串
    // 如果当前元素小于栈顶元素，则将其下标入栈。
    // 栈中 索引对应元素 从栈顶到栈底递增，即栈顶index 所在元素最小
    for (int i = str.length() - 1; i >= 0; i--) {
        char c = str[i];
        if (stack.empty() || str[stack.top()] > c) {
            stack.push(i);
        }
    }

    for (int i = 0; i < str.length(); i++) {
        // 如果为空 说明，字符串逆序是递减的。已是最小
        if (stack.empty()) break;

        // 当前元素，在栈顶索引的左边。
        // 如果大的话 需要交换
        if (i < stack.top()) {
            if (str[i] > str[stack.top()]) {
                swap(str[i], str[stack.top()]);
                break;
            }
        } else {
            // 如果当前索引 大于栈顶元素索引，
            // 因为栈是从栈顶到栈底，递增的，栈顶是最小的索引，说明左边的都比栈顶的小。
            stack.pop();
        }
    }
    return str;
}

int main() {
    string input;
    cin >> input;

    string ans = transform2(input);
    cout << ans << endl;
}

/**
 * 法3：暴力法
*/
int main2() {
    std::string s;
    std::cin >> s;
    std::string ans = s;
    int n = s.length();

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // 令下标对(i, j)对应的两个字符进行交换
            std::swap(s[i], s[j]);
            // 把交换后得到的字符串和ans进行比较，更新ans
            ans = std::min(s, ans);
            // 判断完毕后，下标对(i, j)对应的两个字符重新交换回去
            std::swap(s[i], s[j]);
        }
    }

    std::cout << ans << std::endl;

    return 0;
}