#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <fstream>
#include <functional>
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
 * 455：分发饼干
 *
 * 假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。
 * 对每个孩子 i，都有一个胃口值
 * g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j，都有一个尺寸
 * s[j] 。 如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i
 * ，这个孩子会得到满足。
 * 你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。
 *
 * https://leetcode.cn/problems/assign-cookies/description/
 */

class Solution {
   public:
    /**
     * 贪心思想：
     * 两个数组从小到大排序
     * 尽可能恰好满足
     */
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int n = g.size();
        int m = s.size();
        int ans = 0;
        // 恰好满足
        int i = 0, j = 0;
        while (i < n && j < m) {
            // 当前饼干j大小 满足孩子i
            if (g[i] <= s[j]) {
                // 结果加1
                ans++;
                // 下一个孩子
                i++;
            }
            // 满足或不满足 都下一个饼干
            j++;
        }
        return ans;
    }
};

int main() {
    Solution* solution = new Solution();
    vector<vector<int>> gg = {{1, 2, 3}, {1, 2}, {10, 9, 8, 7}};
    vector<vector<int>> ss = {{1, 1}, {1, 2, 3}, {5, 6, 7, 8}};
    for (int i = 0; i < gg.size(); i++) {
        int ans = solution->findContentChildren(gg[i], ss[i]);
        cout << ans << endl;
    }
}