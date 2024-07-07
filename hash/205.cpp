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
 * 205: 同构字符串
 *
 * 给定两个字符串 s 和 t ，判断它们是否是同构的。
 * 如果 s 中的字符可以按某种映射关系替换得到 t ，那么这两个字符串是同构的。
 * 每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序。不同字符不能映射到同一个字符上，
 * 相同字符只能映射到同一个字符上，字符可以映射到自己本身。
 * https://leetcode.cn/problems/isomorphic-strings/description/
 */

class Solution {
   public:
    /**
     * 哈希表法
     */
    bool isIsomorphic(string s, string t) {
        int m = s.length();
        if (m != t.length()) return false;
        // 存储映射 s -> t
        unordered_map<char, char> sMap;
        // 存储映射 t -> s
        unordered_map<char, char> tMap;
        for (int i = 0; i < m; i++) {
            char sc = s[i], tc = t[i];
            // 存在但不相等 返回false
            if (sMap.find(sc) != sMap.end() && sMap[sc] != tc) return false;
            if (tMap.find(tc) != tMap.end() && tMap[tc] != sc) return false;

            sMap[sc] = tc;
            tMap[tc] = sc;
        }
        return true;
    }
};

int main() {
    Solution *s = new Solution();
    vector<string> ss = {"egg", "foo", "paper", "badc"};
    vector<string> ts = {"add", "bar", "title", "baba"};

    for (int i = 0; i < ss.size(); i++) {
        auto ans = s->isIsomorphic(ss[i], ts[i]);
        cout << ans << endl;
    }
}