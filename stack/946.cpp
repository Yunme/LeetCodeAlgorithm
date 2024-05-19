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
 * 946:验证栈序列
 * 给定 pushed 和 popped 两个序列，每个序列中的
 * 值都不重复，只有当它们可能是在最初空栈上进行的推入 push 和弹出 pop
 * 操作序列的结果时，返回 true；否则，返回 false 。
 * https://leetcode.cn/problems/validate-stack-sequences/description/
 */
class Solution {
   public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> stack;

        int j = 0;
        for (int i : pushed) {
            stack.push(i);
            while (!stack.empty()) {
                if (j >= popped.size()) return false;
                if (popped[j] == stack.top()) {
                    stack.pop();
                    j++;
                } else {
                    break;
                }
            }
        }
        return j == popped.size();
    }
};

int main() {
    Solution* s = new Solution();

    vector<int> pushed = {1, 2, 3, 4, 5};
    // vector<int> poped = {4, 5, 3, 2, 1};
    vector<int> poped = {4, 5, 3, 1, 2};

    bool ans = s->validateStackSequences(pushed, poped);
    cout << ans << endl;
}