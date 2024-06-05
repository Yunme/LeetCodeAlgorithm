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
 * 189: 轮转数组
 * 给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。
 *
 * 进阶：
 * 1.尽可能想出更多的解决方案
 * 2.空间复杂度O(1) 解决
 * https://leetcode.cn/problems/rotate-array/description/
 */
class Solution {
   public:
    /**
     * 法1：模拟法，每次右移一次，总共移动k次
     * 复杂度 O(k*n)
     */
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i < k; i++) {
            // 右移 从后向前遍历
            int last = nums[n - 1];  // 先保存最后一位
            for (int j = n - 1; j > 0; j--) {
                nums[j] = nums[j - 1];
            }
            // 最后一位赋值给第0位
            nums[0] = last;
        }
    }

    /**
     * 法2：新数组辅助空间
     */
    void rotate2(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> newArr(n);
        for (int i = 0; i < n; i++) {
            newArr[(i + k) % n] = nums[i];
        }
        nums.assign(newArr.begin(), newArr.end());
    }

    /**
     * 法3：翻转数组法
     * 因为 向右移动 k 次，尾部 k % n 个元素会到数组头部，其余元素向右移动 k % n
     *
     * 1. 翻转所有元素 [7,6,5,4,3,2,1] k = 3
     * 2. 翻转 [0, k mod n - 1] 区间元素 [5,6,7,4,3,2,1]
     * 3. 翻转 [k mod n, n - 1] 区间元素 [5,6,7,1,2,3,4]
     */
    void rotate3(vector<int>& nums, int k) {
        int n = nums.size();
        // k 可能大于n
        // k = k % n;
        reverse(nums, 0, n - 1);
        reverse(nums, 0, k % n - 1);
        reverse(nums, k % n, n - 1);
    }
    void reverse(vector<int>& nums, int start, int end) {
        while (start < end) {
            swap(nums[start], nums[end]);
            start++;
            end--;
        }
    }
    
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> array = {{1, 2, 3, 4, 5, 6, 7}, {-1, -100, 3, 99}};
    vector<int> count = {3, 2};

    for (size_t i = 0; i < array.size(); i++) {
        s->rotate3(array[i], count[i]);
        for (auto j : array[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
}