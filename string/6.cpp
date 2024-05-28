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
#include <sstream>
#include <stack>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 6: Z 字形变换
 * 将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z
 * 字形排列。
 * 比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * 之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。
 * https://leetcode.cn/problems/zigzag-conversion/description/
 */

class Solution {
   public:
    /**
     * 法1：二维数组模拟 自己实现
     * 创建二维数组，在矩阵上填写字符串，最后逐行拼接非空字符，返回
     * 以 （下，斜上） 为一个周期，n 为行数，
     * 每个周期填写了 t = (n + n - 2) = 2n-2 个；
     * 每个周期占用了 n - 1 列，
     * 所以整个周期有 len / t 个周期（最后一个可能不满），
     * 所以列数 = (n - 1) * len / t.
     */
    string convert(string s, int numRows) {
        int len = s.length();
        // 只有 1 行的或只有 1 列的直接返回原字符串
        if (numRows >= len || numRows == 1) return s;
        int column = (numRows - 1) * len / (2 * numRows - 2);
        vector<vector<char>> matrix(numRows, vector<char>(column));

        // 填充法1：遍历每列
        // int a = 0;
        // for (int j = 0; j < column; j++) {
        //     // 从上到下
        //     for (int i = 0; i < numRows; i++) {
        //         if (a < len) matrix[i][j] = s[a++];
        //     }
        //     // 从坐下 到 右上
        //     for (int i = 1; i < numRows - 1; i++) {
        //         j++;
        //         if (a < len) matrix[numRows - 1 - i][j] = s[a++];
        //     }
        // }

        // 填充法2：
        // 遍历字符串，当前下标i满足 i % (t = n * 2 - 2) < (n - 1)
        // 则向下，否则右上。
        int x = 0, y = 0;
        for (int i = 0; i < len; i++) {
            matrix[x][y] = s[i];
            if (i % (numRows * 2 - 2) < numRows - 1) {
                x++;
            } else {
                x--;
                y++;
            }
        }

        string ans;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < column; j++) {
                if (matrix[i][j]) {
                    ans += matrix[i][j];
                }
                cout << setw(2) << matrix[i][j] << " ";
            }
            cout << endl;
        }
        return ans;
    }

    /**
     * 法2：直接构造法 简介版本
     * 还是构造二维数组，只不过是一个字符串列表，
     * 整个 Z 字形变换，相当于是对外层数组进行循环访问，
     * 0 1 2 3，(2 1)，0 1 2 3，(2 1)，...
     * 每一次访问拼接当前字符到对应的数组的字符串中
     */
    string convert2(string s, int numRows) {
        if (numRows > s.length() || numRows == 1) return s;
        vector<string> rows(numRows);

        int i = 0, flag = -1;
        for (char c : s) {
            rows[i] += c;
            // i 到 顶部 或者到 底部，转向循环
            if (i == 0 || i == numRows - 1) {
                flag = -flag;
            }
            i += flag;
        }

        string ans;
        for (const auto& c : rows) {
            ans += c;
        }
        return ans;
    }
};

int main() {
    Solution* solution = new Solution();
    vector<string> arr = {"PAYPALISHIRING", "PAYPALISHIRING", "A", "ABCDEFG",
                          "AB"};
    vector<int> rows = {3, 4, 1, 5, 1};
    for (int i = 0; i < arr.size(); i++) {
        auto ans = solution->convert2(arr[i], rows[i]);
        cout << ans << endl;
    }
    return 0;
}