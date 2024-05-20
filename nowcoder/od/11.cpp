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
#include <set>
#include <sstream>
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
 * 11: 跳马问题
 * 输入 m 和 n 两个数，m 和 n 表示一个 m*n
 * 的棋盘。输入棋盘内的数据。棋盘中存在数字和"."两种字符，
 * 如果是数字表示该位置是一匹马，如果是"."表示该位置为空的，棋盘内的数字表示为该马能走的最大步数。
 *
 * 例如棋盘内某个位置一个数字为 k，表示该马只能移动 0~k 步的距离。
 * 棋盘内的马移动类似于中国象棋中的马移动，先在水平或者垂直方向上移动一格，然后再将其移动到对角线位置。
 * 棋盘内的马可以移动到同一个位置，同一个位置可以有多匹马。
 * 请问能否将棋盘上所有的马移动到同一个位置，若可以请输出移动的最小步数。若不可以输出0。
 *
 * https://blog.csdn.net/weixin_48157259/article/details/138081973
 *
 * 输入:
 * 第一行 m 和 n 两个数，m 和 n 表示一个 m*n 的棋盘。
 * m 行，每行 n 个数，表示棋盘内的数据。
 * 输出：
 * 最小移动步数。
 */

/**
 * 自己根据思路实现
*/
int minHorseMoveStep(int m, int n, vector<vector<int>> &matrix,
                     vector<pair<int, int>> &horsePos) {
    // 马的移动向量
    vector<pair<int, int>> nextWay = {{-1, -2}, {1, -2}, {2, -1}, {2, 1},
                                      {1, 2},   {-1, 2}, {-2, 1}, {-2, -1}};
    int horseCount = horsePos.size();
    vector<vector<vector<int>>> allHorseMat(horseCount);
    // 每匹马的可移动到的位置。
    for (int i = 0; i < horseCount; i++) {
        vector<vector<int>> horseMatrix(m, vector<int>(n, -1));
        auto initPos = horsePos[i];
        int k = matrix[initPos.first][initPos.second];
        vector<pair<int, int>> posList, nextPosList;
        horseMatrix[initPos.first][initPos.second] = 0;
        posList.push_back(initPos);
        for (int step = 1; step <= k; step++) {
            for (auto pos : posList) {
                for (auto w : nextWay) {
                    int y = pos.first + w.first;
                    int x = pos.second + w.second;
                    if (x < n && x >= 0 && y < m && y >= 0 &&
                        horseMatrix[y][x] == -1) {
                        horseMatrix[y][x] = step;
                        nextPosList.push_back({y, x});
                    }
                }
            }
            posList = nextPosList;
        }
        cout << "horseMatrix:" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << horseMatrix[i][j] << " ";
            }
            cout << endl;
        }
        allHorseMat[i] = horseMatrix;
    }

    // 所有马的可移动矩阵 叠加，
    // 1. 只有有一匹马不能到的点 -1，那么叠加结果为-1，表示有马到不了此点
    // 2. 所有马都能到达的点，步数相加。
    // 3. 最后找出最小步数的点
    // 叠加到第一个的矩阵上
    for (int k = 1; k < horseCount; k++) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int step = allHorseMat[k][i][j];
                // 0上的不能被覆盖
                if (step == -1 || allHorseMat[0][i][j] == -1) {
                    allHorseMat[0][i][j] = -1;
                } else {
                    allHorseMat[0][i][j] += step;
                }
            }
        }
    }
    // 找出结果矩阵 中最小的步数
    cout << "final matrix:" << endl;
    int minStep = INT_MAX;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int step = allHorseMat[0][i][j];
            if (step >= 0) {
                minStep = min(step, minStep);
            }
            cout << step << " ";
        }
        cout << endl;
    }
    return minStep == INT_MAX ? 0 : minStep;
}

int main() {
    // 行 列
    int m, n;
    cin >> m >> n;

    vector<vector<int>> matrix(m, vector<int>(n));
    string a;
    vector<pair<int, int>> horsePos;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a;
            if (a == ".") {
                matrix[i][j] = -1;
            } else {
                matrix[i][j] = stoi(a);
                horsePos.push_back({i, j});
            }
        }
    }

    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // for (auto i : horsePos) {
    //     cout << i.first << "," << i.second << endl;
    // }

    int ans = 0;
    if (horsePos.size() > 1) {
        ans = minHorseMoveStep(m, n, matrix, horsePos);
    }
    cout << ans << endl;
}

/**
 * 简洁代码版本
*/

const vector<pair<int, int>> DIRECTIONS = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

vector<vector<int>> bfs4SingleHorse(int i, int j, int m, int n, int step) {
    vector<vector<int>> mat(m, vector<int>(n, -1));
    mat[i][j] = 0;
    queue<pair<int, int>> q;
    q.push({i, j});
    int level = 0;

    while (!q.empty()) {
        level++;
        if (level > step) {
            break;
        }
        int qSize = q.size();
        for (int k = 0; k < qSize; k++) {
            pair<int, int> cur = q.front();
            q.pop();
            for (auto &dir : DIRECTIONS) {
                int ni = cur.first + dir.first;
                int nj = cur.second + dir.second;
                if (0 <= ni && ni < m && 0 <= nj && nj < n && mat[ni][nj] == -1) {
                    mat[ni][nj] = level;
                    q.push({ni, nj});
                }
            }
        }
    }

    cout << "horseMatrix:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    return mat;
}

int main2() {
    int m, n;
    cin >> m >> n;
    cin.ignore();

    vector<vector<string>> grid(m, vector<string>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    vector<vector<int>> ansMat(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != ".") {
                auto mat = bfs4SingleHorse(i, j, m, n, stoi(grid[i][j]));
                for (int x = 0; x < m; x++) {
                    for (int y = 0; y < n; y++) {
                        if (mat[x][y] == -1 || ansMat[x][y] == -1) {
                            ansMat[x][y] = -1;
                        } else {
                            ansMat[x][y] += mat[x][y];
                        }
                    }
                }
            }
        }
    }

    cout << "final matrix:" << endl;
    int ans = INT_MAX;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << ansMat[i][j] << " ";
            if (ansMat[i][j] != -1 && ans > ansMat[i][j]) {
                ans = ansMat[i][j];
            }
        }
        cout << endl;
    }

    cout << ((ans == INT_MAX) ? 0 : ans) << endl;
    return 0;
}
