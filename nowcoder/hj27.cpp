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
 * hj27 查找兄弟单词
 * 兄弟单词为：交换该单词的顺序，而不添加、删除和修改原有字母生成的单词
 * 要求和原单词不同。比如 ab 和 ba 就是兄弟单词
 *
 * 给定n个单词，再给一个单词x，在n中寻找x的兄弟单词，比将兄弟单词按字典排序。输出第k个。
 *
 * 输入：
 * 只有一行。 先输入字典中单词的个数n，再输入n个单词作为字典单词。
 * 然后输入一个单词x 最后后输入一个整数k 第一行输出查找到x的兄弟单词的个数m
 * 输出：
 * 查找到的按照字典顺序排序后的第k个兄弟单词，没有符合第k个的话则不用输出。
 * https://www.nowcoder.com/practice/03ba8aeeef73400ca7a37a5f3370fe68
 */

/**
 * 判断是否是兄弟
 * 对单词按字母排序后，兄弟单词应该是相等的
 */
bool isBrother(string str, string brother) {
    if (str != brother) {
        sort(str.begin(), str.end());
        sort(brother.begin(), brother.end());
        return str == brother;
    }

    return false;
}

/**
 * 比对字符串是否是兄弟单词
 * 不相等的单词，长度相等的情况下，各个字母出现次数相同
 * 哈希表存储单词出现次数
 */
vector<string> findBrother(string &str, vector<string> &strs) {
    // 待比较单词字母出现次数
    unordered_map<char, int> map1;
    for (char c : str) {
        map1[c]++;
    }

    vector<string> brothers;
    for (string &s : strs) {
        if (str == s || str.length() != s.length()) {
            continue;
        }
        if (isBrother(str, s)) {
            brothers.push_back(s);
        }

        // 判断是否是兄弟 比较哈希表存储单词出现次数
        // unordered_map<char, int> map2;
        // for (char c : s) {
        //     map2[c]++;
        // }
        // if (map1 == map2) {
        //     brothers.push_back(s);
        // }
    }
    sort(brothers.begin(), brothers.end());
    return brothers;
}

int main() {
    int n = 0;
    cin >> n;
    vector<string> strs(n);
    for (int i = 0; i < n; i++) {
        cin >> strs[i];
    }
    string str;
    cin >> str;
    int index;
    cin >> index;

    vector<string> brothers = findBrother(str, strs);

    // for (string &s : brothers) {
    //     cout << s << " ";
    // }
    // cout << endl;

    cout << brothers.size() << endl;
    if (index <= brothers.size()) {
        cout << brothers[index - 1] << endl;
    }
    return 0;
}