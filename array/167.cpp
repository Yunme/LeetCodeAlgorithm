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
 * 167: 两数之和II - 输入有序数组
 * 给你一个下标从 1 开始的整数数组 numbers ，该数组已按 非递减顺序排列  ，
 * 请你从数组中找出满足相加之和等于目标数 target 的两个数
 *
 * 以长度为 2 的整数数组 [index1, index2] 的形式返回这两个整数的下标 index1 和
 * index2。
 *
 * 你可以假设每个输入 只对应唯一的答案 ，而且你 不可以 重复使用相同的元素。
 * 你所设计的解决方案必须只使用常量级的额外空间。
 * https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/description/
 */
class Solution {
   public:
    /**
     * 双指针法（自己实现）
     */
    vector<int> twoSum(vector<int>& numbers, int target) {
        int n = numbers.size();
        // 左指针左边开始
        for (int i = 0; i < n; i++) {
            // 跳过重复的左指针
            if (i > 0 && numbers[i] == numbers[i - 1]) continue;
            // 右指针右边开始
            for (int j = n - 1; j > i; j--) {
                // 跳过重复的右指针
                if (j < n - 1 && numbers[j] == numbers[j + 1]) continue;
                // 之和大于 target，右边太大，右指针左移
                if (numbers[i] + numbers[j] > target) continue;
                // 之和小于 target，左边太小，左指针右移
                else if (numbers[i] + numbers[j] < target)
                    break;
                else {
                    return {i + 1, j + 1};
                }
            }
        }
        return {};
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> nums = {{2, 7, 11, 15}, {2, 3, 4}, {-1, 0}};
    vector<int> targets = {9, 6, -1};

    for (int i = 0; i < nums.size(); i++) {
        auto ans = s->twoSum(nums[i], targets[i]);
        for (auto i : ans) {
            cout << i << " ";
        }
        cout << endl;
    }
}