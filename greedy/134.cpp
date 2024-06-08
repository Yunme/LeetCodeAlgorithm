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
 * 134: 加油站
 * 在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。
 * 你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油
 * cost[i] 升。
 *
 * 你从其中的一个加油站出发，开始时油箱为空。
 *
 * 给定两个整数数组 gas 和 cost
 * ，如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1。
 * 如果存在解，则 保证 它是 唯一 的。
 *
 * gas.length == n
 * cost.length == n
 * https://leetcode.cn/problems/gas-station/description
 */

class Solution {
   public:
    /**
     * 法1：暴力法 双指针 O(n^2)
     * 从每一个加油站出发，进行尝试能否再次回到，不行则换下一个加油站出发
     * i 为当前出发的位置
     * j 为出发后每个加油站位置
     */
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        // if (gas.size() == 1) return gas[0] > cost[0] ? 0 : -1;
        int n = gas.size();
        // 从每个加油站出发，
        for (int i = 0; i < n; i++) {
            int j = i;
            int currentGas = 0;
            // 出发后计算能否到下一站
            // 循环次数为 n + 1 必须行驶一个环路，到达出发的位置，
            for (; j < n + i + 1; j++) {
                int k = j % n;  // 当前所在加油站
                cout << k << " ";
                if (j > i && k == i)
                    return i;  // 当出发后又到达出发点 i 说明可以完成，返回
                if (gas[k] == 0) continue;
                if (currentGas + gas[k] <
                    cost[k]) {  // 当前油量 + 加油站量 < 不能到达下一个
                    // 跳出，从下一个加油站尝试
                    break;
                }
                // 扣除花费
                currentGas -= cost[k];
                // 加油
                currentGas += gas[k];
            }
            cout << endl;
        }
        return -1;
    }

    /**
     * 法2：贪心 O(n)
     * 从某个站 x 开始最远能到达 y，说明此时总油量小于 cost[y], 不能再向前了
     * 说明从 x 到 y 中间的某站出发 都不能到达 y + 1，因为：
     * 每少一站，少了加油的机会，油量只会更少。
     * 下一步直接从 y + 1 开始，
     *
     * 只要所有站汽油总和 >= 消耗的汽油总和，那么肯定有解
     */
    int canCompleteCircuit2(vector<int>& gas, vector<int>& cost) {
        // 总油量
        int totalGas = 0;
        // 花费的量
        int totalCost = 0;
        // 当前的油量
        int currentGas = 0;
        int start = 0;  // 起始位置
        for (int i = 0; i < gas.size(); i++) {
            totalGas += gas[i];
            totalCost += cost[i];
            currentGas += gas[i] - cost[i];
            if (currentGas < 0) {  // 当前小于0 ，说明到达不了下一站，
                start = i + 1;   // 换下一个 i+1 出发
                currentGas = 0;  // 重置当前油量
            }
        }
        // 如果总油量小于总花费，那肯定到不了，否则就能绕一圈
        return totalGas < totalCost ? -1 : start;
    }
};

int main() {
    Solution* solution = new Solution();
    vector<vector<int>> gas = {{1, 2, 3, 4, 5}, {2, 3, 4}, {4}, {5}};
    vector<vector<int>> cost = {{3, 4, 5, 1, 2}, {3, 4, 3}, {5}, {4}};

    for (int i = 0; i < gas.size(); i++) {
        int ans = solution->canCompleteCircuit2(gas[i], cost[i]);
        cout << endl << "ans:";
        cout << ans << endl;
    }
}