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
 * 15. 灰度图恢复
 *
 * 输入一串数字数值以空格分隔
 * 前2个表示矩阵行数和列数，
 * 从第三个数开始，每两个数一组，
 * 每组第一个数是灰阶值，第二个数表示该灰阶值以左到右，
 * 从上到下（可理解为将二维数组按行存储在一维矩阵中)的连续像素个数。
 * 比如 255 34表示有连续34个像素的灰阶值是255。
 *
 * https://blog.csdn.net/weixin_48157259/article/details/138228427
 *
 * 输入:
 * 第一行：上述一串数字
 * 第二行：表示一个像素位置的行号和列号，如 0 0 表示左上角像素
 * 输出：
 * 一个数字，表示输入中指定像素的灰度值
 */

/**
 * 法1：自己实现
 * 直接二维数组模拟还原
 */
int getPixel(int m, int n, vector<pair<int, int>> list, pair<int, int> pos) {
    vector<vector<int>> matrix(m, vector<int>(n, -1));

    int counter = 0;
    int k = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            auto l = list[k];
            matrix[i][j] = l.first;
            counter++;
            if (counter >= l.second) {
                k++;
                counter = 0;
            }
            // cout << setw(4) << matrix[i][j] << " ";
        }
        // cout << endl;
    }

    return matrix[pos.first][pos.second];
}

int main() {
    string input;
    getline(cin, input);
    stringstream ss(input);

    string numStr;
    int m = 0, n = 0;
    vector<pair<int, int>> list;
    bool first = true;
    pair<int, int> p;
    while (getline(ss, numStr, ' ')) {
        int num = stoi(numStr);
        if (m == 0)
            m = num;
        else if (n == 0)
            n = num;
        else {
            if (first) {
                p = {num, -1};
            } else {
                p.second = num;
                list.push_back(p);
            }
            first = !first;
        }
    }
    int x, y;
    cin >> x >> y;

    int pixel = getPixel(m, n, list, {x, y});
    cout << pixel << endl;
}

/**
 * 法2：因为只需要目标位置的颜色
 * 所以根据矩阵宽高，可以计算出目标位置，距离开始有多少个，
 * 在根据距离推算出到这个位置时的颜色。
*/
int main2() {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);

    int n, m;
    iss >> n >> m;

    std::vector<int> nums;
    int num;
    while (iss >> num) {
        nums.push_back(num);
    }

    int r, c;
    std::cin >> r >> c;
    int idx = r * m + c + 1;

    int totalNum = 0;

    for (int i = 0; i < nums.size(); i += 2) {
        int val = nums[i];
        int num = nums[i + 1];
        totalNum += num;

        if (totalNum >= idx) {
            std::cout << val << std::endl;
            break;
        }
    }

    return 0;
}