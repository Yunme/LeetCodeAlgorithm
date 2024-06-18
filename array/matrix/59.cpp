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
 * 59：螺旋矩阵II
 * 给你一个正整数 n ，生成一个包含 1 到 n^2
 * 所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。
 * https://leetcode.cn/problems/spiral-matrix-ii/description/
 *
 * 与 54 类似
 */
class Solution {
   public:
    vector<vector<int>> generateMatrix(int n) {
        int m = 0;
        vector<vector<int>> result(n, vector<int>(n));
        int left = 0, top = 0, right = n - 1, bottom = n - 1;
        while (left <= right && top <= right) {
            // 右  top,left -> top,right
            for (int i = left; i <= right; i++) {
                result[top][i] = ++m;
            }
            // 下 top+1,right -> bottom,right
            for (int i = top + 1; i <= bottom; i++) {
                result[i][right] = ++m;
            }

            if (top < bottom && left < right) {
                // 左 bottom,right-1 -> bottom,left+1
                for (int i = right - 1; i >= left + 1; i--) {
                    result[bottom][i] = ++m;
                }
                // 上 bottom,left -> top+1,left
                for (int i = bottom; i >= top + 1; i--) {
                    result[i][left] = ++m;
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
    int n = 2;
    vector<vector<int>> array = s->generateMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}