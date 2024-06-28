#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 977: 有序数组的平方
 *
 * 给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方
 * 组成的新数组，要求也按 非递减顺序 排序。
 *
 * https://leetcode.cn/problems/remove-duplicates-from-sorted-array/solutions
 */
class Solution {
   public:
    /**
     * O(n) O(1)
     * 双指针 类似于合并有序数组
     * 找到负数和正数边界
     */
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);

        int postive = n, negative = -1;
        // 找到正数和负数边界
        while (negative + 1 < n && nums[negative + 1] < 0) {
            negative++;
        }

        // // 直接这样好点
        // for (int i = 0; i < n; i++) {
        //     if (nums[i] < 0)
        //         negative = i;
        //     else
        //         break;
        // }

        // 正数索引 = 负数 + 1
        postive = negative + 1;
        cout << negative << " " << postive << endl;
        int k = 0;
        // 双指针向两侧
        while (postive < n && negative >= 0) {
            int pow1 = nums[postive] * nums[postive];
            int pow2 = nums[negative] * nums[negative];
            if (pow1 < pow2) {
                ans[k++] = pow1;
                postive++;
            } else {
                ans[k++] = pow2;
                negative--;
            }
        }
        for (int i = postive; i < n; i++) {
            ans[k++] = nums[i] * nums[i];
        }

        for (int i = negative; i >= 0; i--) {
            ans[k++] = nums[i] * nums[i];
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{-4, -1, 0, 3, 10},
                                {-7, -3, 2, 3, 11},
                                {1, 2, 3, 4},
                                {-4, -3, -2, -1},
                                {-3, 2}};

    for (int i = 0; i < list.size(); i++) {
        auto ans = s->sortedSquares(list[i]);
        for (int i : ans) {
            cout << i << " ";
        }
        cout << endl;
    }
}