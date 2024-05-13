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
 * hj23 合唱队
 * 合唱队形：中间高，两边依次递减
 * 已知 n 位同学身高，计算最少需要几位同学出列，可以使得剩下的同学成合唱队形。
 * https://www.nowcoder.com/practice/05182d328eb848dda7fdd5e029a56da9
 *
 * 最长递增子序列问题
 */

/**
 * 求最长递增子序列 Longest Increasing Subsequence
 * 动态规划 时间复杂度 O(n^2)
 */
vector<int> LIS(vector<int> &nums) {
    // 表示 以i为结尾的最长递增子序列的长度。
    int n = nums.size();
    // 初始化为1，表示本身就是长度为1的子序列
    vector<int> dp(n, 1);

    // 每个元素左侧的最长递增
    // 以第i个元素为尾的最长递增序列 =
    // 从头开始遍历前 i-1 个元素，找到那个小于 i 元素中最大的元素，它的dp值 +
    // 1。
    // + 1就是加上当前元素，组成新的最长子序列。
    // 就是 i 的dp 值

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    return dp;
}

/**
 * 求最长递增子序列 Longest Increasing Subsequence
 * 二分查找 时间复杂度 O(nLogN)
 * 思想来源于纸牌游戏：
 * 思路是：
 * 1. 从前向后遍历数组，分堆堆放；
 * 2. 从左向右查找大于堆顶元素大于当前元素的堆；
 * 3. 如果没有大于堆顶元素的堆，那么则另起一个堆；
 * 4. 直到放完所有的数，堆的个数就是最长递增子序列的长度。
 * check
 * https://labuladong.online/algo/dynamic-programming/longest-increasing-subsequence-2/#%E4%BA%8C%E3%80%81%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE%E8%A7%A3%E6%B3%95
 */
vector<int> LIS2(vector<int> &nums) {
    // 牌堆的个数
    int heapCount = 0;
    // 初始化一个数组来存放堆，存放的是堆顶的元素。
    vector<int> heap(nums.size());

    // 存储每个元素 以当前元素为尾的最长递增子序列长度
    vector<int> result(nums.size());
    for (int i = 0; i < nums.size(); i++) {
        // 要放置的元素
        int poker = nums[i];
        // 由于堆顶元素是有序的，二分查找到要放置的位置
        int left = 0, right = heapCount;
        while (left < right) {
            int mid = (left + right) / 2;
            if (poker <= heap[mid]) {
                right = mid;
            } else if (poker > heap[mid]) {
                left = mid + 1;
            }
        }
        // 最后 left 与 right 相等；
        // 就是需要放置的位置，
        // 如果是最后一个位置，那么需要，说明没有找到比当前的小的，
        if (left == heapCount) {
            // 牌堆个数+1
            heapCount++;
        }
        // 放置。
        heap[left] = poker;
        // 因为堆顶是有序的，所以此时放置的位置 与前面堆顶就形成了递增子序列。
        // 于是，以当前位置为尾的最长递增子序列长度尾 left + 1.
        // cout << left + 1 << " ";
        result[i] = left + 1;
    }
    // cout << endl;
    return result;
}

/**
 * 队形
 * 出列后，剩下的元素形成的 小大小 长度最长。
 * 也就是
 * 对于每一个元素，左边比它小的递增的个数
 * +
 * 右边比它小的递减的个数之和最大，形成最长队形
 * 那么，剩下的人数就是要出列的最小。
 *
 * 转化为求数组中最长递增子序列。
 */
int x(vector<int> &nums) {
    int n = nums.size();

    // 每个元素前面的最长递增子序列
    vector<int> leftDP = LIS2(nums);

    // 每个元素后面的最长递减子序列；
    // = 数组逆序的最长递增
    // 反转后求最长递增子序列
    reverse(nums.begin(), nums.end());
    vector<int> rightDP = LIS2(nums);
    // 再反转回来
    reverse(rightDP.begin(), rightDP.end());

    // 对于每一个元素，左边比它小的递增的个数
    //
    // 右边比它小的递减的个数之和最大，形成最长队形
    int maxLength = 0;
    for (int i = 0; i < n; i++) {
        // 当前位置被算了两次，所以减1
        maxLength = max(maxLength, leftDP[i] + rightDP[i] - 1);
    }

    for (int i : leftDP) {
        cout << i << " ";
    }
    cout << endl;
    for (int i : rightDP) {
        cout << i << " ";
    }
    cout << endl;
    return n - maxLength;
}

int main() {
    int n = 0;
    // cin >> n;
    vector<int> nums = {186, 186, 150, 200, 160, 130, 197, 200};
    // vector<int> nums;
    // for (int i = 0; i < n; i++) {
    //     int m;
    //     cin >> m;
    //     nums.push_back(m);
    // }
    // LIS2(nums);
    cout << x(nums) << endl;
    return 0;
}