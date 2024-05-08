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
 * 912. 排序数组
 * https://leetcode.cn/problems/sort-an-array/description/
 */
class Solution {
   public:
    int quickPartition(vector<int> &nums, int low, int high) {
        // 基准 随机
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution dis(low, high);
        int random = dis(gen);
        swap(nums[low], nums[random]);

        int pivot = nums[low];

        int j = low;
        for (int i = low + 1; i <= high; i++) {
            if (nums[i] <= pivot) {
                j++;
                swap(nums[i], nums[j]);
            }
        }
        swap(nums[j], nums[low]);
        return j;
    }

    int quickPartitionDual(vector<int> &nums, int low, int high) {
        // 基准 随机
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution dis(low, high);
        int random = dis(gen);
        swap(nums[low], nums[random]);

        int pivot = nums[low];
        while (low < high) {
            // high 位置 >= 基准，排序满足， high--
            // 直到 high 位置 < 基准，跳出循环，high 位置的元素存到 low 位置。
            while (low < high && nums[high] >= pivot) high--;
            nums[low] = nums[high];
            // low 位置 <= 基准，排序满足，low++
            // 直到 low 位置 > 基准，跳出循环，low 位置的元素存到 high 位置
            while (low < high && nums[low] <= pivot) low++;
            nums[high] = nums[low];
        }
        // low 和 high 重合 位置就是基准排序位置。
        nums[low] = pivot;
        return low;
    }

    /**
     * 二路快排
     */
    void quickSort(vector<int> &nums, int low, int high) {
        if (low < high) {
            int pivotIndex = quickPartitionDual(nums, low, high);
            quickSort(nums, low, pivotIndex - 1);
            quickSort(nums, pivotIndex + 1, high);
        }
    }

    /**
     *  * 1. 当元素 < pivot，元素交换到 等于 pivot 区间的前一个位置
     * 2. 当元素 = pivot，什么都不做，看下一个元素
     * 3. 当元素 > pivot, 元素交换到大于 pivot 的前一个位置。
     */
    void quickSortThreeWay(vector<int> &nums, int low, int high) {
        if (low < high) {
            // 基准 随机
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution dis(low, high);
            int random = dis(gen);
            swap(nums[low], nums[random]);

            int pivot = nums[low];
            int lessThan = low;
            int greatThan = high;
            int i = low + 1;

            while (i <= greatThan) {
                if (nums[i] < pivot) {
                    // 小于基准值 跟小于的右边界交换
                    swap(nums[i], nums[lessThan]);
                    i++;
                    lessThan++;
                } else if (nums[i] > pivot) {
                    // 大于基准值 跟大于的左边界交换
                    swap(nums[i], nums[greatThan]);
                    greatThan--;
                } else {
                    i++;
                }
            }
            quickSortThreeWay(nums, low, lessThan - 1);
            quickSortThreeWay(nums, greatThan + 1, high);
        }
    }

    vector<int> sortArray(vector<int> &nums) {
        // quickSort(nums, 0, nums.size() - 1);
        quickSortThreeWay(nums, 0, nums.size() - 1);
        return nums;
    }
};

int main() {
    Solution *s = new Solution;
    int array[] = {3, 2, 2, 2, 2, 3, 2, 2, 4};
    vector<int> nums(array, array + size(array));
    s->sortArray(nums);
    for (int i : nums) {
        cout << i << " ";
    }
}