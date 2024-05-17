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
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 729: 我的日程安排表 I
 * 当两个日程安排有一些时间上的交叉时（例如两个日程安排都在同一时间内），就会产生
 * 重复预订 。 输出每次预定后，是否会导致重复预订。
 * https://leetcode.cn/problems/my-calendar-i/description/
 */
class MyCalendarThree {
   public:
    MyCalendarThree() {}
    /**
     * 法1：暴力查找 事件复杂度 O(n^2)
     * 如果可以将日程安排成功添加到日历中而不会导致重复预订，
     * 返回 true。
     * 否则，返回 false 并且不要将该日程安排添加到日历中。
     */
    bool book(int startTime, int endTime) {
        // 暴力遍历查找
        for (auto i : list) {
            // [s1, e1) 和 [s2, e2) 如果不冲突 则 e2 <= s1 或 s2 >= e1;
            // 取反 则冲突
            // e2 > s1 且 s2 < e1;
            if (startTime < i.second && endTime > i.first) {
                return false;
            }
        }
        list.emplace_back(startTime, endTime);
        return true;
    }

    /**
     * 法2：二分查找
     *
     */
    bool book2(int startTime, int endTime) {
        cout << startTime << " " << endTime << endl;
        // 首次直接插入
        if (set.empty()) {
            set.emplace(startTime, endTime);
            return true;
        }
        // 寻找第一个不小于的，如果没有就返回 end
        auto a = set.lower_bound({endTime, 0});
        cout << "last:" << (a == set.end()) << endl;
        if (a == set.begin() || (--a)->second <= startTime) {
            set.emplace(startTime, endTime);
            return true;
        }
        return false;
    }

   private:
    vector<pair<int, int>> list;
    set<pair<int, int>> set;
};

int main() {
    MyCalendarThree* s = new MyCalendarThree();

    // vector<pair<int, int>> list = {
    //     {37, 50}, {33, 50}, {4, 17}, {35, 48}, {8, 25}};
    vector<pair<int, int>> list = {{10, 20}, {15, 25}, {20, 30},
                                   {5, 15},  {5, 10},  {25, 55}};
    for (auto i : list) {
        bool count = s->book2(i.first, i.second);
        cout << count << endl;
    }
}