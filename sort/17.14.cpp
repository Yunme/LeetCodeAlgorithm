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
 * 17.14：最小k个数
 * 
 * 设计一个算法，找出数组中最小的k个数。以任意顺序返回这k个数均可。
 * https://leetcode.cn/problems/smallest-k-lcci/description/
 */
class Solution {
   public:
    /**
     * 基于快排思想 O(n) O(logN)
     */
    vector<int> smallestK(vector<int>& arr, int k) {
        quickSort(arr, 0, arr.size() - 1, k);
        // 查找第 k 小元素 就是排序后的第 k 个
        return vector<int>(arr.begin(), arr.begin() + k);
    }

    /**
     * 基准元素
     * 二路快排
     */
    int partition(vector<int>& arr, int left, int right) {
        int data = arr[left];
        while (left < right) {
            while (left < right && arr[right] >= data) {
                right--;
            }
            arr[left] = arr[right];
            while (left < right && arr[left] <= data) {
                left++;
            }
            arr[right] = arr[left];
        }
        arr[left] = data;
        return left;
    }
    void quickSort(vector<int>& arr, int left, int right, int k) {
        if (left >= right) return;
        int pivot = partition(arr, left, right);
        cout << pivot << endl;
        if (pivot == k) {  // 等于直接返回
            return;
        } else if (pivot > k) {  // pivot 较大，去左区间查找
            quickSort(arr, left, pivot - 1, k);
        } else {  // pivot 较小，去右区间查找
            quickSort(arr, pivot + 1, right, k);
        }
    }
};

int main() {
    Solution* s = new Solution;
    vector<vector<int>> list = {{1, 3, 5, 7, 2, 4, 6, 8}};
    vector<int> ks = {4};
    for (int i = 0; i < list.size(); i++) {
        auto ans = s->smallestK(list[i], ks[i]);
        for (auto j : ans) {
            cout << j << " ";
        }
        cout << endl;
    }
}