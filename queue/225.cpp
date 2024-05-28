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
 * 225：用队列实现栈
 * 请你仅使用两个队列实现一个后入先出（LIFO）的栈，
 * 并支持普通栈的全部四种操作（push、top、pop和 empty）。
 *
 * 进阶：你能否仅用一个队列来实现栈。
 * https://leetcode.cn/problems/implement-stack-using-queues/description/
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
class MyStack1 {
   public:
    MyStack1() {}

    void push(int x) {
        if (queue1.empty()) {
            queue1.push(x);
            queue2.push(x);
        } else {
            clearQueue(queue2);
            queue2.push(x);
            while (!queue1.empty()) {
                queue2.push(queue1.front());
                queue1.pop();
            }
            queue1 = queue2;
        }
    }

    int pop() {
        if (queue1.empty()) return -1;
        int t = top();
        queue1.pop();
        return t;
    }

    int top() {
        if (queue1.empty()) return -1;
        return queue1.front();
    }

    bool empty() { return queue1.size() == 0; }

   private:
    queue<int> queue1;
    queue<int> queue2;
    void clearQueue(queue<int>& queue) {
        while (!queue.empty()) queue.pop();
    }
};

/**
 * 法2：一个队列实现
 * 入队时：获取队列中元素个数 n，
 * 入队后，对队头的 n 个元素依次出队后再入队，形成栈的形式
 * push(1): q: 1
 * push(2): q: 1 2, -> q:2 1 (2前面的元素出队再入队)
 */
class MyStack2 {
   public:
    MyStack2() {}

    void push(int x) {
        int n = queue.size();
        queue.push(x);
        for (int i = 0; i < n; i++) {
            queue.push(queue.front());
            queue.pop();
        }
    }

    int pop() {
        if (queue.empty()) return -1;
        int t = top();
        queue.pop();
        return t;
    }

    int top() {
        if (queue.empty()) return -1;
        return queue.front();
    }

    bool empty() { return queue.size() == 0; }

   private:
    queue<int> queue;
};

typedef MyStack2 MyStack;

int main() {
    MyStack* s = new MyStack();
    s->push(1);
    s->push(2);
    s->push(3);
    auto result = s->pop();
    cout << result << endl;
    result = s->pop();
    cout << result << endl;
    result = s->pop();
    cout << result << endl;
    result = s->pop();
    cout << result << endl;
    result = s->empty();
    cout << result << endl;
}