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
 * 3: 无重复字符的最长子串
 * 给定一个字符串，求其无重复字符的最长子串。
 * https://leetcode.cn/problems/longest-substring-without-repeating-characters/description
 */

/**
 * 滑动窗口
 */
class Solution {
   public:
    /**
     * 法1：传统方法（自己实现的），思路基本对，但是实现可以更简洁，
     * 这里把前面不重复的字符加到map里，key 对应字符，value 对应index；
     * 在遍历时，未找到重复时，一直累加；
     * 找到重复的后，根据map 找到上一个重复的元素，删除map里前面的包括自己。
     */
    int lengthOfLongestSubstring(string str) {
        unordered_map<char, int> map;
        int maxLength = 0;
        for (int i = 0; i < str.length(); i++) {
            char c = str[i];
            // 已有，说明重复了
            if (map.find(c) != map.end()) {
                // 记录当前的大小
                int lastIndex = map[c];
                maxLength = max(maxLength, (int)i - lastIndex);
                // 移除已有的前面的，包含自己，计算下个不重复子串的长度
                auto m = map.begin();
                while (m != map.end()) {
                    if (m->second <= lastIndex) {
                        m = map.erase(m);
                    } else {
                        m++;
                    }
                }
                map[c] = i;
            } else {
                map[c] = i;
                maxLength = max(maxLength, (int)map.size());
            }
        }
        maxLength = max(maxLength, (int)map.size());
        return maxLength;
    }

    /**
     * 双指针，滑动窗口
     * 不重复的元素，存到set里
     * 快指针fast：从0开始找不同，加到set里。直到找到set里已有的；从slow
     *      开始移除重复前的元素，包括重复的元素
     * 慢指针slow：在原地，表示不重复子串的首个元素
     */
    int lengthOfLongestSubstring2(string str) {
        int slow = 0, fast = 0;
        unordered_set<char> set;
        int maxLength = 0;
        for (fast = 0; fast < str.length() && slow < str.length();) {
            char c = str[fast];
            if (set.find(c) == set.end()) {
                // set 中不存在，未重复
                set.insert(c);
                maxLength = max(maxLength, fast - slow + 1);
                fast++;
            } else {
                // 重复了，从开始的位置移除元素，直到移除重复的那个后。fast继续向前走。
                set.erase(str[slow]);
                slow++;
            }
        }
        return maxLength;
    }
};

int main() {
    Solution* solution = new Solution();
    vector<string> arr = {"abcabcbb", "bbbbb", "pwwkew", "dvdf", "nfpdmpi"};
    for (string& s : arr) {
        cout << s << ":";
        int len = solution->lengthOfLongestSubstring2(s);
        cout << len << endl;
    }
    return 0;
}