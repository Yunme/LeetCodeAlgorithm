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
 * 454：四数相加 II
 *
 * 给你四个整数数组 nums1、nums2、nums3 和 nums4 ，数组长度都是 n
 * ，请你计算有多少个元组 (i, j, k, l) 能满足： 0 <= i, j, k, l < n nums1[i] +
 * nums2[j] + nums3[k] + nums4[l] == 0
 *
 * https://leetcode.cn/problems/4sum-ii/description/
 */

class Solution {
   public:
    /**
     * 类似于 1.两数之和的 hash 解法
     */
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3,
                     vector<int>& nums4) {
        // 存储 num1 num2 中相加和的个数
        unordered_map<int, int> abMap;
        for (int i : nums1) {
            for (int j : nums2) {
                abMap[i + j]++;
            }
        }
        int ans = 0;
        for (int i : nums3) {
            for (int j : nums4) {
                // 目标
                int target = 0 - (i + j);
                if (abMap.find(target) != abMap.end()) {
                    ans += abMap[target];
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list1 = {{1, 2}, {0}};
    vector<vector<int>> list2 = {{-2, -1}, {0}};
    vector<vector<int>> list3 = {{-1, 2}, {0}};
    vector<vector<int>> list4 = {{0, 2}, {0}};

    for (int i = 0; i < list1.size(); i++) {
        auto ans = s->fourSumCount(list1[i], list2[i], list3[i], list4[i]);
        cout << ans << endl;
    }
}