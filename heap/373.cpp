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

#include "heap.cpp"
#include "heap.h"
using namespace std;

/**
 * 373: 查找和最小的 K 对数字
 * 给定两个以 非递减顺序排列 的整数数组 nums1 和 nums2 , 以及一个整数 k 。
 * 定义一对值 (u,v)，其中第一个元素来自 nums1，第二个元素来自 nums2 。
 * 请找到和最小的 k 个数对 (u1,v1),  (u2,v2)  ...  (uk,vk) 。
 *
 * https://leetcode.cn/problems/find-k-pairs-with-smallest-sums/description
 */

class Solution {
   public:
    /**
     * 小根堆优先队列
     * 最小的是 0,0, 其次是 1,0 或 0,1
     * 初始入堆 0,0
     * 其次入队 1,0 和 0,1 由最小堆保证小值在上
     * 使用 set 去重
     */
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2,
                                       int k) {
        int m = nums1.size();
        int n = nums2.size();
        // 队列里存储的是 一对元组，(u,v) u是 nums1里的索引，v是 nums2里的索引
        auto compare = [&](const pair<int, int>& p1, const pair<int, int>& p2) {
            // 两个元组之和 大小比较
            return nums1[p1.first] + nums2[p1.second] >
                   nums1[p2.first] + nums2[p2.second];
        };

        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       decltype(compare)>
            queue(compare);
        // set 用来去重
        // 例如对于 1,1 元组来说， 0,1 和 1,0 出队后都会加到队列里，1,1 元组重复
        auto pairHash = [](const pair<int, int>& p) {
            return p.first * 31 + p.second;
        };
        unordered_set<pair<int, int>, decltype(pairHash)> queuedSet(m * n,
                                                                    pairHash);
        // 0，0最小 入队
        queue.push({0, 0});
        queuedSet.insert({0, 0});

        vector<vector<int>> ans;
        while (!queue.empty() && k > 0) {
            auto top = queue.top();
            queue.pop();
            ans.push_back({nums1[top.first], nums2[top.second]});
            // 加入 i + 1, j
            if (top.first + 1 < m &&
                queuedSet.count({top.first + 1, top.second}) ==
                    0) {  // 确保数组范围
                queue.push({top.first + 1, top.second});
                queuedSet.insert({top.first + 1, top.second});
            }
            // 加入 i, j+1
            if (top.second + 1 < n &&
                queuedSet.count({top.first, top.second + 1}) == 0) {
                queue.push({top.first, top.second + 1});
                queuedSet.insert({top.first, top.second + 1});
            }
            k--;
        }
        return ans;
    }

    /**
     * 优先队列
     * 不用额外空间去重
     * 先将 nums1 的前 k 个元素入队
     */
    vector<vector<int>> kSmallestPairs2(vector<int>& nums1, vector<int>& nums2,
                                        int k) {
        int m = nums1.size();
        int n = nums2.size();
        // 队列里存储的是 一对元组，(u,v) u是 nums1里的索引，v是 nums2里的索引
        auto compare = [&](const pair<int, int>& p1, const pair<int, int>& p2) {
            // 两个元组之和 大小比较
            return nums1[p1.first] + nums2[p1.second] >
                   nums1[p2.first] + nums2[p2.second];
        };

        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       decltype(compare)>
            queue(compare);
        // i,0 提前入队
        for (int i = 0; i < min(m, k); i++) {
            queue.push({i, 0});
        }

        vector<vector<int>> ans;
        while (!queue.empty() && k > 0) {
            auto top = queue.top();
            queue.pop();
            ans.push_back({nums1[top.first], nums2[top.second]});
            // 只需要加入 i, j+1
            if (top.second + 1 < n) {
                queue.push({top.first, top.second + 1});
            }
            k--;
        }
        return ans;
    }
};

int main() {
    Solution* solution = new Solution();
    vector<vector<int>> list = {
        {1, 7, 11},      {2, 4, 6},    {1, 1, 2},       {1, 2, 3},
        {1, 2, 4, 5, 6}, {3, 5, 7, 9}, {0, 0, 0, 0, 0}, {-3, 22, 35, 56, 76}};
    vector<int> k = {3, 2, 20, 22};
    for (int i = 0; i < k.size(); i++) {
        auto ans = solution->kSmallestPairs2(list[2 * i], list[2 * i + 1], k[i]);
        for (auto& j : ans) {
            cout << "[ ";
            for (auto& k : j) {
                cout << k << " ";
            }
            cout << "]";
        }
        cout << endl;
    }
}