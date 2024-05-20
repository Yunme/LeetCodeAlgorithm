#include <math.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "../../../../../msys64/ucrt64/include/c++/13.2.0/parallel/numericfwd.h"
using namespace std;

/**
 * https://blog.csdn.net/weixin_48157259/article/details/138087531
 *
 * 13.智能成绩表
 * 将学生成绩按总分或单科分数排名
 *
 * https://blog.csdn.net/weixin_48157259/article/details/138138258
 *
 * 输入:
 * 第1行输入两个整数，学生人数 n 和科目数量 m。0 < n < 100，0 < m < 10
 * 第2行输入m个科目名称，彼此之间用空格隔开，科目名称只由英文字母构成，单个长度不超过10个字符。
 *  科目的出现顺字和后续输入的学生成绩一一对应。不会出现重复的科目名称。
 * 从第3行开始的行，输入 n 行
 * 学生的姓名和该生m个科目的成绩空格隔开，学生不会重名。
 * 最后一行，输入用作排名的科目名称，如果科目不存在，则按总分排序。
 * 输出：
 * 一行，按成绩排序后的学生名字，空格隔开，成绩相同的按学生名字典排序
 */

struct Student {
    string name;
    vector<int> scores;
    Student() : name(""), scores({}) {}
    Student(int m) : name(""), scores(vector<int>(m)) {}
};

int sum(vector<int> nums) {
    int ans = 0;
    for (auto i : nums) {
        ans += i;
    }
    return ans;
}

void sortList(int sortIndex, vector<Student> &list) {
    sort(
        list.begin(), list.end(),
        [&sortIndex](const Student &s1, const Student &s2) {
            int score1 = sortIndex >= 0 ? s1.scores[sortIndex] : sum(s1.scores);
            int score2 = sortIndex >= 0 ? s2.scores[sortIndex] : sum(s2.scores);
            return score1 > score2 || (score1 == score2 && s1.name < s2.name);
        });
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> subjects;
    // m 科目
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        subjects.push_back(s);
    }

    vector<Student> list(n);
    for (int i = 0; i < n; i++) {
        Student s(m);
        cin >> s.name;
        for (int j = 0; j < m; j++) {
            cin >> s.scores[j];
        }
        list[i] = s;
    }

    string sortSubject;
    cin >> sortSubject;
    auto index = find(subjects.begin(), subjects.end(), sortSubject);
    if (index != subjects.end()) {
        sortList(index - subjects.begin(), list);
    } else {
        sortList(-1, list);
    }

    for (auto s : list) {
        cout << s.name << " ";
        // for (auto i : s.scores) {
        //     cout << i << " ";
        // }
        // cout << endl;
    }
}