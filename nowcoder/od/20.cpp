#include <math.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
// #include <sstream>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

/**
 * https://blog.csdn.net/weixin_48157259/article/details/138087531
 *
 * 20. 两个字符串间的最短路径
 * 给定两个字符串 A 和 B，根据两个字符串的长度，可以分为 m x n 的矩阵，
 * 从左上角 0,0 点，到终点 m,n 点，有不同的走法，
 * 当坐标中，两边字符不同时，只能走水平或垂直方向；
 * 当两边字符相同时，可以走斜边。
 * 看如何走，从源点到终点距离最短，最短距离是多少。
 * https://blog.csdn.net/weixin_48157259/article/details/139015764
 *
 * 输入:
 * 空格分割的两个字符串 A 和 B，都为大写字母
 * 输出：
 * 原点到终点的最短距离
 */

/**
 * 自己实现：动态规划
 *
 * 到每个点的最短路径 ：
 * 如果当前不是相等的字符，那么只能从上或左来
 * 最短路径就是到达上的最短路径与到达左的最短路径 + 1 = min(上, 左) + 1
 * 如果是相等的字符: = min(上, 左, 左上对角线) + 1
 */
int minDistance(string &a, string &b) {
    int m = a.length();
    int n = b.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i < m + 1; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j < n + 1; j++) {
        dp[0][j] = j;
    }
    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            // 比较的是前一个字符
            if (a[i - 1] != b[j - 1]) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;
            } else {
                dp[i][j] =
                    min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
            }
        }
    }

    for (int i = 0; i < m + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    return dp[m][n];
}

int main() {
    string A = "ABCABBA";
    string B = "CBABAC";
    cin >> A >> B;

    int ans = minDistance(A, B);
    cout << ans << endl;
}