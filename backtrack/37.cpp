#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
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
 * 37: 解数独
 * 编写一个程序，通过填充空格来解决数独问题。
 * 数独的解法需 遵循如下规则：
 * 数字 1-9 在每一行只能出现一次。
 * 数字 1-9 在每一列只能出现一次。
 * 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
 * 数独部分空格内已填入了数字，空白格用 '.' 表示。
 *
 * https://leetcode.cn/problems/sudoku-solver/description/
 */
class Solution {
   public:
    /**
     * 只需要找到一个解后 返回
     */
    bool backtracking(vector<vector<char>> &board) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                // 当前是空格子
                if (board[i][j] == '.') {
                    // 尝试放入 1~9数字 字符
                    for (char k = '1'; k <= '9'; k++) {
                        // 如果满足 放入
                        if (check(board, i, j, k)) {
                            board[i][j] = k;
                            bool result = backtracking(board);
                            if (result) return true;
                            board[i][j] = '.';
                        }
                    }
                    // 放入 1~9都不符合
                    return false;
                }
            }
        }
        return true;
    }
    /**
     * 检查在 i，j处放置 k 是否符合数独
     */
    bool check(vector<vector<char>> &board, int row, int column, char k) {
        // 检查当前行
        for (int j = 0; j < 9; j++) {
            // 当前行已经有k
            if (board[row][j] == k) return false;
        }
        // 检查当前列
        for (int i = 0; i < 9; i++) {
            if (board[i][column] == k) return false;
        }
        // 检查当前 3x3
        int startRow = (row / 3) * 3;
        int startCol = (column / 3) * 3;
        for (int i = startRow; i < startRow + 3; i++) {  // 判断9方格里是否重复
            for (int j = startCol; j < startCol + 3; j++) {
                if (board[i][j] == k) {
                    return false;
                }
            }
        }
        return true;
    }
    void solveSudoku(vector<vector<char>> &board) {
        backtracking(board);
    }
};

int main() {
    Solution *s = new Solution();
    vector<vector<char>> list = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                 {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                 {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                 {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                 {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                 {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                 {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                 {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                 {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    // for (int i = 0; i < list.size(); i++) {
        s->solveSudoku(list);
        for (auto &i : list) {
            for (auto &j : i) {
                cout << j << ' ';
            }
            cout << endl;
        }
        cout << endl;
    // }
}