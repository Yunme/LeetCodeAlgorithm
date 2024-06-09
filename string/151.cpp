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
 * 151: 反转字符串中的单词
 * 给你一个字符串 s ，请你反转字符串中 单词 的顺序。
 * 单词是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词
 * 分隔开。 返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。
 *
 * 注意：输入字符串 s 中可能会存在前导空格、尾随空格或者单词间的多个空格。
 * 返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。
 *
 * https://leetcode.cn/problems/reverse-words-in-a-string/description/
 */

class Solution {
   public:
    /**
     * 法1：逆序循环判断 拼接 （自己实现）
     * 逆向根据字符串中的空格分割，将单词输出
     * 双指针
     */
    string reverseWords(string s) {
        int n = s.length();
        // 慢指针
        int start = n - 1;
        string ans;

        // i 快指针
        for (int i = n - 1; i >= 0; i--) {
            // 如果是空格，则分割子串
            if (i < n - 1 && s[i] == ' ') {
                // 不是第一个后面的单词前拼接空格
                if (!ans.empty()) ans += ' ';
                // i 处是空格，下一个是单词开始
                ans += s.substr(i + 1, start - i);
            }
            // 找到下一个不为空格的 作为开始
            while (i >= 0 && s[i] == ' ') {
                i--;
                start = i;
            }
        }
        // 最后一个，如果 start 大于等于0 说明 还有单词
        if (start >= 0) {
            if (!ans.empty()) ans += ' ';
            ans += s.substr(0, start + 1);
        }
        return ans;
    }
    /**
     * 法2：使用库函数
     */
    string reverseWords2(string s) {
        int n = s.length();
        stringstream ss(s);
        string ans, word;
        // ss 直接取出空格
        while (ss >> word) {
            if (ans.empty()) {
                // 首次不拼接空格
                ans = word;
            } else {
                ans = word + ' ' + ans;
            }
        }
        return ans;
    }

    /**
     * C++ string 可变，原地修改 O(1) 空间
     * 去除首尾空格，reverse 整个字符串
     * 再 reverse 每个单独单词
     * 拼接
     */
    string reverseWords3(string s) {
        reverse(s.begin(), s.end());
        int n = s.size();
        int index = 0;
        for (int start = 0; start < n; start++) {
            if (s[start] != ' ') {
                // 填充一个空格
                // 后移index 到下一个单词的开头
                if (index != 0) s[index++] = ' ';
                int end = start;
                while (end < n && s[end] != ' ') s[index++] = s[end++];
                // 翻转一整个单词
                reverse(s.begin() + index - (end - start), s.begin() + index);
                // 更新start 找下一个单词
                start = end;
            }
        }
        // 擦除尾部空格
        s.erase(s.begin() + index, s.end());
        return s;
    }
};

int main() {
    Solution* solution = new Solution();
    vector<string> arr = {"the sky is blue", "  hello world ",
                          "a good  example "};
    for (auto& s : arr) {
        auto len = solution->reverseWords3(s);
        cout << len << endl;
    }
    return 0;
}