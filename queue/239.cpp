#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 239：滑动窗口最大值
 * 给你一个整数数组 nums，有一个大小为 k
 * 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k
 * 个数字。滑动窗口每次只向右移动一位。 返回 滑动窗口中的最大值 。
 *
 * https://leetcode.cn/problems/sliding-window-maximum/description/
 */

/**
 * 法1：自己实现 两个队列
 * queue1 负责以栈的顺序存储数据，queue2 负责中转
 * 当数据x插入时：queue2先清空，x 入队 queue2 ，然后 queue1，挨个出队，入队到
 * queue2， 此时 queue2，完全按照后入先出，再赋值给 queue1.
 * push(1)：q1：1， q2：1
 * push(2): q2.clear(), 入队 q2:2, q1全部入队q2：2 1；
 * 以此类推
 */
class Solution {
   public:
    /**
     * 法1：暴力查找 O(n k) 超时
     */
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans(n - k + 1);
        // 双层循环
        for (int i = 0; i < n - k + 1; i++) {
            int maxVal = INT_MIN;
            // 找窗口内最大值
            for (int j = i; j < i + k; j++) {
                maxVal = max(nums[j], maxVal);
            }
            ans[i] = maxVal;
        }
        return ans;
    }

    /**
     * 法2：优先队列 大顶堆 O(nLogN) O(n)
     * 队列里存储 元素和index，当滑动窗口移动时，如果堆顶元素 index
     * 不再是滑动窗口范围内的 则出队
     */
    vector<int> maxSlidingWindow2(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans;
        priority_queue<pair<int, int>> queue;
        // 初始 k 个入队
        for (int i = 0; i < k; i++) {
            queue.push({nums[i], i});
        }
        // 第一个窗口里最大值
        ans.push_back(queue.top().first);
        // 滑动窗口移动
        for (int i = k; i < n; i++) {
            queue.push({nums[i], i});
            // 窗口左侧 index = i - k 在窗口之外 出队
            while (queue.top().second <= i - k) {
                queue.pop();
            }
            ans.push_back(queue.top().first);
        }
        return ans;
    }

    /**
     * 法3：单调队列（从头到尾单调递减） O(n) O(n)
     * 队列里从头到尾保持递减 头部的是最大值，尾部的是最小值
     * 尾部入队时：从尾部 pop 掉小于入队值的元素
     */
    vector<int> maxSlidingWindow3(vector<int>& nums, int k) {
        int n = nums.size();
        // 存储数组中的 index 方便出队
        deque<int> deque;
        vector<int> ans;
        // 前 k 个入队
        for (int i = 0; i < k; i++) {
            // 入队到队尾 小于的出队
            while (!deque.empty() && nums[deque.back()] < nums[i]) {
                deque.pop_back();
            }
            deque.push_back(i);
        }
        ans.push_back(nums[deque.front()]);
        // 从第 k 个遍历
        for (int i = k; i < n; i++) {
            // 入队到队尾 小于的出队
            while (!deque.empty() && nums[deque.back()] < nums[i]) {
                deque.pop_back();
            }
            deque.push_back(i);
            // 队列头部最大值 超出滑动窗口边界 出队
            while (deque.front() <= i - k) {
                deque.pop_front();
            }
            ans.push_back(nums[deque.front()]);
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> list = {{1, 3, -1, -3, 5, 3, 6, 7}, {1}};
    vector<int> ks = {3, 1};
    for (int i = 0; i < list.size(); i++) {
        auto ans = s->maxSlidingWindow3(list[i], ks[i]);
        for (auto j : ans) {
            cout << j << " ";
        }
        cout << endl;
    }
}