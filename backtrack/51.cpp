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
 * 51：N皇后
 *
 * 按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
 * n 皇后问题 研究的是如何将 n 个皇后放置在 n×n
 * 的棋盘上，并且使皇后彼此之间不能相互攻击。 给你一个整数 n ，返回所有不同的 n
 * 皇后问题 的解决方案。 每一种解法包含一个不同的 n 皇后问题
 * 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。
 *
 * https://leetcode.cn/problems/n-queens/description/
 */
class Solution {
   public:
    /**
     * 回溯
     * 树为 ：
     * 当前层 检查当前行的所有为止
     * 下一层 检查下一行
     */
    void backtrack(int n, int row, vector<string> &board,
                   vector<vector<string>> &ans) {
        if (row == n) {
            ans.push_back(board);
            return;
        }
        // 遍历当前行 所有格子，检测放入是否合法
        for (int i = 0; i < n; i++) {
            // 检查当前格子是否符合条件
            if (check(board, n, row, i)) {
                // 符合 放入
                board[row][i] = 'Q';
                // 下一行
                backtrack(n, row + 1, board, ans);
                // 回溯
                board[row][i] = '.';
            }
        }
    }
    /**
     * 检测把皇后放到 row，column 处是否合法
     * 行在递归时已经过滤了
     * 只需要检查列 和对角线
     */
    bool check(const vector<string> &board, int n, int row, int column) {
        // 检查 column 列
        // 只需要检查 row 行之上的，下面还没递归到
        for (int i = 0; i < row; i++) {
            if (board[i][column] == 'Q') return false;
        }
        // 检查正对角线 向左上方向，右下还没递归到
        for (int i = row - 1, j = column - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
        }
        // 检查 反对角线 向右上方向，左下还没递归到
        for (int i = row - 1, j = column + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') return false;
        }
        return true;
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> board(n, string(n, '.'));
        backtrack(n, 0, board, ans);
        return ans;
    }
};

int main() {
    Solution *s = new Solution();
    vector<int> list = {4, 1};
    for (auto &i : list) {
        auto ans = s->solveNQueens(i);
        for (auto &j : ans) {
            for (auto &k : j) {
                cout << k << " ";
            }
            cout << ",";
        }
        cout << endl;
    }
}