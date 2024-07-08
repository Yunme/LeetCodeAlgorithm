#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 541：反转字符串 II
 *
 * 给定一个字符串 s 和一个整数 k，从字符串开头算起，每计数至 2k 个字符，就反转这
 * 2k 字符中的前 k 个字符。 如果剩余字符少于 k 个，则将剩余字符全部反转。
 * 如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。
 *
 * https://leetcode.cn/problems/reverse-string-ii/description/
 */

class Solution {
   public:
    /**
     * 反转字符串局部 [start, end]
     */
    void reverseRegion(string& s, int start, int end) {
        while (start < end) {
            int temp = s[start];
            s[start] = s[end];
            s[end] = temp;
            start++;
            end--;
        }
    }
    /**
     * 双指针反转 O(n) O(1)
     */
    string reverseStr(string s, int k) {
        int n = s.length();
        int i = 0;
        // 前 2k 整数倍个元素
        for (; i < n - 2 * k + 1; i += 2 * k) {
            int start = i, end = i + k - 1;
            reverseRegion(s, start, end);
        }
        // 剩下的
        if (n - i >= k) {  // 大于等于 k
            reverseRegion(s, i, i + k - 1);
        } else {
            // 小于 k
            reverseRegion(s, i, n - 1);
        }
        return s;
    }
};

int main() {
    Solution* s = new Solution();
    vector<string> list = {"abcdefg", "abcd", "abcdefghij"};
    vector<int> ks = {2, 2, 3};

    for (int i = 0; i < list.size(); i++) {
        auto ans = s->reverseStr(list[i], ks[i]);
        cout << ans << endl;
    }
}