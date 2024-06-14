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
 * 79: 单词搜索
 * 给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word
 * 存在于网格中，返回 true ；否则，返回 false 。
 *
 * 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
 * 同一个单元格内的字母不允许被重复使用。
 *
 * https://leetcode.cn/problems/word-search/description/
 */
class Solution {
   public:
    /**
     * 回溯
     */
    // 四个方向向量
    vector<pair<int, int>> direct = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    bool backtracking(vector<vector<char>> &board, vector<vector<int>> &used,
                      int i, int j, int index, string &word) {
        char c = word[index];
        // 当前字符 与 矩阵不同，返回 false
        if (c != board[i][j]) {
            return false;
        }
        // 当前位与矩阵 i，j 处相等，到达最后一位，返回 true
        if (index == word.length() - 1) {
            return true;
        }

        used[i][j] = 1;
        bool result = false;
        // 遍历当前位置的 四个方向
        for (auto &d : direct) {
            int newI = i + d.first;
            int newJ = j + d.second;
            if (newI >= 0 && newI < board.size() && newJ >= 0 &&
                newJ < board[0].size()) {  // 检查是否越界
                // 如果没被访问到
                if (!used[newI][newJ]) {
                    // 且下一位 与 单词下一位相等。
                    if (backtracking(board, used, newI, newJ, index + 1,
                                     word)) {
                        // 结果设为 true
                        result = true;
                    }
                }
            }
        }
        // 回溯
        cout << "back:" << i << "," << j << endl;
        used[i][j] = 0;
        return result;
    }

    bool exist(vector<vector<char>> &board, string word) {
        int m = board.size();
        int n = board[0].size();
        // 访问数组
        vector<vector<int>> used(m, vector<int>(n, 0));

        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                // 找到第一个与首位相同的
                if (board[i][j] == word[0]) {
                    cout << "start:" << i << "," << j << endl;
                    if (backtracking(board, used, i, j, 0, word)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

int main() {
    Solution *s = new Solution();
    vector<vector<vector<char>>> list = {
        {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
        {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
        {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
        {{'C', 'A', 'A'}, {'A', 'A', 'A'}, {'B', 'C', 'D'}}};

    vector<string> words = {"ABCCED", "SEE", "ABCB", "AAB"};

    for (int i = 0; i < list.size(); i++) {
        auto ans = s->exist(list[i], words[i]);
        cout << ans << endl;
    }
}