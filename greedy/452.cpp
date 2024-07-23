#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 452：用最少数量的箭引爆气球
 *
 * 有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组
 * points ， 其中points[i] = [xstart, xend] 表示水平直径在 xstart 和
 * xend之间的气球。你不知道气球的确切 y 坐标。 一支弓箭可以沿着 x 轴从不同点
 * 完全垂直 地射出。 在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为
 * xstart，xend， 且满足  xstart ≤ x ≤ xend，则该气球会被 引爆
 * 。可以射出的弓箭的数量 没有限制 。 弓箭一旦被射出之后，可以无限地前进。
 * 给你一个数组 points ，返回引爆所有气球所必须射出的 最小 弓箭数 。
 *
 * https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/description/
 */

class Solution {
   public:
    /**
     * 重叠区间问题
     * 1. 按左区间排序
     * 2. 如果当前的区间与上个不重复，需要加一个弓箭
     * 3. 如果当前的区间与上个重复，则修改当前区间右边界为
     * 与上个区间的右边界的较小值
     */
    int findMinArrowShots(vector<vector<int>>& points) {
        int n = points.size();
        if (n == 0) return 0;
        auto compare = [](vector<int>& a, vector<int>& b) {
            return a[0] < b[0];
        };
        // 按左边界排序
        sort(points.begin(), points.end(), compare);
        // 默认为 1 第一个气球需要
        int ans = 1;
        // 从第1个开始遍历 看区间是否重复
        for (int i = 1; i < n; i++) {
            // 区间不重复 当前的左边界大于上一个的右边界 不重复
            if (points[i][0] > points[i - 1][1]) {
                ans++;
            } else {
                // 区间重复 当前区间右边界更新为当前和上一个右区间的较小值
                // 方便下一个区间计算是否能用同一支箭
                points[i][1] = min(points[i][1], points[i - 1][1]);
            }
        }
        return ans;
    }
};

int main() {
    Solution* solution = new Solution();
    vector<vector<vector<int>>> list = {{{10, 16}, {2, 8}, {1, 6}, {7, 12}},
                                        {{1, 2}, {3, 4}, {5, 6}, {7, 8}},
                                        {{1, 2}, {2, 3}, {3, 4}, {4, 5}}};
    for (int i = 0; i < list.size(); i++) {
        int ans = solution->findMinArrowShots(list[i]);
        cout << ans << endl;
    }
}