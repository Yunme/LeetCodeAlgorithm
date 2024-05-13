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
 * hj26 字符串排序
 * 规则 1 ：英文字母从 A 到 Z 排列，不区分大小写。
 * 如，输入： Type 输出： epTy
 * 规则 2 ：同一个英文字母的大小写同时存在时，按照输入顺序排列。
 * 如，输入： BabA 输出： aABb
 * 规则 3 ：非英文字母的其它字符保持原来的位置。
 * 如，输入： By?e 输出： Be?y
 * https://www.nowcoder.com/practice/5190a1db6f4f4ddb92fd9c365c944584
 */

/**
 * 字符串排序
 * 快排 不稳定
 * 归并 稳定
 */
int compare(char a, char b) {
    bool aAlpha = a >= 'a' && a <= 'z' || a >= 'A' && a <= 'Z';
    bool bAlpha = b >= 'a' && b <= 'z' || b >= 'A' && b <= 'Z';
    if (aAlpha && bAlpha) {
        char A = toupper(a);
        char B = toupper(b);
        if (A == B) {
            return 0;
        } else {
            return A > B ? 1 : -1;
        }
    }
    return 0;
}

void merge(vector<char> &arr, int low, int mid, int high) {
    // 左半部分 mid 包含
    // 但 vector 构造方法是左比右开，所以+1.
    vector<char> left(arr.begin() + low, arr.begin() + mid + 1);
    vector<char> right(arr.begin() + mid + 1, arr.begin() + high + 1);
    vector<char> result;
    int i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        int compared = compare(left[i], right[j]);
        // left <= right
        if (compared == -1 || compared == 0) {
            result.push_back(left[i]);
            i++;
        } else if (compared == 1) {
            // left > right
            result.push_back(right[j]);
            j++;
        }
    }
    // 拼接剩下的
    if (i < left.size()) {
        for (int k = i; k < left.size(); k++) {
            result.push_back(left[k]);
        }
    } else {
        for (int k = j; k < right.size(); k++) {
            result.push_back(right[k]);
        }
    }

    // 排好序的复制到源数组中
    for (int i = 0; i < result.size(); i++) {
        arr[low + i] = result[i];
    }
}

void test(vector<char> &a) { a[0] = 'Z'; }

string mergeSortString(string str) {
    int len = str.length();
    vector<char> arr(len);
    for (int i = 0; i < len; i++) {
        arr[i] = str[i];
    }
    // 这里 mid 既可以在左半部分也可以在右半部分
    // 一般在左半部分 因为通常 计算 mid = (low + high) / 2  就在左半部分
    // 右半部分的计算方式：mid = left + (right - left) / 2
    for (int size = 1; size < len; size *= 2) {
        for (int i = 0; i < len - size; i += 2 * size) {
            int low = i;
            // mid 一般在左半部分 左部分 [low, mid]
            int mid = i + size - 1;
            // 右部分 (mid, high] high 需要包含
            int high = min(i + 2 * size - 1, len - 1);
            merge(arr, low, mid, high);
        }
    }
    return {arr.begin(), arr.end()};
}

string sortString(string str) {
    // 特殊字符先拿出来 等排序好后再插入
    // map 存储特殊字符的 index 和 字符。
    map<int, char> map;
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        if (!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z')) {
            map[i] = c;
        }
    }
    // 两种擦除特殊字符方式
    // 1. 从前向后，每擦除一个 index 前移一位。
    // int i = 0;
    // for (auto &[k, v] : map) {
    //     str.erase(k - i, 1);
    //     i++;
    // }
    // 2. 从后向前，不要修改索引
    for (int i = str.length(); i >= 0; i--) {
        char c = str[i];
        if (map.find(i) != map.end()) {
            str.erase(i, 1);
        }
    }

    // 排序字符串
    str = mergeSortString(str);

    // 插入特殊字符
    for (auto &[k, v] : map) {
        str.insert(str.begin() + k, v);
    }
    return str;
}

int main() {
    string s = "A Famous Saying: Much Ado About Nothing (2012/8).";
    // string s = "A$Fam$(2012/8).";
    getline(cin, s);
    cout << s << endl;
    cout << sortString(s) << endl;
    return 0;
}