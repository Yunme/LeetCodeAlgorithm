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
 * 135:分发糖果
 * n 个孩子站成一排。给你一个整数数组 ratings 表示每个孩子的评分。
 * 你需要按照以下要求，给这些孩子分发糖果：
 * 每个孩子至少分配到 1 个糖果。
 * 相邻两个孩子评分更高的孩子会获得更多的糖果。
 *
 * 请你给每个孩子分发糖果，计算并返回需要准备的 最少糖果数目 。
 * https://leetcode.cn/problems/candy/description/
 */

class Solution {
   public:
    /**
     * 法1：O(n) O(n)
     * 左规则：a, b： 当 b 的评分大于 a 时，分给 b 比 a 的多
     * 右规则：a, b：当 a 的评分大于 b 时，分给 a 比 b 的多
     */
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> left(n, 1);
        // 左规则 左边的大
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) {
                left[i] = left[i - 1] + 1;
            }
        }
        // 右规则 右边的小
        int total = 0;
        vector<int> right(n, 1);
        for (int i = n - 1; i >= 0; i--) {
            if (i < n - 1 && ratings[i] > ratings[i + 1]) {
                right[i] = right[i + 1] + 1;
            }
            // 结果为 左右中的 大者
            total += max(left[i], right[i]);
        }
        return total;
    }

    /**
     * 法2：一次遍历 O(n)、O(1)
     * 递增序列，每次加1，
     *
     * 递减序列，第一个是1，如果没有后续，则结束
     * 如果有第二个递减，第二个应该是1，前一个应该是2，所以在上面基础上总数 +
     * 2； 1,2 == 2,1
     * 如果有第三个递减，第三个应该是1，第二个是2，第三个是3，所以在前面基础上 +
     * 3 1,2,3 == 3,2,1 每次加递减序列的个数
     *
     */
    int candy2(vector<int>& ratings) {
        int n = ratings.size();
        int ans = 1;
        int inc = 1; // 当前递增数量
        int dec = 0; // 当前递减数量
        int pre = 1; // 前一个值
        // 从 1 开始循环
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) { 
                // 比 前一个大，递增
                inc++;
                dec = 0;
                pre = inc; // 更新前一个
                ans += inc; // 累计到结果
            } else if (ratings[i] < ratings[i - 1]) {
                // 比前一个小，递减
                dec++;
                inc = 1;
                ans += dec; // 累计递减的个数
                if (dec >= pre) { 
                    // 递减序列个数 大于等于 递增个数，
                    // 之前的递增序列峰值就会等于或小于递减序列的第一个值，
                    // 调整每次递增序列峰值 + 1
                    ans++;
                }
            } else {
                inc = 1;
                dec = 0;
                pre = 1;
                ans++;
            }
        }
        return ans;
    }
};

int main() {
    Solution* solution = new Solution();
    vector<vector<int>> array = {{1, 0, 2}, {1, 2, 2}, {1, 3, 2, 2, 1}};

    for (int i = 0; i < array.size(); i++) {
        int ans = solution->candy2(array[i]);
        cout << endl << ans << endl;
    }
}