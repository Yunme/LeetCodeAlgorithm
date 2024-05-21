#include <math.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

/**
 * https://blog.csdn.net/weixin_48157259/article/details/138087531
 *
 * 21. 掌握单词个数
 * 有一个字符串数组 words，和一个字符串 chars
 * 对于 words 中的某个单词，如果在 chars
 * 中都能找到所有字母，则表示掌握了这个单词； words 中的单词都由小写字母组成
 * chars 中的由小写字母和 ? 问号组成;  每个字符只能匹配一次
 * ? 问号表示万能字母，可以匹配任一字母，但 ? 只能匹配一次
 *
 * https://blog.csdn.net/weixin_48157259/article/details/138868714
 *
 * 输入:
 * 第一行：words 数组个数 N
 * 接下来 N 行：words 中的元素
 * 最后一行：chars
 * 输出：
 * words 中掌握的单词个数
 */

/**
 * 法1：自己实现
 * 记录 chars 中各个字母出现的个数
 * 逐个对比 words 中的单词，对某个单词
 * 逐个对比各个字符：
 * 如果在 map 中有则 map 中个数-1，
 * 如果在 map 中个数为0了，则去消耗问号。
 *
 */
int getLearnedWordCount(vector<string>& words, string& chars) {
    // chars 中字母 及对应个数
    unordered_map<char, int> map;
    for (char& c : chars) {
        map[c]++;
    }
    int ans = 0;
    int l = 0;
    for (string& s : words) {
        unordered_map<char, int> temp = map;
        bool match = true;
        // ? 号数大于单词长度，必会匹配
        if (temp.count('?') > 0 && temp['?'] >= s.length()) {
            ans++;
            continue;
        }
        // 单词长度大于 字符串长度，肯定没法匹配
        if (s.length() > chars.length()) continue;
        for (char c : s) {
            // 存在 个数减一
            if (temp.count(c) > 0 && temp[c] > 0) {
                temp[c]--;
            } else if (temp.count('?') > 0 && temp['?'] > 0) {
                // 字符不存在 有?号，且个数大于0 则尝试消耗 ? 号
                temp['?']--;
            } else {
                // 字符不存在 而且无 ?
                match = false;
            }
        }
        if (match) {
            // cout << s << endl;
            ans++;
        }
    }
    return ans;
}

// #define file cin
int main() {
    // ifstream file("21t copy.txt");
    // if (!file.is_open()) {
    //     return 1;
    // }

    int n;
    cin >> n;
    cin.ignore();
    vector<string> words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }
    cin.ignore();
    string chars;
    cin >> chars;
    cin.ignore();

    // nwtljcutebqun
    int ans = getLearnedWordCount(words, chars);
    cout << ans << endl;
}

/**
 * 法2：写法差异
 * 把每个单词的字母出现次数也统计
 * 跟 chars 的map 比对
 * 对于某个字符，如果 chars 中出现的次数更多，则继续下一个字符
 * 如果字符在单词中出现的较少，那么就消耗对应的问号的个数。
 * 如果 问号数量 小于0，则不匹配
 */
bool check(unordered_map<char, int>& cntChars,
           unordered_map<char, int>& cntWord, int num) {
    for (auto& kv : cntWord) {
        char k = kv.first;
        if (cntChars[k] >= cntWord[k]) {
            continue;
        } else {
            num -= cntWord[k] - cntChars[k];
            if (num < 0) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    cin.ignore();  // To consume the newline character

    vector<string> words(n);
    for (int i = 0; i < n; ++i) {
        cin >> words[i];
    }
    cin.ignore();  // To consume the newline character

    string chars;
    getline(cin, chars);

    unordered_map<char, int> cntChars;
    for (char c : chars) {
        cntChars[c]++;
    }

    int ans = 0;
    int num = cntChars['?'];

    for (string& word : words) {
        unordered_map<char, int> cntWord;
        for (char c : word) {
            cntWord[c]++;
        }
        ans += check(cntChars, cntWord, num) ? 1 : 0;
    }
    cout << ans << endl;
    return 0;
}