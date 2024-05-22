#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

/**
 * 27:解密犯罪时间
 * OJ：100%
 * 警察在侦破一个案件时，得到了线人给出的可能犯罪时间，形如“HH:MM”表示的时刻。
 * 根据警察和线人的约定，为了隐蔽，该时间是修改过的解密规则为:
 * 利用当前出现过的数字，构造下一个距离 当前时间只最近的时刻，则该时间为可能的犯罪时间。
 * 每个出现数字都可以被无限次使用。
 * 输入：形如HH:MM的字符串
 * 输出：
 * 推理出的可能的犯罪时间
*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <climits>

using namespace std;

/**
 * Honor
 * 敏感词屏蔽
 * 
 * 搜索字符串中，如果子串完全匹配敏感词，则将它替换成 *
 * 只考虑匹配到了一次。
*/
int search(string &str, string &search) {
    if (search.length() > str.length()) return -1;
    int i, j = 0;
    while (i < str.length() && j < search.length()) {
        if (str[i] == search[j]) {
            j++;
        } else {
            j = 0;
        }
        i++;
    }
    if (j == search.length()) return i - j;
    return -1;
}

int main() {
    string str1;
    string str2;
    cin >> str1 >> str2;
    cin.ignore();

//    int index = str1.find(str2);
    int index = search(str1, str2);
    if (index != string::npos) {
        for (int i = 0; i < str2.length(); ++i) {
            str1[index + i] = '*';
        }
    }

    cout << str1 << endl;
    return 0;
}
