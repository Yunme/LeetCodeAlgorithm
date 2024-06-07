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
 * 238:除自身以外数组的乘积
 *
 * 给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除
 * nums[i] 之外其余各元素的乘积 。
 * 题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32
 * 位整数范围内。
 *
 * 请 不要使用除法，且在 O(n) 时间复杂度内完成此题。
 *
 * 进阶：空间 O(1)
 * 2 <= nums.length <= 105
 * https://leetcode.cn/problems/product-of-array-except-self/description/
 */
class Solution {
   public:
    /**
     * 法1：前缀后缀 乘积预先存起来(自己实现)
     * 时空：O(n) 空间 O(n)
     */
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        // 前缀乘积 不包括当前元素
        // prefix[i] 表示 前i个元素的乘积，不包含i
        vector<int> prefix(n + 1, 1);  // 默认1
        prefix[1] = nums[0];
        for (int i = 2; i < n + 1; i++) {
            prefix[i] = nums[i - 1] * prefix[i - 1];
        }
        // suffix[i] 表示 j 以后的所有元素的乘积，不包含j
        vector<int> suffix(n + 1, 1);
        suffix[n] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            suffix[i] = nums[i + 1] * suffix[i + 1];
        }
        // for (auto i : prefix) {
        //     cout << i << " ";
        // }
        // cout << endl;
        // for (auto i : suffix) {
        //     cout << i << " ";
        // }
        // cout << endl;
        vector<int> ans(n);
        // 结果就是对应的前缀和后缀相乘
        for (int i = 0; i < n; i++) {
            ans[i] = prefix[i] * suffix[i];
        }
        return ans;
    }

    /**
     * 法2：前缀后缀 思想与上一致，只是空间压缩
     * 时空：O(n) 空间 O(1)
     */
    vector<int> productExceptSelf2(vector<int>& nums) {
        int n = nums.size();
        // 前缀乘积 不包括当前元素
        // prefix[i] 表示 前i个元素的乘积，不包含i

        // 前缀集合当作结果数组
        vector<int> ans(n, 1);  // 默认1
        for (int i = 1; i < n; i++) {
            ans[i] = nums[i - 1] * ans[i - 1];
        }
        // 在 ans 的基础上计算 后缀 并直接填入到结果
        int R = 1;  // 右边的乘积
        for (int i = n - 1; i >= 0; i--) {
            // 左边的乘积为 ans[i] 右边的乘积为 R
            ans[i] *= R;
            R *= nums[i];  // 右边的乘积更新
        }
        return ans;
    }

    /**
     * 法3：双指针解法
     * 时空：O(n) 空间 O(1)
     */
    vector<int> productExceptSelf3(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 1);
        int prefix = 1, suffix = 1;
        for (int i = 0, j = n - 1; i < n, j >= 0; i++, j--) {
            ans[i] *= prefix;
            ans[j] *= suffix;
            prefix *= nums[i];
            suffix *= nums[j];
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> array = {{1, 2, 3, 4}, {-1, 1, 0, -3, 3}};

    for (size_t i = 0; i < array.size(); i++) {
        vector<int> arr = s->productExceptSelf3(array[i]);
        for (auto j : arr) {
            cout << j << " ";
        }
        cout << endl;
    }
}