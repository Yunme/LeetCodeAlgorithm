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
 * 34.在排序数组中查找元素的第一个和最后一个位置
 * 在一个非递减顺序的数组 nums 中，找到 target，所在的开始位置和结束位置
 *
 * 如果不存在 返回[-1,-1]
 * 要求 O(logN) 复杂度
 * https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/description/
 */
class Solution {
   public:
    /**
     * 法1：二分查找 自己实现
     * 根据一般二分查找 找到 target 的左边界
     * 再从后逐个找，直到找到右边界
     * 这样当 target 在数组中很多时，退化到了 O(n)
     */
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty()) return {-1, -1};
        int low = 0;
        int high = nums.size() - 1;
        while (low < high) {
            int mid = (low + high) / 2;
            if (target <= nums[mid]) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        // low == high
        if (nums[low] == target) {
            int i = low + 1;
            while (i < nums.size() && nums[i] == target) i++;
            return {low, --i};
        }
        return {-1, -1};
    }

    /**
     * 法2：两次二分查找
     * 题目其实让我们找的是 target 的左边界 和 大于target数的左边界 - 1.
     * 这样可以用两次二分查找来解决
     */
    /**
     * 在有序数组中找 target，返回其索引
     * @param low true 时代表左边界，false 代表右边界
     */
    int binarySearch(vector<int>& nums, int target, bool lower) {
        int low = 0;
        int high = nums.size();
        while (low < high) {
            int mid = (low + high) / 2;
            // 有等号 左边界
            if (lower && target <= nums[mid] || target < nums[mid]) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
    vector<int> searchRange2(vector<int>& nums, int target) {
        if (nums.empty()) return {-1, -1};
        int leftIndex = binarySearch(nums, target, true);
        int rightIndex = binarySearch(nums, target, false) - 1;
        if (leftIndex <= rightIndex && rightIndex < nums.size() &&
            nums[leftIndex] == target && nums[rightIndex] == target) {
            return {leftIndex, rightIndex};
        }
        return {-1, -1};
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> array = {
        {5, 7, 7, 8, 8, 10}, {5, 7, 7, 8, 8, 10}, {1}, {}};
    vector<int> target = {8, 6, 1, 0};

    for (size_t i = 0; i < array.size(); i++) {
        vector<int> arr = array[i];
        auto ans = s->searchRange2(arr, target[i]);
        cout << ans[0] << "," << ans[1] << endl;
    }
}