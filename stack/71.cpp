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
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 71：简化路径
 * 给你一个字符串 path ，表示指向某一文件或目录的 Unix 风格 绝对路径 （以 '/'
 * 开头），请你将其转化为更加简洁的规范路径。 在 Unix
 * 风格的文件系统中，一个点（.）表示当前目录本身；此外，两个点 （..）
 * 表示将目录切换到上一级（指向父目录）；两者都可以是复杂相对路径的组成部分。
 * 任意多个连续的斜杠（即，'//'）都被视为单个斜杠
 * '/' 。 对于此问题，任何其他格式的点（例如，'...'）均被视为文件/目录名称。
 *
 * 请注意，返回的 规范路径 必须遵循下述格式：
 * 始终以斜杠 '/' 开头。
 * 两个目录名之间必须只有一个斜杠 '/' 。
 * 最后一个目录名（如果存在）不能 以 '/' 结尾。
 * 此外，路径仅包含从根目录到目标文件或目录的路径上的目录（即，不含 '.' 或
 * '..'）。 返回简化后得到的 规范路径 。
 *
 * https://leetcode.cn/problems/simplify-path/description
 */
class Solution {
   public:
    /**
     * 栈模拟 （自己实现）O(n) O(n)
     */
    string simplifyPath(string path) {
        int n = path.length();
        // 栈里存储的是每级路径 segment
        stack<string> stack;

        for (int i = 0; i < n; i++) {
            int start = i;
            // 找出下一个分隔符
            while (i < n && path[i] != '/') {
                i++;
            }
            if (i == start) {
                continue;
            }
            // 分隔符中间的就是 segment
            string segment = path.substr(start, i - start);
            cout << "seg:" << segment << endl;

            if (!stack.empty()) {
                // 如果是 . 当前目录，不处理
                if (segment == ".") {
                    continue;
                } else if (segment == "..") {
                    // 如果是 .. 上级目录，pop出上级目录
                    stack.pop();
                } else {
                    // 正常目录 入栈
                    stack.push(segment);
                }
            } else if (segment != "." && segment != "..") {
                // 正常目录 入栈
                stack.push(segment);
            }
        }

        // int i = 0;
        // while (i < n) {
        //     int start = i;
        //     while (i < n && path[i] != '/') {
        //         i++;
        //     }
        //     if (i == start) {
        //         i++;
        //         continue;
        //     }

        //     string segment = path.substr(start, i - start);
        //     cout << "seg:" << segment << endl;
        //     if (!stack.empty()) {
        //         if (segment == ".") {
        //             continue;
        //         }
        //         if (segment == "..") {
        //             stack.pop();
        //             continue;
        //         }
        //         if (!segment.empty()) {
        //             stack.push(segment);
        //         }

        //     } else if (segment != "." && segment != "..") {
        //         if (!segment.empty()) {
        //             stack.push(segment);
        //         }
        //     }
        //     i++;
        // }
        string ans;
        // 栈里 由后向前存储了各级目录
        // 拼接
        while (!stack.empty()) {
            string segment = stack.top();
            stack.pop();
            // 每级目录前拼接 /
            ans = '/' + segment + ans;
        }
        // 为空的话 还是在根目录
        return ans == "" ? "/" : ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<string> list = {"/home/", "/../", "/home//foo/", "/a/./b/../../c/"};

    for (auto& i : list) {
        auto ans = s->simplifyPath(i);
        cout << "ans:" << ans << endl;
    }
}