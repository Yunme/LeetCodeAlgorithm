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

int getMinute(vector<int> &nums) {
    int minutes = 0;
    int a = (nums[0] * 10 + nums[1]) * 60;
    int b = (nums[2] * 10 + nums[3]);
    minutes = a + b;
    return minutes;
}

string ans(vector<int> &nums) {
    int minutes = getMinute(nums);
    int n = nums.size();
    vector<vector<int>> list;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                for (int l = 0; l < n; ++l) {
                    if (nums[k] <= 5) {
                        if (nums[i] < 2) {
                            list.push_back({nums[i], nums[j], nums[k], nums[l]});
                        } else if (nums[i] == 2 && nums[j] <= 3) {
                            list.push_back({nums[i], nums[j], nums[k], nums[l]});
                        }
                    }
                }
            }
        }
    }

    int minMinuteCount = INT_MAX;
    vector<int> minA;
    for (auto i: list) {
        int a = getMinute(i);
        if (a - minutes > 0 && a - minutes < minMinuteCount) {
            minMinuteCount = a - minutes;
            minA = i;
        }
//        for (auto j: i) {
//            cout << j << " ";
//        }
//        cout << endl;
    }

//    cout << minMinuteCount << endl;
//    for (auto i: minA) {
//        cout << i << " ";
//    }

    if (minA.empty()) {
        int minMinute2 = INT_MAX;
        for (auto i: list) {
            int a = getMinute(i);
            if (a < minMinute2) {
                minMinute2 = a;
                minA = i;
            }
        }
    }

    return to_string(minA[0]) + to_string(minA[1]) + ":" + to_string(minA[2])
           + to_string(minA[3]);
}

int main() {
    string input;
    cin >> input;
    cin.ignore();

    vector<int> list;
    for (char c: input) {
        if (isdigit(c)) {
            list.push_back(c - '0');
        }
    }
    string a = ans(list);
    cout << a << endl;
    return 0;
}
