#include <math.h>

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
 * https://blog.csdn.net/qfc_128220/article/details/127914382
 *
 * 1.螺旋数字矩阵
 * 螺旋数字矩阵生成
 * 输入数字个数 n 和行数 m，生成m行矩阵；
 * 从左上角1开始，顺时针螺旋向内。
 * 1. 每行数字一样多；
 * 2. 列的数量尽可能少；
 * 3. 填充数字时优先填充外部；
 * 4. 数字不够时，用*代替
 * https://fcqian.blog.csdn.net/article/details/135085069
 * 类似于 https://leetcode.cn/problems/spiral-matrix-ii/description/
 */

/**
 * @param n n个数字
 * @param m m行
 */
vector<vector<string>> generate(int n, int m) {
    // 计算列
    int row = ceil((float)n / m);
    // cout << row;
    int j = 0;
    auto getNext = [&n, &j]() -> string {
        if (j < n) {
            return to_string(++j);
        }
        return "*";
    };
    vector<vector<string>> ans(m, vector<string>(row));
    int top = 0, left = 0, bottom = m - 1, right = row - 1;
    while (top <= bottom && left <= right) {
        // 右 top,left -> top,right
        for (int i = left; i <= right; i++) {
            ans[top][i] = getNext();
        }
        // 下 top+1,right -> bottom,right
        for (int i = top + 1; i <= bottom; i++) {
            ans[i][right] = getNext();
        }
        if (left < right && top < bottom) {
            // 左 bottom,right-1 -> bottom,left+1
            for (int i = right - 1; i >= left + 1; i--) {
                ans[bottom][i] = getNext();
            }
            // 上 bottom,left -> top+1,left
            for (int i = bottom; i >= top + 1; i--) {
                ans[i][left] = getNext();
            }
        }
        top++;
        left++;
        right--;
        bottom--;
    }
    return ans;
}

int main() {
    int n = 120;
    int m = 7;
    // cin >> n >> m;

    auto ans = generate(n, m);
    for (auto i : ans) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}