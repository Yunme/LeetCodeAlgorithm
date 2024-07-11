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
 * 74：搜索二维矩阵
 *
 * 给你一个满足下述两条属性的 m x n 整数矩阵：
 * 每行中的整数从左到右按非严格递增顺序排列。
 * 每行的第一个整数大于前一行的最后一个整数。
 * 给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。
 *
 * https://leetcode.cn/problems/search-a-2d-matrix/description/
 */
class Solution {
   private:
    int binarySearch(vector<int>& array, int target, int start, int end) {
        int low = start;
        int high = end;
        while (low < high) {
            int mid = (low + high) / 2;
            if (array[mid] == target) {
                return mid;
            } else if (array[mid] < target) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return -1;
    }

   public:
    /**
     * 法1：按行搜索每行 nLogN
     */
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (auto& list : matrix) {
            int index = binarySearch(list, target, 0, list.size());
            if (index >= 0) return true;
        }
        return false;
    }

    /**
     * 法2： 一次二分查找 O(log MN)
     * 因为这一行第一个数大于 上一行最后一个，
     * 所以按行拼接后时递增的
     */
    bool searchMatrix2(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        int low = 0, high = m * n;
        while (low < high) {
            // 摊平矩阵
            int mid = (low + high) / 2;
            // 定位元素
            int midVal = matrix[mid / n][mid % n];
            if (midVal == target) {
                return true;
            } else if (midVal < target) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return false;
    }

    /**
     * 法3：排除法 Z字形 O(m + n)
     * 因为从左到右，从上到下递增
     * 从右上角开始寻找
     */
    bool searchMatrix3(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        // 右上角
        int i = 0, j = n - 1;
        while (i < m && j >= 0) {
            if (matrix[i][j] == target) return true;
            if (matrix[i][j] < target) {
                // 当前行最后一个元素是当前行最大的元素  小于target
                // 排除 检查下一行
                i++;
            } else {
                // 当前行最后一个元素是当前行最大的元素 大于 target
                // 有可能在当前行
                // 逐列向左侧的列寻找
                j--;
            }
        }
        return false;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<vector<int>>> array = {
        {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}},
        {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}},
        {{1}}};
    vector<int> targets = {3, 13, 1};
    for (int i = 0; i < array.size(); i++) {
        bool ans = s->searchMatrix3(array[i], targets[i]);
        cout << ans << endl;
    }
}