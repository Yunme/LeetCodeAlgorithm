#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/**
 * 27:解密犯罪时间
 * OJ：100%
 * 警察在侦破一个案件时，得到了线人给出的可能犯罪时间，形如“HH:MM”表示的时刻。
 * 根据警察和线人的约定，为了隐蔽，该时间是修改过的解密规则为:
 * 利用当前出现过的数字，构造下一个距离
 * 当前时间只最近的时刻，则该时间为可能的犯罪时间。
 * 每个出现数字都可以被无限次使用。
 * 输入：形如HH:MM的字符串
 * 输出：
 * 推理出的可能的犯罪时间
 */
#include <climits>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/**
 * 法1：暴力法
 * 根据已有的四个数字，组成的新的四个数字，每位都有4个可能，共 4*4*4*4
 * =256种组合 对一个时刻来说，分数十位不能大于5；小时十位不能大于2
 */
int getMinute(vector<int> &nums) {
    int minutes = 0;
    int a = (nums[0] * 10 + nums[1]) * 60;
    int b = (nums[2] * 10 + nums[3]);
    minutes = a + b;
    return minutes;
}

string decryptCrimeTime(string &input) {
    vector<int> nums;
    for (char c : input) {
        if (isdigit(c)) {
            nums.push_back(c - '0');
        }
    }
    int minutes = getMinute(nums);
    int n = nums.size();
    vector<vector<int>> list;
    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                for (int l = 0; l < n; ++l) {
                    count++;
                    if (nums[k] <= 5) {
                        if (nums[i] < 2 || (nums[i] == 2 && nums[j] <= 3)) {
                            list.push_back(
                                {nums[i], nums[j], nums[k], nums[l]});
                            cout << nums[i] << " " << nums[j] << " " << nums[k]
                                 << " " << nums[l] << endl;
                        }
                    }
                }
            }
        }
    }
    cout << "count:" << count << endl;

    int minMinuteCount = INT_MAX;
    vector<int> minA;
    // 找出列表中4位数字组成的时间 大于 传入的时间
    // 大于传入时间的 最小时间
    // 如果找到说明结论时间就是这个最小时间
    for (auto i : list) {
        int a = getMinute(i);
        if (a - minutes > 0 && a - minutes < minMinuteCount) {
            minMinuteCount = a - minutes;
            minA = i;
        }
    }

    // 如果没找到，那么说明在第二天
    // 直接找里面最小的那个，就是第二天的最小时间
    if (minA.empty()) {
        int minMinute2 = INT_MAX;
        for (auto i : list) {
            int a = getMinute(i);
            if (a < minMinute2) {
                minMinute2 = a;
                minA = i;
            }
        }
    }
    // 组装返回
    return to_string(minA[0]) + to_string(minA[1]) + ":" + to_string(minA[2]) +
           to_string(minA[3]);
}

/**
 * 法2：优化法
 * 两次循环找到 符合分钟数 的数列表
 * 从小到大排序
 * 从前向后找：
 * 1. 先找最小的大于给定的分钟数，如有，则跟已有的小时组成时间，返回；
 * 2.
 * 如果不是23点，找最小的大于给定的小时数，如有，则跟最小的分钟数组成时间，返回；
 * 3. 最后，是第二天，直接返回最小的数 组成的小时和分钟，返回
 */
string format(int a, int b) {
    string A = (a <= 9 ? "0" : "") + to_string(a);
    string B = (b <= 9 ? "0" : "") + to_string(b);
    return A + ":" + B;
}

string decryptCrimeTime2(string &s) {
    std::vector<int> nums_list;
    for (char i : s) {
        if (i != ':') {
            nums_list.push_back(i - '0');
        }
    }
    // 小时
    int H = stoi(s.substr(0, 2));
    // 分钟
    int M = stoi(s.substr(3, 2));
    
    vector<int> unique_nums;
    // <=59 找到合法分钟的数
    // 合法小时数的也在里面 <= 23
    for (int i : nums_list) {
        for (int j : nums_list) {
            // 分数十位 小于等于5
            if (i <= 5) {
                unique_nums.push_back(i * 10 + j);
                cout << i * 10 + j << " ";
            }
        }
    }
    cout << endl;
    // 进行排序 小的在前
    std::sort(unique_nums.begin(), unique_nums.end());

    // 找到大于当前分钟的最小分钟
    for (int i : unique_nums) {
        if (i <= M) continue;
        // 如果能找到
        // 和当前小时组成 就是结果
        return format(H, i);
    }

    // 如果上述，大于当前分钟的找不到
    // 不是 23 点的情况下，找大于当前小时的最小小时
    if (H != 23) {
        for (int i : unique_nums) {
            if (i <= H) continue;
            // 如果能找到
            // 和最小分钟，组成最小时间
            return format(i, unique_nums[0]);
        }
    }

    // 否则就是第二天的最小时间
    return format(unique_nums[0], unique_nums[0]);
}

int main() {
    string input = "12:34";
    // cin >> input;
    // cin.ignore();

    string a = decryptCrimeTime2(input);
    cout << a << endl;
    return 0;
}
