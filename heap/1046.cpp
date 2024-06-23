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

#include "heap.h"
#include "heap.cpp"
using namespace std;

/**
 * 1046: 最后一块石头的重量
 * 有一堆石头，每块石头的重量都是正整数。
 * 每一回合，从中选出两块 最重的 石头，然后将它们一起粉碎。假设石头的重量分别为
 * x 和 y，且 x <= y。那么粉碎的可能结果如下：
 *
 * 如果 x == y，那么两块石头都会被完全粉碎；
 * 如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。
 * 最后，最多只会剩下一块石头。返回此石头的重量。如果没有石头剩下，就返回 0。
 * https://leetcode.cn/problems/last-stone-weight/description/
 */

class Solution {
   public:
    /**
     * 使用优先队列 （自己实现）
     * 使用系统类
     *
     * 队头的大值 出队两个，
     * 相等的话，都已出队；
     * 否则大的减去小后的差再入队
     */
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> queue;
        for (int i : stones) {
            queue.push(i);
        }
        while (queue.size() > 1) {
            int top1 = queue.top();
            queue.pop();
            int top2 = queue.top();
            queue.pop();
            // cout << top1 << " " << top2 << endl;
            if (top1 > top2) {  // 肯定是 top1 大或相等
                // top1 大 差值再入队
                top1 = top1 - top2;
                queue.push(top1);
            }
            // 相等的话 都出队
        }
        // 最后剩余 1个的话 返回，否则 返回 0
        return queue.size() > 0 ? queue.top() : 0;
    }

    /**
     * 自己实现一个大根堆 （自己实现）
     *
     * 队头的大值 出队两个，
     * 相等的话，都已出队；
     * 否则大的减去小后的差再入队
     */
    int lastStoneWeight2(vector<int>& stones) {
        Heap queue(stones);
        while (queue.size() > 1) {
            int top1 = queue.top();
            queue.pop();
            int top2 = queue.top();
            queue.pop();
            cout << top1 << " " << top2 << endl;
            if (top1 > top2) {  // 肯定是 top1 大或相等
                // top1 大 差值再入队
                top1 = top1 - top2;
                queue.push(top1);
            }
            // 相等的话 都出队
        }
        // 最后剩余 1个的话 返回，否则 返回 0
        return queue.size() > 0 ? queue.top() : 0;
    }
};

int main() {
    Solution* solution = new Solution();
    vector<vector<int>> list = {
        {2, 7, 4, 1, 8, 1}, {191, 193, 552, 881, 68,  337, 209, 749, 58,  923,
                             300, 43,  121, 185, 977, 454, 151, 83,  97,  282,
                             561, 58,  692, 550, 949, 931, 465, 29,  295, 412}};
    for (int i = 0; i < list.size(); i++) {
        auto l = list[i];
        auto ans = solution->lastStoneWeight2(l);
        cout << ans << endl;
    }
}