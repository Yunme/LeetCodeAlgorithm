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
 * 875：爱吃香蕉的珂珂
 * 珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i]
 * 根香蕉。警卫已经离开了，将在 h 小时后回来。 珂珂可以决定她吃香蕉的速度
 * k（单位：根/小时）。 每个小时，她将会选择一堆香蕉，从中吃掉 k
 * 根。如果这堆香蕉少于 k 根，
 * 她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉。珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。
 * 返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。
 * https://leetcode.cn/problems/koko-eating-bananas/description/
 *
 * 也就是说在 h 小时内，每个堆访问一次，最慢速度吃完这堆。在 h 小时内完成所有。
 */
class Solution {
   public:
    /**
     * h >= piles.length
     * 最小速度 k 代表 速度大于k肯定能吃完，小于k则吃不完；
     * k 最小为1，最大则为最多的那堆的个数。
     *
     * 二分查找从 1 到 最多的那个 逼近寻找
     * 如果在当前速度 s 下 h 小时内能吃掉所有，
     * 那么最小速度 k 一定 <= s，在下界查找;
     * 如果吃不掉，那么 k > s, 在上界寻找。
     */
    int minEatingSpeed(vector<int>& piles, int h) {
        //  下界
        int low = 1;
        int high = 0;
        for (int i : piles) {
            high = max(i, high);
        }
        if (h == piles.size()) return high;

        while (low < high) {
            int mid = (low + high) / 2;
            // 能吃掉
            if (canEating(mid, piles, h)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
    /**
     * 当速度为 speed 时，h小时内能不能吃完
     */
    bool canEating(int speed, vector<int>& piles, int h) {
        int hours = 0;
        for (int i : piles) {
            // 向上取整
            // 都是整数的情况下  等价于 (i + speed - 1) / speed
            // float 会溢出 精度不准 ceil((double)i / speed)
            hours += (i + speed - 1) / speed;
        }
        return hours <= h;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> array = {
        {3, 6, 7, 11}, {30, 11, 23, 4, 20}, {30, 11, 23, 4, 20}, {1000000000}};
    vector<int> target = {8, 5, 8, 2};

    for (size_t i = 0; i < array.size(); i++) {
        vector<int> arr = array[i];
        cout << s->minEatingSpeed(arr, target[i]) << endl;
    }
}