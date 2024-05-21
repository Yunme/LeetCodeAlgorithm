#include <math.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
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
 * 22. 掌握单词个数
 * 在一个机房中，服务器的位置标识在 n*m
 * 的整数矩阵网格中，1表示单元格上有服务器，0 表示没有。
 * 如果两台服务器位于同一行或者同一列中紧邻的位置，则认为它们之间可以组成一个局域网。
 * 请你统计机房中最大的局域网包含的服务器个数。
 *
 * https://blog.csdn.net/weixin_48157259/article/details/138868772
 *
 * 输入:
 * 第一行：n 和 m
 * n * m 的二维数组，代表服务器信息
 * 输出：
 * 最大局域网包含的服务器个数
 */

/**
 * BFS 自己实现
 */
int maxLanCount(int m, int n, vector<vector<int>> &matrix,
                vector<pair<int, int>> &lanPosList) {
    vector<vector<int>> visited(m, vector<int>(n));
    int ans = 0;
    queue<pair<int, int>> queue;
    for (auto p : lanPosList) {
        int temp = 0;
        if (matrix[p.first][p.second] == 2) {
            continue;
        }
        queue.push(p);
        matrix[p.first][p.second] = 2;
        while (!queue.empty()) {
            auto front = queue.front();
            queue.pop();
            temp++;
            int top = front.first - 1;
            if (top >= 0 && matrix[top][front.second] == 1) {
                queue.push({top, front.second});
                matrix[top][front.second] = 2;
            }
            int left = front.second - 1;
            if (left >= 0 && matrix[front.first][left] == 1) {
                queue.push({front.first, left});
                matrix[front.first][left] = 2;
            }
            int bottom = front.first + 1;
            if (bottom < m && matrix[bottom][front.second] == 1) {
                queue.push({bottom, front.second});
                matrix[bottom][front.second] = 2;
            }
            int right = front.second + 1;
            if (right < n && matrix[front.first][right] == 1) {
                queue.push({front.first, right});
                matrix[front.first][right] = 2;
            }
        }
        ans = max(ans, temp);
    }
    return ans;
}

/**
 * BFS 2
 */
vector<pair<int, int>> DIRECTIONS = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int maxLanCount2(int m, int n, vector<vector<int>> &matrix,
                 vector<pair<int, int>> &lanPosList) {
    vector<vector<int>> visited(m, vector<int>(n));
    int ans = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1 && visited[i][j] == 0) {
                int temp = 0;
                queue<pair<int, int>> queue;
                queue.push({i, j});
                visited[i][j] = 1;
                while (!queue.empty()) {
                    auto front = queue.front();
                    queue.pop();
                    // if (visited[front.first][front.second] == 0) {
                    // visited[front.first][front.second] = 1;
                    temp++;
                    // }
                    for (auto dir : DIRECTIONS) {
                        int x_next = front.first + dir.first;
                        int y_next = front.second + dir.second;
                        if (x_next >= 0 && x_next < m && y_next >= 0 &&
                            y_next < n && visited[x_next][y_next] == 0 &&
                            matrix[x_next][y_next] == 1) {
                            queue.push({x_next, y_next});
                            visited[x_next][y_next] = 1;
                        }
                    }
                }
                ans = max(ans, temp);
            }
        }
    }
    return ans;
}

/**
 * DFS 递归版，代码简洁 迭代版本就是把 BFS 的队列改成栈
 */

void dfs(int i, int j, int m, int n, vector<vector<int>> &matrix, int &area,
        vector<vector<int>> &visited) {
    visited[i][j] = 1;
    area++;

    for (auto dir : DIRECTIONS) {
        int nextI = i + dir.first;
        int nextJ = j + dir.second;
        if (nextI >= 0 && nextI < m && nextJ >= 0 && nextJ < n &&
            !visited[nextI][nextJ] && matrix[nextI][nextJ] == 1) {
            dfs(nextI, nextJ, m, n, matrix, area, visited);
        }
    }
}

int dfsHelper(int m, int n, vector<vector<int>> &matrix) {
    vector<vector<int>> visited(m, vector<int>(n));
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 1 && !visited[i][j]) {
                int area = 0;
                dfs(i, j, m, n, matrix, area, visited);
                ans = max(ans, area);
            }
        }
    }
    return ans;
}

int main() {
    int m, n;
    cin >> m >> n;
    cin.ignore();

    vector<pair<int, int>> lanPosList;
    vector<vector<int>> matrix(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
            if (matrix[i][j]) {
                lanPosList.push_back({i, j});
            }
        }
        cin.ignore();
    }

    // cout << endl;
    // int ans = maxLanCount(m, n, matrix, lanPosList);
    int ans = dfsHelper(m, n, matrix);
    cout << ans << endl;
}