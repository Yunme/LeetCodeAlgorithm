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
 * hj19 简单错误记录
 *
 * key value 哈希表
 *
 * 开发一个简单错误记录功能小模块，能够记录出错的代码所在的文件名称和行号。
 * 处理：
 * 1、记录最多8条错误记录，循环记录，最后只用输出最后出现的八条错误记录。对相同的错误记录只记录一条，
 *    但是错误计数增加。最后一个斜杠后面的带后缀名的部分（保留最后16位）和行号完全匹配的记录才做算是“相同”的错误记录。
 * 2、超过16个字符的文件名称，只记录文件的最后有效16个字符；
 * 3、输入的文件可能带路径，记录文件名称不能带路径。也就是说，哪怕不同路径下的文件，
 *    如果它们的名字的后16个字符相同，也被视为相同的错误记录
 * 4、循环记录时，只以第一次出现的顺序为准，后面重复的不会更新它的出现时间，仍以第一次为准
 * 输入描述：每组只包含一个测试用例。一个测试用例包含一行或多行字符串。每行包括带路径文件名称，行号，以空格隔开。
 *
 * 输出描述：将所有的记录统计并将结果输出，格式：文件名 代码行数
 * 数目，一个空格隔开，如：
 * https://www.nowcoder.com/practice/2baa6aba39214d6ea91a2e03dff3fbeb
 */

/**
 * 字符串按字符分割
 */
vector<string> splitString(string s, char delimiter) {
    vector<string> result;
    int start = 0;
    for (int i = 0; i < s.length(); i++) {
        char a = s[i];
        if (a == delimiter) {
            result.push_back(s.substr(start, i - start));
            start = i + 1;
        }
    }
    result.push_back(s.substr(start, s.length() - start));
    return result;
}

struct ErrorRecord {
    string name;
    int line;
    int count;
    ErrorRecord() {}
    ErrorRecord(string name, int line) : name(name), line(line), count(1) {}
};

/**
 * 传统方式 list
 */
vector<ErrorRecord> note(vector<ErrorRecord> recods) {
    vector<ErrorRecord> saved;
    for (int i = 0; i < recods.size(); i++) {
        ErrorRecord err = recods[i];
        vector<string> path = splitString(err.name, '\\');
        string name = *path.rbegin();
        if (name.length() > 16) {
            name = name.substr(name.length() - 16, 16);
        }
        err.name = name;

        bool found = false;
        for (ErrorRecord &r : saved) {
            if (r.name == name && r.line == err.line) {
                found = true;
                r.count++;
                break;
            }
        }
        if (!found) {
            saved.push_back(err);
        }
    }
    return saved;
}

/**
 * 简洁版
 * name 和 行号作为map 的key 存储，value 为个数。
 * deque 双端队列，先进先出。先输入的先输出。
 */
void note1() {
    // 存储map
    map<string, int> map;
    // 输出队列
    deque<string> deque;
    string str;
    while (getline(cin, str)) {
        str = str.substr(str.find_last_of('\\') + 1);
        int pos = str.find_last_of(' ');
        // name超过16字符
        if (pos > 16) {
            str = str.substr(pos - 16);
        }

        if (map.find(str) == map.end()) {
            deque.push_back(str);
        }
        map[str]++;
        if (deque.size() > 8) {
            deque.pop_front();
        }
    }
    for (auto x : deque) {
        cout << x << " " << map[x] << endl;
    }
}

int normalNote() {
    vector<ErrorRecord> records;
    // records.emplace_back("D:\\zwtymj\\xccb\\ljj\\cqzlyaszjvlsjmkwoqijggmybr",
    //                      645);
    // records.emplace_back("E:\\je\\rzuwnjvnuz", 633);
    // records.emplace_back("C:\\km\\tgjwpb\\gy\\atl ", 637);
    // records.emplace_back("F:\\weioj\\hadd\\connsh\\rwyfvzsopsuiqjnr", 647);
    // records.emplace_back("E:\\ns\\mfwj\\wqkoki\\eez", 648);
    // records.emplace_back("D:\\cfmwafhhgeyawnool", 649);
    // records.emplace_back("E:\\czt\\opwip\\osnll\\c", 637);
    // records.emplace_back("G:\\nt\\f", 633);
    // records.emplace_back("F:\\fop\\ywzqaop", 631);
    // records.emplace_back("F:\\yay\\jc\\ywzqaop", 631);
    // records.emplace_back("D:\\zwtymj\\xccb\\ljj\\cqzlyaszjvlsjmkwoqijggmybr",
    //                      645);
    string name;
    int line;
    while (cin >> name >> line) {
        ErrorRecord record(name, line);
        records.push_back(record);
    }

    int len = 8;
    vector<ErrorRecord> saved = note(records);

    // 最多输出最后八个
    for (int i = max((int)(saved.size() - len), 0); i < saved.size(); i++) {
        ErrorRecord record = saved[i];
        cout << record.name << " " << record.line << " " << record.count
             << endl;
    }

    return 0;
}

int main() {
    note1();
    // normalNote();
    return 0;
}