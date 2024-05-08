/// @brief
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
 * 215: 数组中的第 k 个最大元素 （eg:最大的，第1大，次大，第2大）
 * https://leetcode.cn/problems/kth-largest-element-in-an-array/description/
 */
class Solution {
   public:
    // 二路快排
    int partition(vector<int> &nums, int low, int high) {
        // 基准 随机
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution dis(low, high);
        int random = dis(gen);
        swap(nums[low], nums[random]);
        int pivot = nums[low];
        while (low < high) {
            while (low < high && nums[high] >= pivot) --high;
            nums[low] = nums[high];
            while (low < high && nums[low] <= pivot) ++low;
            nums[high] = nums[low];
        }
        nums[low] = pivot;
        return low;
    }

    int quickSelect(vector<int> &nums, int left, int right, int k) {
        int pivotIndex = partition(nums, left, right);
        // 快排中，基数元素的排序位置已经确定
        if (pivotIndex == k) {
            // 直接找到返回
            return nums[k];
        } else if (k < pivotIndex) {
            // k 比 基数index 小，去基数左边找
            return quickSelect(nums, left, pivotIndex - 1, k);
        }
        // k 比 基数index 大，去基数右边找
        return quickSelect(nums, pivotIndex + 1, right, k);
    }

    int findKthLargest(vector<int> &nums, int k) {
        // 第 k 大，为排序后的数组的index = n-k
        // 比如 [1,2,3] 第1大为3=3-1=2 ..
        if (k <= 0 || k > nums.size()) {
            return -1;
        }

        return quickSelect(nums, 0, nums.size() - 1, nums.size() - k);
    }
};

int main() {
    Solution *s = new Solution;
    int array[] = {0};
    vector<int> nums(array, array + size(array));
    int val = s->findKthLargest(nums, 0);
    printf("%d\n", val);
}