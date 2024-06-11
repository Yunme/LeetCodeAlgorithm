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
 * 76: 最小覆盖子串
 * 给你一个字符串 s 、一个字符串 t 。
 * 返回 s 中涵盖 t 所有字符的最小子串。
 * 如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
 *
 * 注意：
 * 对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
 * 如果 s 中存在这样的子串，我们保证它是唯一的答案。
 *
 * https://leetcode.cn/problems/minimum-window-substring/description/
 */

/**
 * 滑动窗口
 */
class Solution {
   public:
    /**
     * 滑动窗口，哈希表
     * 窗口右边指针 end 延伸，左边 start 收缩。
     * 当窗口全部包含 t 的全部时，收缩 start 到最小
     *
     * 累加的思维：每一个字符个数满足，计数+1，直到计数等于 map 的 size
     *
     * 使用两个 map 存储
     */
    string minWindow(string s, string t) {
        int n = s.length();
        int m = t.length();
        // t 里的字符个数
        unordered_map<char, int> map;
        for (char c : t) {
            map[c]++;
        }
        string ans;
        int start = 0, end = 0;
        int minLen = INT_MAX, minStart = 0;
        // 窗口里的 在 t 里的字符个数
        unordered_map<char, int> window;
        int matchedCount = 0;
        while (end < n) {
            char c = s[end];
            // 窗口内的字符计数
            if (map.count(c) > 0) {
                window[c]++;
                if (map[c] == window[c]) matchedCount++;
            }
            // 窗口内的字符已经包含了 t 中所有的，收缩 start
            while (matchedCount == map.size()) {
                // 更新最小值
                if (end - start + 1 < minLen) {
                    minLen = end - start + 1;
                    // 只记录每次的最短长度和 起始位置
                    // ans 最后再更新
                    // ans = s.substr(start, minLen);
                    minStart = start;
                }
                c = s[start];
                // 如果 c 是 t 里的字符
                if (map.count(c) > 0) {
                    // window 里个数减1
                    window[c]--;
                    if (window[c] < map[c]) {  // 个数少了，匹配个数减1
                        matchedCount--;
                    }
                }
                start++;
            }
            end++;
        }
        return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
    }

    /**
     * 优化为 一个 map 存储
     * 减法思想
     */
    string minWindow2(string s, string t) {
        int n = s.length();
        // 窗口内部覆盖 t 还需要的各个字符的个数
        unordered_map<char, int> map;
        for (char c : t) {
            map[c]++;
        }
        int start = 0, end = 0;
        // 窗口中还需要多少个 t 里的字符
        int windowRemainCount = t.length();
        int minLen = INT_MAX;
        int minStart = 0;
        while (end < n) {
            char c = s[end];
            if (map[c] > 0) {
                windowRemainCount--;  // 满足一个 剩余个数减 1
            }
            map[c]--;
            // == 0 表示 window 中已包含所有 t 中字符
            while (windowRemainCount == 0) {
                // 更新最短长度
                if (end - start + 1 < minLen) {
                    minLen = end - start + 1;
                    minStart = start;
                }
                // 左侧开始收缩
                c = s[start];
                if (map[c] == 0) {
                    windowRemainCount++;
                }
                map[c]++;
                start++;
            }
            end++;
        }
        return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
    }
};

int main() {
    Solution* solution = new Solution();
    vector<string> arr = {"ADOBECODEBANC", "a", "a"};
    vector<string> arrT = {"ABC", "a", "aa"};
    for (int i = 0; i < arr.size(); i++) {
        auto ans = solution->minWindow2(arr[i], arrT[i]);
        cout << ans << endl;
    }
    return 0;
}