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
 * 27：移除数组中元素
 * 给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val
 * 的元素。元素的顺序可能发生改变。 然后返回 nums 中与 val 不同的元素的数量。
 *
 * 假设 nums 中不等于 val 的元素数量为 k，要通过此题，您需要执行以下操作：
 * 更改 nums 数组，使 nums 的前 k 个元素包含不等于 val 的元素。nums 的其余元素和
 * nums 的大小并不重要。 返回 k。
 *
 * https://leetcode.cn/problems/remove-element/description
 */
class Solution {
   public:
    /**
     * 笨办法，遇到相等的 左移数组 复杂度高
     */
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int i = 0;
        while (i < n) {
            if (nums[i] == val) {
                for (int j = i + 1; j < n; j++) {
                    nums[j - 1] = nums[j];
                }
                n--;
            } else {
                i++;
            }
        }
        return n;
    }
    /**
     * 快慢指针法：
     * 慢指针i：指向不等于 val 的元素；
     * 快指针j 去找不等于 val 的元素，找到后交给 i。
     * 直到 i 找完数组。
     */
    int removeElement2(vector<int>& nums, int val) {
        int i = 0;

        for (int j = 0; j < nums.size(); j++) {
            if (nums[j] != val) {
                nums[i] = nums[j];
                i++;
            }
        }
        return i;
    }

    /**
     * 双指针，i在数组头，j在数组尾
     * 当 i 指向的 == val 时，j 指向的赋值给 i，j--;
     * 如果，赋值来的还是相等，继续 j--;
     * 直到 i 指针指向的不等于 val 为止。
     * i 和 j 一起遍历了整个数组
     */
    int removeElement3(vector<int>& nums, int val) {
        int n = nums.size();
        int i = 0, j = n;
        // 左指针i
        while (i < j) {
            if (nums[i] == val) {
                nums[i] = nums[j - 1];
                j--;
            } else {
                i++;
            }
        }
        return i;
    }
};

int main() {
    Solution* s = new Solution();
    int array1[] = {0, 1, 2, 2, 3, 0, 4, 2};
    vector<int> v1(array1, array1 + size(array1));

    int count = s->removeElement2(v1, 2);

    for (int i = 0; i < count; i++) {
        cout << v1[i] << " ";
    }
}