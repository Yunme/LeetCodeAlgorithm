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
 * 54：螺旋矩阵
 * 给你一个 m 行 n 列的矩阵 matrix ，请按照顺时针螺旋顺序
 * ，返回矩阵中的所有元素。
 * https://leetcode.cn/problems/spiral-matrix/description/
 */
class Solution {
   public:
    /**
     * 自己模拟实现
     * 转圈，右 -> 下 -> 左 -> 上
     */
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) return {};
        if (matrix[0].empty()) return {};
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> result;
        int i = 0, j = 0;
        int k = 0;
        // 每转一圈 个数少一，前面加1
        while (m > i || n > j) {
            // 右
            j = k;
            if (j >= n) break;
            for (; j < n; j++) {
                result.push_back(matrix[i][j]);
                cout << "右:" << result.back() << "-->";
            }
            if (--j < 0 || ++i >= m) break;
            // 下
            for (; i < m; i++) {
                result.push_back(matrix[i][j]);
                cout << "下:" << result.back() << "-->";
            }
            if (--i < 0 || --j < k) break;
            // 左
            for (; j >= k; j--) {
                result.push_back(matrix[i][j]);
                cout << "左:" << result.back() << "-->";
            }
            // 左边+1
            k++;
            if (++j > n || --i < k) break;
            // 上
            for (; i >= k; i--) {
                result.push_back(matrix[i][j]);
                cout << "上:" << result.back() << "-->";
            }
            if (++i > m) break;
            // 个数少1
            m -= 1;
            n -= 1;
        }
        return result;
    }

    /**
     * 官方模拟实现
     * 简洁
     * 记录四个角，一圈一圈遍历
     * 左上角：top,left，右上角 top,right 右下角 bottom,right 左下角 bottom,left
     *
     * 遍历时，
     * 右： top,left 到 top,right，
     * 下： top+1,right 到 bottom,right
     * 如果 left < right 且 top < bottom;
     * 左： bottom,right-1 到 bottom,left+1
     * 上： bottom,left 到 top+1,left;
     * 遍历完后，left，top 加1，bottom，right 减1.
     */
    vector<int> spiralOrder2(vector<vector<int>>& matrix) {
        if (matrix.empty()) return {};
        if (matrix[0].empty()) return {};
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> result;

        int left = 0, top = 0, right = n - 1, bottom = m - 1;
        while (left <= right && top <= bottom) {
            // 右
            for (int i = left; i <= right; i++) {
                result.push_back(matrix[top][i]);
            }
            // 下
            for (int i = top + 1; i <= bottom; i++) {
                result.push_back(matrix[i][right]);
            }
            if (left < right && top < bottom) {
                // 左
                for (int i = right - 1; i >= left + 1; i--) {
                    result.push_back(matrix[bottom][i]);
                }
                // 上
                for (int i = bottom; i >= top + 1; i--) {
                    result.push_back(matrix[i][left]);
                }
            }
            left++;
            top++;
            right--;
            bottom--;
        }
        return result;
    }
};

int main() {
    Solution* s = new Solution();
    // vector<vector<int>> array = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int m = 10, n = 2;
    vector<vector<int>> array(m, vector<int>(n));
    int k = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            array[i][j] = ++k;
        }
    }

    auto result = s->spiralOrder2(array);
    cout << endl;
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i] << ", ";
    }
}