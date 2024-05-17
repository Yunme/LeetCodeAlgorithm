#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 732: 我的日程安排表 III
 * 当 k 个日程安排有一些时间上的交叉时（例如 k
 * 个日程安排都在同一时间内），就会产生 k 次预订。
 * https://leetcode.cn/problems/my-calendar-iii/description/
 */
class MyCalendarThree {
   public:
    MyCalendarThree() {}
    int book(int startTime, int endTime) {
        map[startTime]++;
        map[endTime]--;
        int maxBook = 0;
        int ans = 0;
        for (auto& [k, v] : map) {
            cout << k << " " << v << endl;
            maxBook += v;
            ans = max(maxBook, ans);
        }
        return ans;
    }

   private:
    map<int, int> map;
};

int main() {
    MyCalendarThree* s = new MyCalendarThree();

    vector<pair<int, int>> list = {{10, 20}, {50, 60}, {10, 40},
                                   {5, 15},  {5, 10},  {25, 55}};
    for (auto i : list) {
        int count = s->book(i.first, i.second);
        cout << count << endl;
    }
}