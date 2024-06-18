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
 * 287: 寻找重复数
 *
 * 给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和
 * n），可知至少存在一个重复的整数。 假设 nums 只有 一个重复的整数 ，返回
 * 这个重复的数 。 你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1)
 * 的额外空间。
 *
 * https://leetcode.cn/problems/find-the-duplicate-number/description/
 */
class Solution {
   public:
    /**
     * 法1：二分查找 O(nLogN) O(1)
     * 根据题目，n + 1个整数，都在 [1, n] 的范围内
     * 二分查找 1~n 范围，
     * 如果数组中 <= mid 的数的个数 > mid，那么重复的数在 [1, mid] 中，
     * 例如 1,2,3,3,4  <= 4的个数为 5 > 4, 则重复的数比在 [1,4]中
     * 否则在 mid ~ high 中
     */
    int findDuplicate(vector<int>& nums) {
        int low = 1;
        int high = nums.size() - 1;
        while (low < high) {
            int mid = (low + high) / 2;
            int count = 0;
            // 遍历数组找到 <= mid 的数的个数
            for (int i = 0; i < nums.size(); i++) {
                if (nums[i] <= mid) {
                    count++;
                }
            }
            // 如果个数 大于mid，则比在 [1, mid]
            if (count > mid) {
                high = mid;
            } else {
                // 否则在 [mid+1, high]
                low = mid + 1;
            }
        }
        // 最后 low == high
        return low;
    }

    /**
     * 法2：刷圈法（龟兔赛跑） O(n) O(1)
     * 类似于 142：环形链表 II
     * 如果重复的话，必定有环，入环处的元素为重复元素
     * [1, 3, 4, 2, 2]
     * 根据 index：0->1->3->2->4->2->4 ...
     */
    int findDuplicate2(vector<int>& nums) {
        int n = nums.size();
        int slow = 0;
        int fast = 0;
        while (fast >= 0 && fast < n) {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow == fast) {  // 相遇：有环
                // cout << slow << " " << fast << endl;
                // 从 0 开始
                int index1 = 0;
                // 从 相遇处开始
                int index2 = slow;
                while (index1 != index2) {
                    // 每次走一步
                    index1 = nums[index1];
                    index2 = nums[index2];
                }
                // 再次相遇 就是入环处。重复的元素
                return index1;
            }
        }
        return -1;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> array = {
        {1, 3, 4, 2, 2}, {3, 1, 3, 4, 2}, {3, 3, 3, 3, 3}};

    for (size_t i = 0; i < array.size(); i++) {
        auto ans = s->findDuplicate2(array[i]);
        cout << ans << " ";
        cout << endl;
    }
}