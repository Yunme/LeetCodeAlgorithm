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
 * 4.寻找两个正序数组的中位数
 * 给定两个大小分别为 m 和 n 的正序（从小到大）数组 num1 和 num2
 * 请找出并返回两个正序数组的中位数
 *
 * 算法复杂度应该是 O(log(m+n))
 * https://leetcode.cn/problems/two-sum/description/
 *
 * 最简单的：合并两个有序数组，之后找中间值，但是这样复杂度是 O(m+n)
 *
 * 要实现 O(log(m+n)) ，需要使用二分查找；
 * 这里其实就是要找第 k 小的数，k是两个数组长度之和的中间数（跟长度奇偶有关）
 */
class Solution {
   public:
    /**
     * 法1：二分查找第k小数 O(log(m+n))
     * 获取两个有序数组中第 k 小的数，注意 k 从 1 开始；
     * 要找第k小的元素，就取 pivot1=nums1[k/2-1] 和 pivot2=nums2[k/2-1] 比较
     * nums1 中小于等于 pivot1 的元素有 nums1[0..k/2-2] 共 k/2-1个
     * nums2 中小于等于 pivot2 的元素有 nums2[0..k/2-2] 共 k/2-1个
     * 取 pivot = min(pivot1,pivot2)，两个数组中小于等于 pivot
     *  的元素个数不会超过 (k/2-1) + (k/2-1) = k-2 个
     * 这样 pivot 本身也最大只能是第 k-1 小的元素
     * 如果 pivot = pivot1，那么 nums1[0..k/2-1] 都不可能是第k小的元素，都排除
     * 如果 pivot = pivot2，那么 nums2[0..k/2-1] 都不可能是第k小的严肃，都排除
     * 由于排除了一些元素（这些元素都比第 k 小的元素要小），
     * 因此 k 值变小，减去删除元素的个数
     */
    int getKthElement(const vector<int>& nums1, const vector<int>& nums2,
                      int k) {
        int size1 = nums1.size();
        int size2 = nums2.size();
        int index1 = 0, index2 = 0;
        while (true) {
            // 数组1 中都被排除，直接找数组2中的第k小，它的index 是 k-1
            if (index1 == size1) return nums2[index2 + k - 1];
            // 数组2 中都被排除，直接找数组1中的第k小，它的index 是 k-1
            if (index2 == size2) return nums1[index1 + k - 1];
            // k=1，找最小的数，两数组中的小者。
            if (k == 1) return min(nums1[index1], nums2[index2]);
            // 数组中index， 不能越界
            // 当前比较的两个数
            int newIndex1 = min(index1 + k / 2 - 1, size1 - 1);
            int newIndex2 = min(index2 + k / 2 - 1, size2 - 1);
            // 如果数组 1 里的较小，排除数组 1 里前面的数，index 指向下一个元素
            // 排除了 newIndex1 - index1 + 1 个数
            // k 值减少
            if (nums1[newIndex1] <= nums2[newIndex2]) {
                k -= newIndex1 - index1 + 1;
                index1 = newIndex1 + 1;
            } else {
                k -= newIndex2 - index2 + 1;
                index2 = newIndex2 + 1;
            }
        }
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int size = nums1.size() + nums2.size();
        if (size % 2 == 1)
            // 总个数为 奇数
            // 找第 (size + 1) / 2 小的数，比如 size = 5, 中位数是第3小
            return getKthElement(nums1, nums2, (size + 1) / 2);
        else
            // 总个数为 偶数
            // 两个中位数的平均数，比如 size = 6, 中位数是第3小和第4小的平均数
            return (getKthElement(nums1, nums2, size / 2) +
                    getKthElement(nums1, nums2, size / 2 + 1)) /
                   2.0;
    }

    /**
     * 法2：划分数组
     * 中位数定义：将一个集合划分成两个长度相等的子集，其中一个子集里的元素总是大于另一个子集中的元素
     * 所有中位数所在的位置，左边的都比右边的小。
     * 那么只需要在两个数组的合适的位置划分数组，使得左边的小于右边的；
     *
     * 特别的，数组1左边的都小于数组2右边的，数组2左边的都小于数组1右边的。
     * 现在就是需要找到这个划分的位置。使用二分查找
     * i + j = (m+n+1) / 2
     */
    double findMedianSortedArrays2(vector<int>& nums1, vector<int>& nums2) {
        // 确保数组1的长度较小
        if (nums1.size() > nums2.size()) {
            auto temp = nums1;
            nums1 = nums2;
            nums2 = temp;
        }
        int m = nums1.size();
        int n = nums2.size();
        int left = 0, right = m;
        int median1 = 0, median2 = 0;
        while (left <= right) {
            // 前部分：nums1[0..i-1] 和 nums2[0..j-1]
            // 后部分：nums1[i, m-1] 和 nums2[j, n-1]
            int i = (left + right) / 2;
            int j = (m + n + 1) / 2 -
                    i;  // 包含总长度奇偶处理 对于偶数+1不影响整除取值
            int nums1LeftMax = i == 0 ? INT_MIN : nums1[i - 1];
            int nums1RightMin = i == m ? INT_MAX : nums1[i];
            int nums2LeftMax = j == 0 ? INT_MIN : nums2[j - 1];
            int nums2RightMin = j == n ? INT_MAX : nums2[j];

            if (nums1LeftMax <= nums2RightMin) {
                median1 = max(nums1LeftMax, nums2LeftMax);
                median2 = min(nums1RightMin, nums2RightMin);
                left = i + 1;
            } else {
                right = i - 1;
            }
        }
        return (m + n) % 2 == 0 ? (median1 + median2) / 2.0 : median1;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> array1 = {{1, 3}, {1, 2}, {1, 3}};
    vector<vector<int>> array2 = {{2}, {3, 4}, {2, 4, 5, 6}};

    for (size_t i = 0; i < array1.size(); i++) {
        auto ans = s->findMedianSortedArrays2(array1[i], array2[i]);
        cout << ans << endl;
    }
}