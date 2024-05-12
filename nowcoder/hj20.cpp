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
 * hj20 密码验证合格程序
 * 密码要求:
 * 1.长度超过8位
 * 2.包括大小写字母.数字.其它符号,以上四种至少三种
 * 3.不能有长度大于2的包含公共元素的子串重复 （注：其他符号不含空格或换行）
 * https://www.nowcoder.com/practice/184edec193864f0985ad2684fbc86841
 */
/**
 * 初始版本
 * 时间复杂度 O(n^2), 空间复杂度O(1)
 */
bool validPassword(string &password) {
    if (password.length() < 8) return false;

    // 包含大写，小写，数字，其他字符。
    bool containUpper = false, containLower = false, containNum = false,
         containChar = false;
    int maxSameCount = 0;
    for (int i = 0; i < password.length(); i++) {
        char c = password[i];
        bool lower = c >= 'a' && c <= 'z';
        bool upper = c >= 'A' && c <= 'Z';
        bool num = c >= '0' && c <= '9';
        containChar = containChar || !upper && !lower && !num;
        containUpper = containUpper || upper;
        containLower = containLower || lower;
        containNum = containNum || num;

        int sameCount = 0;
        int lastSameCount = 0;
        int k = i;
        // 暴力查找
        for (int j = i + 3; j < password.length(); j++) {
            char cFast = password[j];
            if (password[k] == cFast) {
                sameCount++;
                k++;
            } else {
                k = i;
                lastSameCount = sameCount;
                sameCount = 0;
            }
            lastSameCount = sameCount;
            maxSameCount = max(maxSameCount, lastSameCount);
        }
    }
    int count = 0;
    if (containUpper) count++;
    if (containLower) count++;
    if (containNum) count++;
    if (containChar) count++;
    // cout << count << " " << maxSameCount << endl;
    return count >= 3 && maxSameCount <= 2;
}

/**
 * 更清晰的寻找长度大于等于3的重复子串
 */
bool validPassword2(string &password) {
    if (password.length() < 8) return false;
    int hasUpper = 0, hasLower = 0, hasNum = 0, hasChar = 0;
    for (char c : password) {
        if (c >= 'a' && c <= 'z')
            hasUpper = 1;
        else if (c >= 'A' && c <= 'Z')
            hasLower = 1;
        else if (c >= '0' && c <= '9')
            hasNum = 1;
        else
            hasChar = 1;
    }
    // 不同类型小于3个
    if (hasUpper + hasLower + hasNum + hasChar < 3) return false;

    // 3个一组从前向后比较。
    for (int i = 0; i <= password.length() - 6; i++)
        for (int j = i + 3; j < password.length(); j++)
            if (password.substr(i, 3) == password.substr(j, 3)) {
                return false;
            }
    // 前面后面拼接起来查找是否包含中间的3个。。
    for (int i = 0; i < password.length() - 3; ++i) {
        string ss = password.substr(0, i) + password.substr(i + 3);
        if (ss.find(password.substr(i, 3)) != string::npos) {
            return false;
        }
    }

    return true;
}

/**
 * 简洁版
 * 时间复杂度 O(n), 空间复杂度O(n)
 */
bool validPassword3(string &password) {
    if (password.length() < 8) return false;
    int hasUpper = 0, hasLower = 0, hasNum = 0, hasChar = 0;
    for (char c : password) {
        if (c >= 'a' && c <= 'z')
            hasUpper = 1;
        else if (c >= 'A' && c <= 'Z')
            hasLower = 1;
        else if (c >= '0' && c <= '9')
            hasNum = 1;
        else
            hasChar = 1;
    }
    // 不同类型小于3个
    if (hasUpper + hasLower + hasNum + hasChar < 3) return false;

    // 检测重复子串>=3
    // 把每截取到的3个子串，存到set里
    unordered_set<string> set;
    for (int i = 0; i < password.length(); i++) {
        string substr = password.substr(i, 3);
        if (set.find(substr) != set.end()) {
            // 如果set中已有，说明之前出现过，重复。
            return false;
        } else {
            set.insert(substr);
        }
    }
    return true;
}

int main() {
    string s;
    vector<string> list;
    // while (cin >> s) {
    //     list.push_back(s);
    // }
    list.push_back("dsasdaA4dsasda");
    list.push_back("021Abc9000");
    list.push_back("021Abc9Abc1");
    list.push_back("021ABC9000");
    list.push_back("021$bc9000");

    for (string &s : list) {
        string valid = validPassword2(s) ? "OK" : "NG";
        cout << valid << endl;
    }
    return 0;
}