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
 * 4. 贪心歌手
 *
 * 歌手准备从 A 城去 B 城参加演出
 * 按照合同，他必须在 T 天内赶到。
 * 歌手途径 N 座城市。
 * 歌手不能往回走。
 * 每两座城市之间需要的天数都可以提前获知。
 * 歌手在每座城市都可以在路边卖唱赚钱。经过调研，歌手提前获知了每座城市卖唱的收入预期。
 * 如果在一座城市第一天卖唱可以赚 M，后续每天的收入会减少 D (第二天赚的钱是
 * M-D，第三天是 M-2D…)。 如果收入减到 0 就不会再少了。
 * 歌手到达后的第二天才能开始卖唱。如果今天卖过唱，第二天才能出发。
 * https://blog.csdn.net/weixin_48157259/article/details/137877804
 *
 * 输入
 * 第一行：总天数 T 和 经过的城市数 N，
 * 第二行：N+1 个数字，代表两座城市之前耗费时间 总和 <= T
 * 接下来 N 行：代表每个城市第一天赚的 M 和后续每天减少的 D
 * 输出：最多赚的钱数
 */

/**
 * 法1：贪心 模拟
 * 剩下的天数分配到当前可以赚更多的城市赚，当递减到小于另一个时，再去另一个。
 * 虽然考虑是从每天去赚最多的城市，但与一直在一个城市是一样的。
 */
int maxMoney(int t, int n, vector<int> &dayList,
             vector<pair<int, int>> &moneyList) {
    int costDay = 0;
    for (int i : dayList) {
        costDay += i;
    }
    int remainDay = t - costDay;

    if (remainDay <= 0) return 0;
    int totalMoney = 0;
    // 剩余天数
    for (int i = 0; i < remainDay; i++) {
        if (moneyList.empty()) break;
        // 每天找能赚最多的去
        auto maxCity = max_element(moneyList.begin(), moneyList.end());
        totalMoney += maxCity->first;
        // 赚完，能赚的减去递减值。
        maxCity->first -= maxCity->second;
        // // 如果城市能赚的小于0，则删除
        if (maxCity->first <= 0) {
            moneyList.erase(maxCity);
        }
    }
    return totalMoney;
}

/**
 * 法2：使用优先队列 贪心
 * 优先队列，不是根据插入的顺序出队，而是根据定义的优先级，队内优先级大的出。
 */
int maxMoney2(int t, int n, vector<int> &dayList,
              vector<pair<int, int>> &moneyList) {
    int costDay = 0;
    for (int i : dayList) {
        costDay += i;
    }
    int remainDay = t - costDay;

    if (remainDay <= 0) return 0;
    int totalMoney = 0;
    // 默认大的优先
    priority_queue<pair<int, int>> queue;
    for (auto i : moneyList) {
        queue.push(i);
    }
    for (int i = 0; i < remainDay; i++) {
        if (queue.empty()) break;
        pair<int, int> city = queue.top();
        queue.pop();
        int money = city.first;
        int delta = city.second;
        totalMoney += money;
        money -= delta;
        if (money > 0) {
            queue.push({money, delta});
        }
    }
    return totalMoney;
}

int main() {
    int t = 10, n = 2;
    cin >> t >> n;
    vector<int> days(n + 1);
    for (int i = 0; i < n + 1; i++) {
        cin >> days[i];
    }
    vector<pair<int, int>> money(n);
    for (size_t i = 0; i < n; i++) {
        int p;
        int q;
        cin >> p >> q;
        money[i] = {p, q};
    }
    int max = maxMoney2(t, n, days, money);
    cout << max;
}