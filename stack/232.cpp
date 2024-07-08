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
 * 232: 用栈实现队列
 *
 * 请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：
 * 实现 MyQueue 类：
 * void push(int x) 将元素 x 推到队列的末尾
 * int pop() 从队列的开头移除并返回元素
 * int peek() 返回队列开头的元素
 * boolean empty() 如果队列为空，返回 true ；否则，返回 false
 *
 * https://leetcode.cn/problems/implement-queue-using-stacks/description/
 */

class MyQueue {
   private:
    stack<int> stack;

   public:
    MyQueue() {}

    /**
     * 入栈之前先把栈里原有数据临时存储，清空栈
     * 再把入栈元素入栈，原有元素按原有顺序入栈
     * 保证新入栈的元素在栈底
     */
    void push(int x) {
        int size = stack.size();
        vector<int> list(size);
        // 1, 2, 3
        for (int i = 0; i < size; i++) {
            list[i] = stack.top();
            stack.pop();
        }
        stack.push(x);
        for (int i = size - 1; i >= 0; i--) {
            stack.push(list[i]);
        }
    }

    /**
     * 移除并返回
     */
    int pop() {
        int top = stack.top();
        stack.pop();
        return top;
    }

    int peek() { return stack.top(); }

    bool empty() { return stack.empty(); }
};
int main() {
    MyQueue myQueue;
    // myQueue.push(1);  // queue is: [1]
    // myQueue.push(2);  // queue is: [1, 2] (leftmost is front of the queue)
    // auto result = myQueue.peek();  // return 1
    // cout << result << endl;
    // result = myQueue.pop();  // return 1, queue is [2]
    // cout << result << endl;
    // result = myQueue.empty();  // return false
    // cout << result << endl;

    myQueue.push(1);  // queue is: [1]
    myQueue.push(2);
    myQueue.push(3);
    myQueue.push(4);
    auto result = myQueue.pop();
    cout << result << endl;
    myQueue.push(5);
    result = myQueue.pop();
    cout << result << endl;
    result = myQueue.pop();
    cout << result << endl;
    result = myQueue.pop();
    cout << result << endl;
    result = myQueue.pop();
    cout << result << endl;
}