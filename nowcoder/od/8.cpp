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
using namespace std;

/**
 * https://blog.csdn.net/weixin_48157259/article/details/138087531
 *
 * 8.篮球游戏
 * 幼儿园里有一个放倒的圆桶，它是一个线性结构，允许在桶的右边将篮球放入，
 * 可以在桶的左边和右边将篮球取出。每个篮球有单独的编号，
 * 老师可以连续放入一个或多个篮球，小朋友可以在桶左边或右边将篮球取出，
 * 当桶里只有一个篮球的情况下，必须从左边取出。
 *
 * https://blog.csdn.net/weixin_48157259/article/details/138011098
 *
 * 输入:
 * 第一行：老师依次放入篮球的编号
 * 第二行：检查是否能够按照放入顺序取出篮球的编号
 * 输出：
 * 对于每个篮球的取出序列，如果能取出，那么打印取出顺序左边L，右边R；
 * 不能取出打印 NO
 */

/**
 * 遍历输出序列，
 * 如果队列不为空 且 头或尾是当前输出的，则输出，并记录从哪个方向输出。
 * 否则，从右边放入
 */
vector<string> takeBasketball(vector<int> &putList, vector<int> &takeList) {
    vector<string> ans;
    deque<int> deque;
    // 左边对应队头，右边对应队尾
    // 只能从右边放入；对应队尾
    int i = 0, j = 0;
    while (j < takeList.size()) {
        if (!deque.empty() &&
            (takeList[j] == deque.front() || takeList[j] == deque.back())) {
            if (takeList[j] == deque.front()) {
                ans.push_back("L");
                deque.pop_front();
            } else if (takeList[j] == deque.back()) {
                ans.push_back("R");
                deque.pop_back();
            }
            j++;
        } else {
            if (i < putList.size()) {
                deque.push_back(putList[i++]);
            } else {
                return {"NO"};
            }
        }
    }
    return ans;
}

int main() {
    string s;
    getline(cin, s);
    vector<int> putList;
    int start = 0;
    int pos = 0;
    while ((pos = s.find(",", start)) != string::npos) {
        string sub = s.substr(start, pos - start);
        putList.push_back(stoi(sub));
        start = pos + 1;
    }
    putList.push_back(stoi(s.substr(start, s.length() - start)));

    getline(cin, s);
    vector<int> takeList;
    start = 0;
    pos = 0;
    while ((pos = s.find(',', start)) != string::npos) {
        string sub = s.substr(start, pos - start);
        takeList.push_back(stoi(sub));
        start = pos + 1;
    }
    takeList.push_back(stoi(s.substr(start, s.length() - start)));

    // stringstream ss(s);
    // string token;
    // // 字符可以用这个分割
    // while (getline(ss, token, ',')) {
    //     cout << token << "@";
    // }

    vector<string> ans = takeBasketball(putList, takeList);
    for (string &s : ans) {
        cout << s;
    }
    cout << endl;
}