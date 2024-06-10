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
 * 383: 赎金信
 * 你两个字符串：ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine
 * 里面的字符构成。
 *
 * 如果可以，返回 true ；否则返回 false
 *
 * magazine 中的每个字符只能在 ransomNote 中使用一次。
 * https://leetcode.cn/problems/ransom-note/description
 */
class Solution {
   public:
    /**
     * 哈希表 存储 magazine 各个字符的个数
     * 遍历 ransomNote 中字符，如果在 map 中找到且个数大于1，map
     * 中个数减1，否则返回false
     */
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> map;
        for (auto c : magazine) {
            map[c]++;
        }
        int i = 0;
        for (; i < ransomNote.size(); i++) {
            char c = ransomNote[i];
            // map 中存在 且 个数大于1
            if (map.count(c) > 0 && map[c] > 0) {
                map[c]--;  // 个数减1
            } else
                // 不存在 或个数 小于1
                return false;
        }
        // 找到最后了
        return i == ransomNote.size();
    }
};

int main() {
    Solution *s = new Solution();
    vector<string> arr1 = {"a", "aa", "aa"};
    vector<string> arr2 = {"b", "ab", "aab"};
    for (int i = 0; i < arr1.size(); i++) {
        auto ans = s->canConstruct(arr1[i], arr2[i]);
        cout << (ans ? "true" : "false") << endl;
    }
}
