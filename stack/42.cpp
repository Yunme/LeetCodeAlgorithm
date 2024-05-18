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
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 42: 接雨水
 * 给定 n 个非负整数表示每个宽度为 1
 * 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 * https://leetcode.cn/problems/trapping-rain-water/description/
 */
class Solution {
   public:
    /**
     * 法1：自己实现
     * 单调栈
     * 跟官方思路一致，实现较复杂
     */
    int trap(vector<int>& height) {
        stack<int> stack;
        int count = height.size();
        // 左边界
        stack.push(height[0]);
        int sum = 0;
        for (size_t i = 1; i < count; i++) {
            int h = height[i];
            // 小于等于栈顶 入栈
            // 栈内从栈底到栈顶 非严格递减
            if (h <= stack.top()) {
                stack.push(h);
            } else {
                // 栈内至少需要2个元素，如果栈内只有一个元素，下个比他大，那么应该出栈
                if (stack.size() == 1) {
                    stack.pop();
                    stack.push(h);
                    continue;
                }
                // 大于栈顶开始计算，说明能和栈顶围起来
                // 找出栈内小于 h 的值并出栈, 被 h 和
                // 栈顶元素中的小者减，其差值代表雨水填满量
                vector<int> temp;
                int tempSum = 0;
                int top;
                // 首次循环，top 比小于 h
                while (!stack.empty() && (top = stack.top()) < h) {
                    temp.push_back(top);
                    stack.pop();
                }
                int min = std::min(top, h);  // 小的那个边界
                // 遍历小于小边界的那些，填满雨水
                for (int j : temp) {
                    tempSum += min - j;
                    // 栈空，说明 h 比栈里的都大
                    // 非空，说明还需要继续向前找大的能围起来的
                    if (!stack.empty()) {
                        // 把低的填满到 min，变成了柱子
                        stack.push(min);
                    }
                }
                cout << "temp:" << tempSum << endl;
                sum += tempSum;
                stack.push(h);
            }
        }
        return sum;
    }

    /**
     * 官方 单调栈
     * 代码更简洁
     */
    int trap2(vector<int>& height) {
        int result = 0;
        // 栈里存 有差异的height 数组索引
        stack<int> stack;
        for (int i = 0; i < height.size(); i++) {
            // 循环时直接找到小于 当前的，一步一步填满
            while (!stack.empty() && height[i] > height[stack.top()]) {
                // 大小大 才能接雨水
                // 栈里只有一个元素，下个比他大，则出栈。
                int top = stack.top();  // 当前height最小的 index
                stack.pop();
                if (stack.empty()) {
                    break;
                }
                // 一步一步的填满
                int left = stack.top();
                int currWidth = i - left - 1;
                int currHeight = min(height[left], height[i]) - height[top];
                result += currWidth * currHeight;
            }
            stack.push(i);
        }
        return result;
    }
};

int main() {
    Solution* s = new Solution();

    // vector<int> list = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    vector<int> list = {4, 2, 0, 3, 2, 5};

    int count = s->trap2(list);
    cout << count << endl;
}