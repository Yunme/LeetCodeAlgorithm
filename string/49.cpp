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
 * 49: 字母异位词分组
 * 给你一个字符串数组，请你将 字母异位词组合在一起。可以按任意顺序返回结果列表。
 * 字母异位词 是由重新排列源单词的所有字母得到的一个新单词。
 *
 * 字符集：只包含小写字母
 * https://leetcode.cn/problems/group-anagrams/description/
 */

class Solution {
   public:
    /**
     * 法1：对每个字符串按照字典排序后，异位词一样的，排序后就相等。
     * 把异位词相等的在源数组中的 index 按照key value 存起来，
     * 分别打印。
     *
     * - 时间复杂度 O(nkLogK) n 是 strs 里字符串数量，k 是 strs
     * 里字符串的最大长度。 遍历数组 n，每个字符串排序 kLog(k)
     * - 空间 O(nk)
     */
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<int>> sorted(strs.size());
        for (int i = 0; i < strs.size(); i++) {
            string s = strs[i];
            sort(s.begin(), s.end());
            sorted[s].push_back(i);
        }

        vector<vector<string>> result;
        for (auto& [k, v] : sorted) {
            vector<string> arr2;
            for (int i : v) {
                arr2.push_back(strs[i]);
            }
            result.push_back(arr2);
        }
        return result;
    }

    /**
     * 法2：计数法：由于字符集只是小写字母，两个字符串互为异位词必然各个字符出现次数相同
     * 相对于法1：排序过程变快，变成了 O(m) m 是字符集大小即 26.
     * 时间：O(n(k+m)) k 是最长的字符串的长度
     * 空间: O(n(k+m))
     */
    vector<vector<string>> groupAnagrams2(vector<string>& strs) {
        unordered_map<string, vector<string>> map;
        for (int i = 0; i < strs.size(); i++) {
            // 26个小写字母个数
            vector<int> digits(26);
            for (char c : strs[i]) {
                digits[c - 'a']++;
            }

            // 把每个字母及其个数拼接成 key 存储
            // 作为异位词的唯一表示形式
            // 与法1中排序后词 相同含义
            string key;
            for (int j = 0; j < digits.size(); j++) {
                if (digits[j] > 0) {
                    key += to_string('a' + j) + to_string(digits[j]);
                }
            }
            // 字母个数相同的分到一组存储。
            map[key].push_back(strs[i]);
        }
        // 输出
        vector<vector<string>> ans;
        for (auto& [k, v] : map) {
            ans.push_back(v);
        }
        return ans;
    }
};

int main() {
    Solution* solution = new Solution();
    vector<string> arr = {"eat", "tea", "tan", "ate", "nat", "bat"};
    // vector<string> arr = {"a"};

    vector<vector<string>> result = solution->groupAnagrams2(arr);
    for (vector<string>& a : result) {
        for (string& b : a) {
            cout << b << " ";
        }
        cout << endl;
    }
    return 0;
}