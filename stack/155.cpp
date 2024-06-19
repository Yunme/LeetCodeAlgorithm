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
 * 155：最小栈
 * 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
 * 实现 MinStack 类:
 * MinStack() 初始化堆栈对象。
 * void push(int val) 将元素val推入堆栈。
 * void pop() 删除堆栈顶部的元素。
 * int top() 获取堆栈顶部的元素。
 * int getMin() 获取堆栈中的最小元素。
 *
 * https://leetcode.cn/problems/min-stack/description/
 */

/**
 * 由于栈每次只能单次操作
 */
class MinStack {
   private:
    // 每个栈内结点 存储当前以下的最小值
    struct Node {
        int val;
        int minVal;
        Node(int val, int minVal) : val(val), minVal(minVal) {}
    };
    stack<Node*> stack;

   public:
    MinStack() {}

    /**
     * push 操作
     * 如果栈为空 直接入栈，并且当前最小值为本身
     * 如果栈不为空，入栈的最小值为 当前元素和栈顶元素小值的 较小者
     */
    void push(int val) {
        if (stack.empty()) {
            stack.push(new Node(val, val));
        } else {
            stack.push(new Node(val, min(stack.top()->minVal, val)));
        }
    }

    void pop() { stack.pop(); }

    int top() { return stack.top()->val; }

    /**
     * 栈内小值 保存在栈顶
     */
    int getMin() { return stack.top()->minVal; }
};

/**
 * 辅助栈法 与上面类似，只不过使用另一个栈来存储当前最小值
 */
class MinStack2 {
   private:
    // 两个栈的操作保持同步
    stack<int> minStack;
    stack<int> stack;

   public:
    MinStack2() {}

    /**
     * push 操作
     * 如果栈为空 直接入栈，并且当前最小值为本身
     * 如果栈不为空，入栈的最小值为 当前元素和栈顶元素小值的 较小者
     */
    void push(int val) {
        stack.push(val);
        if (minStack.empty()) {
            minStack.push(val);
        } else {
            minStack.push(min(val, minStack.top()));
        }
    }

    void pop() {
        stack.pop();
        minStack.pop();
    }

    int top() { return stack.top(); }

    /**
     * 栈内小值 保存在栈顶
     */
    int getMin() { return minStack.top(); }
};

typedef MinStack2 TestStack;

int main() {
    TestStack* s = new TestStack();
    s->push(-2);
    s->push(0);
    s->push(-3);
    cout << s->getMin() << endl;
    s->pop();
    cout << s->top() << endl;
    cout << s->getMin() << endl;
}