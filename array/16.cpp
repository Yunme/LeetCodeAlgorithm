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
 * 16：最接近的三数之和
 * https://leetcode.cn/problems/3sum-closest/description/
 */
class Solution {
   public:
    /**
     * 暴力大法
     * 时间复杂度：O(n^3)
     */
    int threeSumClosest(vector<int>& nums, int target) {
        // for (int i : nums) {
        //     cout << i << " ";
        // }
        // cout << endl;
        int closest = nums[0] + nums[1] + nums[2];
        for (int i = 0; i < nums.size(); i++) {
            int a = nums[i];
            for (int j = i + 1; j < nums.size(); j++) {
                for (int k = j + 1; k < nums.size(); k++) {
                    int sum = a + nums[j] + nums[k];
                    if (abs(sum - target) < abs(closest - target)) {
                        closest = sum;
                    }
                }
            }
        }
        return closest;
    }

    /**
     * 时间复杂度 O(n^2)
     * 排序后 从小到大 遍历寻找，
     * 
     * 当前值位置是a：i
     * 慢指针b：i+1 递增 此时最小，
     * 快指针c: n-1 递减 此时最大
     * 如果 a+b+c 大于 target, 说明 c 过大，c--;
     * 如果 小于 target，说明  b 过小，b++；
     */
    int threeSumClosest2(vector<int>& nums, int target) {
        // 排序
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int closest = nums[0] + nums[1] + nums[2];

        for (int i = 0; i < n - 2; i++) {
            // 跟上次一样，遍历过了，跳过
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            // 从后的区间内寻找两个
            // left 处最小，right 处最大
            int left = i + 1, right = n - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                // 等于目标值直接返回
                if (sum == target) {
                    return target;
                }

                // 如果此时
                if (abs(closest - target) > abs(sum - target)) {
                    closest = sum;
                }
                if (sum < target) {
                    // 如果此时和小于target，因为是排序过的，所以left+1，寻找下一个接近的。
                    // 找到下个不相等的数 相等的没比要再试
                    int left1 = left + 1;
                    while (left1 < right && nums[left1] == nums[left]) {
                        left1++;
                    }
                    left = left1;
                } else {
                    // 如果此时和大于target，因为是排序过的，所以right-1，寻找下一个接近的。
                    // 找到下个不相等的数 相等的没比要再试
                    int right1 = right - 1;
                    while (right1 > left && nums[right1] == nums[right]) {
                        right1--;
                    }
                    right = right1;
                }
            }
        }
        return closest;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> array = {{-1, 2, 1, -4},
                                 {0, 0, 0},
                                 {3, 9, 4, 8, 6, 7, 4, 67, 12},
                                 {0, 1, 2},
                                 {4, 0, 5, -5, 3, 3, 0, -4, -5},
                                 {0, 3, 97, 102, 200}};
    vector<int> target = {1, 10000, 45, 0, -2, 300};

    for (size_t i = 0; i < array.size(); i++) {
        vector<int> arr = array[i];
        cout << s->threeSumClosest2(arr, target[i]) << endl;
    }
}