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
 * 3: 字母异位词分组
 * 给你一个字符串数组，请你将 字母异位词组合在一起。可以按任意顺序返回结果列表。
 * 字母异位词 是由重新排列源单词的所有字母得到的一个新单词。
 * https://leetcode.cn/problems/group-anagrams/description/
 */

class Solution {
   public:
   /**
    * 对每个字符串按照字典排序后，异位词一样的，排序后就相等。
    * 把异位词相等的在源数组中的 index 按照key value 存起来，
    * 分别打印。
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
};

int main() {
    Solution* solution = new Solution();
    // vector<string> arr = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<string> arr = {"a"};

    vector<vector<string>> result = solution->groupAnagrams(arr);
    for (vector<string>& a : result) {
        for (string& b : a) {
            cout << b << " ";
        }
        cout << endl;
    }
    return 0;
}