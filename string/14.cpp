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
 * 14:最长公共前缀
 * 编写一个函数来查找字符串数组中的最长公共前缀。
 * 如果不存在公共前缀，返回空字符串 ""。
 * https://leetcode.cn/problems/longest-common-prefix/description
 */

class Solution {
   public:
    /**
     * 最长公共前缀（自己实现）
     */
    string longestCommonPrefix(vector<string>& strs) {
        // 为空 返回空
        if (strs.empty()) return "";
        // 以第一个为基准判断
        string s = strs[0];
        // 循环第一个字符串
        for (int i = 0; i < s.size(); i++) {
            // 数组中第2个元素开始循环判断
            for (int j = 1; j < strs.size(); j++) {
                if (i == strs[j].length())  //  到达最后一位 直接返回这个字符串
                    return strs[j];
                else if (s[i] != strs[j][i])  // 当前位不同直接返回
                    return s.substr(0, i);
            }
            // 如果最后到达 s 的最后一位还没返回，说明 整个是。
            if (i == s.size() - 1) return s;
        }
        return "";
    }
};

int main() {
    Solution* solution = new Solution();
    vector<vector<string>> arr = {
        {"flower", "flow", "flight"},
        {"abcabcbb", "bbbbb", "pwwkew", "dvdf", "nfpdmpi"},
        {"zzabc", "zza", "zzacca"}};
    for (auto& s : arr) {
        auto len = solution->longestCommonPrefix(s);
        cout << len << endl;
    }
    return 0;
}