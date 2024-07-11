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
 * 240：搜索二维矩阵 II
 *
 * 编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target
 * 。该矩阵具有以下特性： 每行的元素从左到右升序排列。
 * 每列的元素从上到下升序排列。
 *
 * https://leetcode.cn/problems/search-a-2d-matrix-ii/description/
 * 类似：74 搜索二维矩阵
 */
class Solution {
   public:
    /**
     * 法1：排除法 Z字形 O(m + n)
     * 因为从左到右，从上到下递增
     * 从右上角开始寻找
     */
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
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
    vector<vector<vector<int>>> array = {{{1, 4, 7, 11, 15},
                                          {2, 5, 8, 12, 19},
                                          {3, 6, 9, 16, 22},
                                          {10, 13, 14, 17, 24},
                                          {18, 21, 23, 26, 30}},
                                         {{1, 4, 7, 11, 15},
                                          {2, 5, 8, 12, 19},
                                          {3, 6, 9, 16, 22},
                                          {10, 13, 14, 17, 24},
                                          {18, 21, 23, 26, 30}}};
    vector<int> targets = {5, 20};
    for (int i = 0; i < array.size(); i++) {
        bool ans = s->searchMatrix(array[i], targets[i]);
        cout << ans << endl;
    }
}