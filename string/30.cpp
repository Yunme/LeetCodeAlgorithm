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
 * 30: 串联所有单词的子串
 * 给定一个字符串 s 和一个字符串数组 words。 words 中所有字符串 长度相同。
 * s 中的 串联子串 是指一个包含 words 中所有字符串以任意顺序排列连接起来的子串。
 *
 * 返回所有串联子串在 s 中的开始索引。你可以以 任意顺序 返回答案。
 *
 * 就是以任意顺序串联 words 里的字符串，是 s 的子串。找出其在 s
 * 中的index。可能有多个。
 * https://leetcode.cn/problems/substring-with-concatenation-of-all-words/description/
 */

class Solution {
   public:
    /**
     * 自己实现：思路基本对，窗口滑动每次只滑了一位，复杂度较高。
     * 滑动窗口 + map
     * 因为 words 数组中字符串长度相等，根据 words 数组中元素的长度和 数组的大小
     * 可知滑动窗口长度为 words.size() * words[i].length、
     * 不太行
     */
    vector<int> findSubstring(string s, vector<string>& words) {
        if (words.empty()) {
            return {};
        }
        vector<int> result;
        int size = words.size();
        int wordLength = words[0].length();
        int length = s.length();
        // words 数组可能有重复的
        // 存储到 map 中，key 为 word，value 为 word出现的个数。
        unordered_map<string, int> map;
        for (string& s : words) {
            map[s]++;
        }
        for (auto& [k, v] : map) {
            cout << k << ":" << v << endl;
        }
        // slow 慢指针，滑动窗口左侧；
        // fast 快指针，滑动窗口右侧。
        // 窗口左必右开
        int slow = 0, fast = slow + size * wordLength;
        while (fast <= length && slow <= length) {
            unordered_map<string, int> temp = map;
            // 每 wordLength个遍历窗口里的子串
            for (int i = slow; i < fast; i += wordLength) {
                string sub = s.substr(i, wordLength);
                bool find = temp.count(sub) > 0;
                // 没找到，直接跳出当前窗口，
                if (!find) {
                    break;
                } else {
                    // 找到了 移除临时map中的
                    if (temp[sub] > 1) {
                        temp[sub]--;
                    } else {
                        temp.erase(sub);
                    }
                }
            }
            // 一个窗口遍历结束，
            // 如果temp map
            // 中的元素被消耗光了，说明在滑动窗口中找到了一样的子串。
            if (temp.empty()) {
                result.push_back(fast - size * wordLength);
            }
            // 下一个滑动窗口
            // 每次只滑动一个字符，复杂度高，没有复用已划过去的。
            slow += 1;
            fast = slow + size * wordLength;
        }
        return result;
    }

    /**
     * 滑动窗口（官方解法），
     * 检测窗口中 子串个数和 words 数组中子串个数，差值相对比
     */
    vector<int> findSubstring2(string s, vector<string>& words) {
        if (words.empty()) {
            return {};
        }
        vector<int> result;
        int wordCount = words.size();
        int wordLength = words[0].length();
        int strLength = s.length();
        int windowLength = wordLength * wordCount;
        // 窗口从 0 开始每次滑动 wordLength 个。下次循环从1开始滑动，等等。
        // 只需循环 wordLength 次，所有 wordLength 大小的子串就都遍历到了。
        for (int i = 0; i < wordLength && i + windowLength <= strLength; i++) {
            // 记录的是每个窗口中，出现的子串数与words中子串数的差值。
            unordered_map<string, int> differ;
            for (int j = 0; j < wordCount; j++) {
                // 每隔单词的长度个截取字符串，记录子串的个数
                differ[s.substr(i + j * wordLength, wordLength)]++;
            }
            // words 中字符串在 differ 中，个数减1；
            for (string& s : words) {
                // 如果个数为0，说明该子串同时存在窗口和 words 中，移除。
                if (--differ[s] == 0) {
                    differ.erase(s);
                }
            }
            // 当前窗口是否匹配？
            if (differ.empty()) {
                result.push_back(i);
            }
            // 窗口开始向右滑动；每次滑动 wordLength 个，直到滑动到最后
            for (int start = i + wordLength;
                 start < strLength - windowLength + 1; start += wordLength) {
                // 右侧滑进来的 个数加1
                string sub =
                    s.substr(start + (wordCount - 1) * wordLength, wordLength);
                if (++differ[sub] == 0) differ.erase(sub);
                // 左侧滑出去的 个数减1
                sub = s.substr(start - wordLength, wordLength);
                if (--differ[sub] == 0) differ.erase(sub);

                // 每滑动一次
                // 就判断一次，是否为空，
                // 为空就说明窗口里的和words里的子串个数相等
                // 相匹配
                if (differ.empty()) {
                    result.push_back(start);
                }
            }
        }
        return result;
    }

    /**
     * 滑动窗口
     * 窗口中，子串个数和words 中子串个数是否一致。
     * 用 map 存储，子串和其个数，查看窗口中的和 words 中的是否一致。
     */
    vector<int> findSubstring3(string s, vector<string>& words) {
        if (words.empty()) {
            return {};
        }
        unordered_map<string, int> map;
        for (string& s : words) {
            map[s]++;
        }

        vector<int> result;
        int wordCount = words.size();
        int wordLength = words[0].length();
        int strLength = s.length();
        int windowLength = wordLength * wordCount;
        // 只需循环 wordLength 个。每次从0，1， 2 ，3 ... wordLength -1 开始滑动
        for (int i = 0; i < wordLength && i + windowLength <= strLength; i++) {
            // 每个窗口中的子串和其个数
            for (int j = i; j <= strLength - windowLength; j += wordLength) {
                unordered_map<string, int> tempMap;
                for (int k = j; k < j + windowLength; k += wordLength) {
                    string sub = s.substr(k, wordLength);
                    tempMap[sub]++;
                }
                if (map == tempMap) {
                    result.push_back(j);
                }
            }
        }
        return result;
    }
};

int main() {
    Solution* solution = new Solution();
    vector<string> arr = {"barfoothefoobarman", "wordgoodgoodgoodbestword",
                          "barfoofoobarthefoobarman",
                          "wordgoodgoodgoodbestword",
                          "lingmindraboofooowingdingbarrwingmonkeypoundcake"};
    vector<vector<string>> substr = {{"foo", "bar"},
                                     {"word", "good", "best", "word"},
                                     {"bar", "foo", "the"},
                                     {"word", "good", "best", "good"},
                                     {"fooo", "barr", "wing", "ding", "wing"}};
    for (int i = 0; i < arr.size(); i++) {
        vector<int> result = solution->findSubstring3(arr[i], substr[i]);
        for (int k : result) {
            cout << k << ",";
        }
        cout << endl;
    }
    return 0;
}