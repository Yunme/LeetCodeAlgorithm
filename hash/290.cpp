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
#include <sstream>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 290：单词规律
 *
 * 给定一种规律 pattern 和一个字符串 s ，判断 s 是否遵循相同的规律。
 *
 * 这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 s
 * 中的每个非空单词之间存在着双向连接的对应规律。
 *
 * https://leetcode.cn/problems/word-pattern/description/
 *
 * s 只包含小写英文字母和 ' '
 * s 不包含 任何前导或尾随对空格
 * s 中每个单词都被 单个空格 分隔
 */

class Solution {
   public:
    /**
     * 哈希表法
     */
    bool wordPattern(string pattern, string s) {
        unordered_map<char, string> map1;
        unordered_map<string, char> map2;
        stringstream ss(s);
        string word;
        int n = pattern.length();
        int i = 0;
        while (getline(ss, word, ' ')) {
            if (i >= n) return false;
            char c = pattern[i];
            if (map1.find(c) != map1.end() && map1[c] != word) {
                return false;
            }
            if (map2.find(word) != map2.end() && map2[word] != c) {
                return false;
            }
            map1[c] = word;
            map2[word] = c;
            i++;
        }
        if (i != n) return false;
        return true;
    }
};

int main() {
    Solution *s = new Solution();
    vector<string> patterns = {"abba", "abba", "aaaa"};
    vector<string> ss = {"dog cat cat dog", "dog cat cat fish",
                         "dog cat cat dog"};

    for (int i = 0; i < ss.size(); i++) {
        auto ans = s->wordPattern(patterns[i], ss[i]);
        cout << ans << endl;
    }
}