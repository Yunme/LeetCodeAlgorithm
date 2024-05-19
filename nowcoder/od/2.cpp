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
 * 2.机器人搬砖
 *
 * 一共 n 堆砖，第i堆砖中有bricks[i]块砖，要求在
 * 8小时内搬完，机器人每小时只能在一堆里搬，
 * 能搬多少块取决于它有多少能量格；每小时只能补充一次且只在这一小时有效。
 * 尽量减少每次补充
 * https://blog.csdn.net/qfc_128220/article/details/134454058
 *
 * 类似于：875 https://leetcode.cn/problems/koko-eating-bananas/description/
 */

bool canMove(int s, vector<int> &bricks, int h) {
    int cost = 0;
    for (int i : bricks) {
        cost += (i + s - 1) / s;
    }
    return cost <= h;
}

/**
 * 二分查找 寻找最佳答案
 * @param nums 砖块数量
 * 8小时内
 */
int minSpeed(vector<int> &bricks) {
    // 大于8个仓库 无法完成任务
    int h = 8;
    if (bricks.size() > h) return -1;
    // 从1到最大值进行 单调 渐进式查找
    int low = 1;
    int high = 0;
    for (int i : bricks) {
        high = max(high, i);
    }
    if (bricks.size() == h) return high;
    while (low < high) {
        // 当前检查的速度
        int mid = (low + high) / 2;
        if (canMove(mid, bricks, h)) {
            // 当前速度可以搬完，那么最小速度 <= 它
            high = mid;
        } else {
            // 当前速度搬不完，那么最小速度 > 它
            low = mid + 1;
        }
    }
    return low;
}

int main() {
    int n = 120;
    int m = 7;
    // cin >> n >> m;
    vector<vector<int>> array = {{3, 6, 7, 11},
                                 {30, 11, 23, 4, 20},
                                 {30, 11, 23, 4, 20},
                                 {1000000000},
                                 {1, 3, 4, 5, 5, 6, 6, 7, 9}};

    for (size_t i = 0; i < array.size(); i++) {
        vector<int> arr = array[i];
        cout << minSpeed(arr) << endl;
    }
}