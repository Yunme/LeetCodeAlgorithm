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
 * 376: 摆动序列
 *
 * 如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为 摆动序列
 * 。第一个差（如果存在的话）可能是正数或负数。仅有一个元素或者含两个不等元素的序列也视作摆动序列。
 * 例如， [1, 7, 4, 9, 2, 5] 是一个 摆动序列 ，因为差值 (6, -3, 5, -7, 3)
 * 是正负交替出现的。 相反，[1, 4, 7, 2, 5] 和 [1, 7, 4, 5, 5]
 * 不是摆动序列，第一个序列是因为它的前两个差值都是正数，第二个序列是因为它的最后一个差值为零。
 * 子序列
 * 可以通过从原始序列中删除一些（也可以不删除）元素来获得，剩下的元素保持其原始顺序。
 * 给你一个整数数组 nums ，返回 nums 中作为 摆动序列 的 最长子序列的长度 。
 *
 * https://leetcode.cn/problems/wiggle-subsequence/description/
 */

class Solution {
   public:
    /**
     * 贪心思想
     */
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        // 1个时为摆动序列
        if (n < 2) return n;
        // 前一个摆动方向
        int preDiff = nums[1] - nums[0];
        int ans = preDiff != 0 ? 2 : 1;  // 不相等时 序列长度为2：否则为1
        for (int i = 2; i < n; i++) {
            int curDiff = nums[i] - nums[i - 1];
            // 前一个上升，当前下降
            // 或
            // 前一个下降，当前上升
            if (curDiff > 0 && preDiff <= 0 || curDiff < 0 && preDiff >= 0) {
                ans++;
                preDiff = curDiff;  // 只有方向发生变化时 更新
            }
        }
        return ans;
    }
};

int main() {
    Solution* solution = new Solution();
    vector<vector<int>> gg = {{1, 7, 4, 9, 2, 5}};
    for (int i = 0; i < gg.size(); i++) {
        int ans = solution->wiggleMaxLength(gg[i]);
        cout << ans << endl;
    }
}