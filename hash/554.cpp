#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 554：砖墙
 * 你的面前有一堵矩形的、由 n
 * 行砖块组成的砖墙。这些砖块高度相同（也就是一个单位高）但是宽度不同。每一行砖块的宽度之和相等。
 *
 * 你现在要画一条 自顶向下 的、穿过 最少
 * 砖块的垂线。如果你画的线只是从砖块的边缘经过，就不算穿过这块砖。你不能沿着墙的两个垂直边缘之一画线，这样显然是没有穿过一块砖的。
 *
 * 给你一个二维数组 wall ，该数组包含这堵墙的相关信息。其中，wall[i]
 * 是一个代表从左至右每块砖的宽度的数组。你需要找出怎样画才能使这条线
 * 穿过的砖块数量最少 ，并且返回 穿过的砖块数量 。
 *
 * 每行数之和都相等
 * https://leetcode.cn/problems/brick-wall/description/
 */
class Solution {
   public:
    /**
     * 法1：模拟（自己实现）O(n^2) 复杂度较高
     * 逐层累加寻找每个单位 经过的砖块数，到最后一行后，找出最小值
     */
    int leastBricks(vector<vector<int>>& wall) {
        int n = wall.size();
        int lineSum = 0;
        for (int i = 0; i < wall[0].size(); i++) {
            lineSum += wall[0][i];
        }
        // 数组记录每个单位后的是否有砖块。即每个单位是否正好是砖块缝隙
        // 并且按行累加
        vector<int> array(lineSum);
        for (int i = 0; i < wall.size(); i++) {
            int k = 1;
            // 遍历每行
            for (int j = 0; j < wall[i].size(); j++) {
                int width = wall[i][j];
                // 消耗大于 1 的 砖块
                for (int w = width; w > 1; w--) {
                    array[k]++;  // 每行累加
                    k++;
                }
                k++;
            }
            for (auto a : array) {
                cout << a << " ";
            }
            cout << endl;
        }
        // 找出最小的砖块数
        int ans = wall.size();
        for (int i = 1; i < lineSum; i++) {
            ans = min(array[i], ans);
        }
        cout << endl;
        return ans;
    }

    /**
     * 法2：哈希表法
     * 找缝隙，砖块边缘，找出最多缝隙位置，用高度减去就是砖块数
     */
    int leastBricks2(vector<vector<int>>& wall) {
        // map 存储每个缝隙的位置和个数
        // key 缝隙的位置：value 整面墙中对应位置缝隙的个数
        unordered_map<int, int> count;
        for (auto& w : wall) {
            int n = w.size();
            int sum = 0;
            for (int i = 0; i < n - 1; i++) {
                // 相对于开始的位置
                sum += w[i]; 
                // 每个砖块后有一个缝隙
                count[sum]++;
            }
        }

        // 找出最多的缝隙
        int maxCount = 0;
        for (auto& [k, v] : count) {
            // cout << k << ":" << v << endl;
            maxCount = max(v, maxCount);
        }
        // 高度 - 最多缝隙数 = 通过的最少砖块数
        return wall.size() - maxCount;
    }
};
int main() {
    Solution* s = new Solution();
    vector<vector<int>> array = {{1, 2, 2, 1}, {3, 1, 2}, {1, 3, 2},
                                 {2, 4},       {3, 1, 2}, {1, 3, 1, 1}};
    // array = {{1}, {1}, {1}};
    auto ans = s->leastBricks2(array);
    cout << ans << endl;
}