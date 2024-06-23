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
 * 1049：最后一块石头的重量 II
 *
 * 有一堆石头，用整数数组 stones 表示。其中 stones[i] 表示第 i 块石头的重量。
 * 每一回合，从中选出任意两块石头，然后将它们一起粉碎。假设石头的重量分别为 x 和
 * y，且 x <= y。那么粉碎的可能结果如下： 如果 x ==
 * y，那么两块石头都会被完全粉碎； 如果 x != y，那么重量为 x
 * 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。 最后，最多只会剩下一块
 * 石头。返回此石头 最小的可能重量 。如果没有石头剩下，就返回 0。
 *
 * https://leetcode.cn/problems/last-stone-weight-ii/description/
 */
class Solution {
   public:
    /**
     * 要使撞击完剩余重量最小，那么每次挑选尽可能相近的石头
     * 也就是能否找到组合其重量为 sum / 2
     */
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        int sum = 0;
        for (int i : stones) {
            sum += i;
        }
        // 背包容量
        int target = sum / 2;
        // 选取 [0,i] 物品，容量为j 时, 其价值最大
        vector<int> dp(target + 1);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = target; j >= stones[i]; j--) {
                // 不选 还是上一行 dp[j]
                // 选 dp[j - stones[i]] + stones[i]
                dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
            }
        }
        // 最终重量为：
        // 容量为 target 时，重量即价值最大为 dp[target].
        // 剩余石头重量为 sum - dp[target];
        // 两堆石头撞击后 : sum - dp[target] - dp[target];
        return sum - dp[target] * 2;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{2, 7, 4, 1, 8, 1}, {31, 26, 33, 21, 40}};
    for (auto i : list) {
        int count = s->lastStoneWeightII(i);
        cout << count << endl;
    }
}