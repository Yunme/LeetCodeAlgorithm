#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

/**
 * 25: 英文输入法
 * OJ：95%
 * 主管期望你来实现英文输入法单词联想功能。
 * 需求如下：
 * 依据用户输入的单词前缀，从已输入的英文语句中联想出用户想输入的单词，按字典序输出联想到的单词序列，
 * 如果联想不到，请输出用户输入的单词前缀。
 * 注意：
 * 英文单词联想时，区分大小写
 * 缩略形式如”don’t”，判定为两个单词，”don”和”t”
 * 输出的单词序列，不能有重复单词，且只能是英文单词，不能有标点符号
 * 输入：
 * 首行输入一段由英文单词word和标点符号组成的语句str；
 * 接下来一行为一个英文单词前缀pre。
 * 输出：
 * 输出符合要求的单词序列或单词前缀，存在多个时，单词之间以单个空格分割
*/

int main() {
    string str;
    getline(cin, str);
    stringstream ss(str);

    vector<string> words;
    string token;
    while (getline(ss, token, ' ')) {
        for (int i = token.length() - 1; i >= 0; i--) {
            if (!isalpha(token[i]) && token[i] != '\'') {
                token.erase(i, 1);
            }
        }
        if (token.find('\'') != string::npos) {
            stringstream sstoken(token);
            string w;
            while (getline(sstoken, w, '\'')) {
                words.push_back(w);
            }
        } else {
            words.push_back(token);
        }
    }
    string pre;
    cin >> pre;

    vector<string> ans;
    for (auto s: words) {
        if (s.find(pre) == 0) {
            ans.push_back(s);
        }
    }
    stable_sort(ans.begin(), ans.end());
    if (ans.empty()) {
        cout << pre << endl;
    } else {
        for (auto &s: ans) {
            cout << s << " ";
        }
        cout << endl;
    }
}
