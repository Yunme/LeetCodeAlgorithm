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
 * 11：盛最多水的容器
 * 给定一个长度为 n 的整数数组 height 。有 n 条垂线，
 * 第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
 * 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
 * 返回容器可以储存的最大水量。 说明：你不能倾斜容器。
 * https://leetcode.cn/problems/container-with-most-water/description/
 */

class Solution {
   public:
    /**
     * 暴力法：
     */
    int maxArea(vector<int>& height) {
        int count = height.size();
        int maxWater = 0;
        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {
                int water = (j - i) * min(height[i], height[j]);
                maxWater = max(maxWater, water);
            }
        }
        return maxWater;
    }
    /**
     * 双指针
     * i：指向左侧
     * j：指向右侧
     * 计算当前容量；
     * 如果此时 i 处小，i++，否则 j--； 移动较小的那边。才有可能装更多的水
     */
    int maxArea2(vector<int>& height) {
        int count = height.size();
        int maxWater = 0;
        int i = 0, j = count - 1;
        while (i < j) {
            int water = (j - i) * min(height[i], height[j]);
            maxWater = max(maxWater, water);
            if (height[j] > height[i]) {
                i++;
            } else {
                j--;
            }
        }
        return maxWater;
    }
};

int main() {
    Solution* solution = new Solution();
    vector<vector<int>> array = {{1, 8, 6, 2, 5, 4, 8, 3, 7},
                                 {1, 1},
                                 {1, 2, 3, 4, 5, 6, 7, 8},
                                 {6, 5, 4, 3}};
    for (auto& i : array) {
        int ans = solution->maxArea2(i);
        cout << ans << endl;
    }
}