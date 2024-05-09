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
 * 88: 合并两个有序数组
 * https://leetcode.cn/problems/merge-sorted-array/description
 */
class Solution {
   public:
    /*
     * 正序：时间：O(m+n), 空间：O(m+n)
     */
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> nums(m + n);
        int a = 0, b = 0, c = 0;
        while (a < m && b < n) {
            if (nums1[a] < nums2[b]) {
                nums[c++] = nums1[a++];
            } else {
                nums[c++] = nums2[b++];
            }
        }
        if (a == m) {
            for (int i = b; i < n; i++) {
                nums[c++] = nums2[i];
            }
        } else {
            for (int i = a; i < m; i++) {
                nums[c++] = nums1[i];
            }
        }
        for (int i = 0; i < m + n; i++) {
            nums1[i] = nums[i];
        }
    }

    /*
     * 逆序：时间：O(m+n), 空间：O(1) 原地
     */
    void mergeReverse(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int a = m - 1, b = n - 1, c = m + n - 1;
        while (a >= 0 || b >= 0) {
            if (a == -1) {
                nums1[c--] = nums2[b--];
            } else if (b == -1) {
                nums1[c--] = nums1[a--];
            } else if (nums1[a] > nums2[b]) {
                nums1[c--] = nums1[a--];
            } else {
                nums1[c--] = nums2[b--];
            }
        }
    }

    /**
     * 逆序优化: num2 元素全部加入后，num1 中元素不需要再动
    */
    void mergeReverse2(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = nums1.size();
        while (n > 0) {
            if (m > 0 && nums1[m - 1] > nums2[n - 1]) {
                nums1[--i] = nums1[--m];
            } else {
                nums1[--i] = nums2[--n];
            }
        }
    }
};

int main() {
    Solution* s = new Solution();
    int array1[] = {2};
    int array2[] = {1};
    vector<int> v1(size(array1) + size(array2));
    for (int i = 0; i < size(array1); i++) {
        v1[i] = array1[i];
    }
    vector<int> v2(array2, array2 + size(array2));

    // s->merge(v1, size(array1), v2, size(array2));
    s->mergeReverse2(v1, size(array1), v2, size(array2));

    for (int i : v1) {
        cout << i << " ";
    }
}