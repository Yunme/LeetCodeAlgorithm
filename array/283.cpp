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
 * 283. 移动零
 * 给定一个数组 nums，编写一个函数将所有 0
 * 移动到数组末尾，同时保持非零元素的相对顺序
 *
 * 请必须在原地操作
 * https://leetcode.cn/problems/move-zeroes/description/
 */
class Solution {
   public:
    /**
     * 法1：简单粗暴法
     * 从后向前，找0，找到之后把之后的元素向前移动一位。
     * （从前向后的话，0 紧接着 0，i就跳过了）
     */
    void moveZeroes(vector<int>& nums) {
        int count = nums.size();
        for (int i = count - 1; i >= 0; i--) {
            if (nums[i] == 0) {
                for (int j = i + 1; j < count; j++) {
                    nums[j - 1] = nums[j];
                }
                nums[count - 1] = 0;
            }
        }
    }

    /**
     * 法2：双指针法
     * 循环了一次 O(n)
     * 从头遍历数组
     * a.慢指针i 指向已处理好的末尾
     * b.快指针j 待处理的头部
     * j 指向的元素不等于0时，自己和自己交换，i++，j++
     * 当 j 指向的元素等于0时，j++，i还是指向0，交换后 0 后移。
     */
    void moveZeroes2(vector<int>& nums) {
        int count = nums.size();
        int i = 0;
        for (int j = 0; j < count; j++) {
            // 等于 0 时，j++；i还在原地等于0的位置
            if (nums[j] != 0) {
                swap(nums[i], nums[j]);
                i++;
            }
        }
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> array = {
        {0, 1, 0, 3, 12}, {0}, {1, 2, 4, 0, 5}, {0, 0, 1}};

    for (size_t i = 0; i < array.size(); i++) {
        vector<int> arr = array[i];
        s->moveZeroes2(arr);
        for (auto j : arr) {
            cout << j << " ";
        }
        cout << endl;
    }
}