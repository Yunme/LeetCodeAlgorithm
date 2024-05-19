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
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * https://blog.csdn.net/qfc_128220/article/details/127914382
 *
 * 6. 数组去重与排序
 * 给定一个乱序的数组，删除所有的重复元素，使得每个元素只出现一次，
 * 并且按照出现的次数从高到低进行排序，相同出现次数按照第一次出现顺序进行先后排序。
 *
 * https://blog.csdn.net/weixin_48157259/article/details/138087415
 *
 * 输入: 一组数据
 * 输出：去重和排序后的数字
 */

/**
 * 🤭 库函数大法
 */
vector<int> sortList(vector<int> &list) {
    unordered_map<int, int> map;
    for (int i : list) {
        map[i]++;
    }
    stable_sort(list.begin(), list.end(),
         [&map](const int &i, const int &j) { return map[i] > map[j]; });
    unordered_set<int> set;
    vector<int> result;
    for (int i : list) {
        if (set.count(i) == 0) {
            result.push_back(i);
        }
        set.insert(i);
    }
    return result;
}

int main() {
    vector<int> list = {1, 3, 3, 3, 2, 4, 4, 4, 5};
    // int a;
    // while (cin >> a) {
    //     list.push_back(a);
    // }
    string a;
    vector<int> ans = sortList(list);
    for (int i : ans) {
        cout << i << ',';
    }
    cout << endl;
}