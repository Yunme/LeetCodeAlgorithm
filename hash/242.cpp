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
 * 242: 有效的字母异位词
 *
 * 给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。
 * 注意：若 s 和 t 中每个字符出现的次数都相同，则称 s 和 t 互为字母异位词。
 *
 * 进阶: 如果输入字符串包含 unicode
 * 字符怎么办？你能否调整你的解法来应对这种情况？
 * https://leetcode.cn/problems/valid-anagram/description/
 */

class Solution {
   public:
    /**
     * 法1： O(max(m, n))
     * 如果字符集是: 26个小写字母
     * 记录 s 的字母个数
     */
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;

        vector<int> sChar(26), tChar(26);
        for (int i = 0; i < s.length(); i++) {
            int index = s[i] - 'a';
            sChar[index]++;
        }
        for (int i = 0; i < t.length(); i++) {
            int index = t[i] - 'a';
            tChar[index]++;
        }
        // 判断字母个数是否相等
        for (int i = 0; i < 26; i++) {
            if (sChar[i] != tChar[i]) return false;
        }
        return true;
    }

    /**
     * 法2: O(nLogN)
     * 对字符串按字典序排序后判断是否相等
     */
    bool isAnagram2(string s, string t) {
        if (s.length() != t.length()) return false;
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }

    /**
     * 法3: 哈希表 O(max(m,n))
     * 取单个字符计数 一个增加计数，一个减少计数，
     * 最后遍历map 如果还有大于 0 的字符说明不是
     */
    bool isAnagram3(string s, string t) {
        if (s.length() != t.length()) return false;
        unordered_map<char, int> sMap;
        for (char c : s) {
            sMap[c]++;
        }
        for (char c : t) {
            sMap[c]--;
        }

        for (auto &[k, v] : sMap) {
            if (v > 0) return false;
        }
        return true;
    }
};

int main() {
    Solution *s = new Solution();
    vector<string> ss = {"anagram", "rat"};
    vector<string> ts = {"nagaram", "car"};

    for (int i = 0; i < ss.size(); i++) {
        auto ans = s->isAnagram3(ss[i], ts[i]);
        cout << ans << endl;
    }
}