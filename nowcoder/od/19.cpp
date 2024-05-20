#include <math.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
// #include <sstream>
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
 * 19. 测试用例执行计划
 * N 个产品特性需要测试，每个特性都有优先级，产品特性使用ID标识。
 * 设计了 M 个测试用例，每个用例对应了一个产品特性集合，
 * 测试用例的优先级定义为其覆盖特性的优先级之和。
 * 计算用例的执行顺序，优先级的大的先执行，优先级相同的，按用例ID小的先执行
 * https://blog.csdn.net/weixin_48157259/article/details/139015748
 *
 * 输入:
 * 第一行输入为 N 和 M ，N 表示特性的数量 M 表示测试用例的数量
 * 之后 N 行表示特性 ID=1 到特性 ID=N 的优先级。
 * 再接下来 M 行表示测试用例 ID=1 到测试用例 ID=M 关联的特性的 ID 的列表。
 * 输出：
 * 按照执行顺序（优先级从大到小）输出测试用例的 ID，每行一个 ID。
 */

int main() {
    int m, n;
    // n: 特性个数
    // m：用例个数
    cin >> n >> m;
    cin.ignore();
    // 特性的优先级
    vector<int> priorityList(n);
    for (int i = 0; i < n; i++) {
        string a;
        getline(cin, a);
        priorityList[i] = stoi(a);
    }
    // 用例关联的特性id列表
    vector<pair<int, int>> list(m);
    for (int i = 0; i < m; i++) {
        string input;
        getline(cin, input);
        stringstream ss(input);
        string token;

        int sum = 0;
        while (getline(ss, token, ' ')) {
            // cout << stoi(token) - 1 << ",";
            sum += priorityList[stoi(token) - 1];
        }
        list[i] = {sum, i + 1};
    }
    // sort(list.begin(), list.end(), greater<pair<int, int>>());
    sort(list.begin(), list.end(),
         [](const pair<int, int> &p1, const pair<int, int> &p2) {
             return p1.first > p2.first || (p1.first == p2.first) && (p1.second < p2.second);
         });

    for (auto i : list) {
        cout << i.second << endl;
    }
}