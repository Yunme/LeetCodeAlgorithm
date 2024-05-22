#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

/**
 * 26:考勤信息
 * OJ：80%
 * 公司用一个字符串来表示员工的出勤信息：
 * absent：缺勤
 * late：迟到
 * leaveearly：早退
 * present：正常上班
 * 现需根据员工出勤信息，判断本次是否能获得出勤奖，能获得出勤奖的条件如下：
 * 缺勤不超过一次；
 * 没有连续的迟到/早退；
 * 任意连续7次考勤，缺勤/迟到/早退不超过3次。
 * 输入：
 * 第一行：n n为考勤记录数
 * 接下来n行：考勤记录
 * 输出：
 * 根据考勤规则，输出是否满足出勤奖，true or false
*/
string late = "late";
string le = "leaveearly";
string absent = "absent";

bool isGood(vector<string> &list) {
    int absentCount = 0;
    for (int i = 0; i < list.size(); ++i) {
        string s = list[i];
        if (s == absent) {
            absentCount++;
            if (absentCount > 1) return false;
        }
        // 连续迟到或早退
        if (i > 0 && (s == late || s == le) && (list[i - 1] == late || list[i - 1] == le))
            return false;
    }
    // 连续七天 缺勤 迟到 早退 不超过3次
    int n = 7;
    if (list.size() >= n) {
        int count = 0;
        for (int i = 0; i <= list.size() - n; ++i) {
            for (int j = i; j < i + n; ++j) {
                if (list[j] == absent || list[j] == late || list[j] == le)
                    count++;
            }
            if (count > 3) return false;
            else count = 0;
        }
    }
    return true;
}

int main() {
    int n;
    vector<vector<string>> list;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; ++i) {
        string input;
        getline(cin, input);
        stringstream ss(input);

        vector<string> l;
        string token;
        while (getline(ss, token, ' ')) {
            l.push_back(token);
        }
        list.push_back(l);
    }

//    list.push_back(
//            {"present", "present", "leaveearly", "late", "present", "present", "late",
//             "present", "late", "present", "present", "present", "present", "present"});
//    list.push_back(
//            {});

    for (auto &a: list) {
        if (isGood(a)) {
            cout << "true" << " ";
        } else {
            cout << "false" << " ";
        }
    }
    cout << endl;
}

