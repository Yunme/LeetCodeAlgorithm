#include <iostream>
#include <vector>
using namespace std;

/**
 * 641: 设计循环双端队列
 * 设计实现双端队列
 * https://leetcode.cn/problems/design-circular-deque/description/
 */

/**
 * 使用双向链表实现
 */
class MyCircularDeque {
   public:
    MyCircularDeque(int k)
        : front(nullptr), last(nullptr), maxSize(k), size(0) {}
    // 插入队头
    bool insertFront(int value) {
        if (isFull()) return false;
        DualNode *node = new DualNode(value);
        if (isEmpty()) {
            front = last = node;
        } else {
            node->next = front;
            front->prev = node;
            front = node;
        }
        size++;
        return true;
    }

    // 插入队尾
    bool insertLast(int value) {
        if (isFull()) return false;
        DualNode *node = new DualNode(value);
        if (isEmpty()) {
            last = front = node;
        } else {
            node->prev = last;
            last->next = node;
            last = node;
        }
        size++;
        return true;
    }

    // 删除队头元素
    bool deleteFront() {
        if (isEmpty()) return false;
        DualNode *p = front;
        front = front->next;
        if (front) front->prev = nullptr;
        delete p;
        size--;
        // 为空后，last 也需要置空
        if (isEmpty()) last = nullptr;
        return true;
    }

    // 删除队尾元素
    bool deleteLast() {
        if (isEmpty()) return false;
        DualNode *p = last;
        last = last->prev;
        if (last) last->next = nullptr;
        delete p;
        size--;
        // 为空后，front 也需要置空
        if (isEmpty()) front = nullptr;
        return true;
    }

    // 获取队头元素
    int getFront() {
        if (front) return front->val;
        return -1;
    }

    // 获取队尾元素
    int getRear() {
        if (last) return last->val;
        return -1;
    }

    bool isEmpty() { return size == 0; }

    bool isFull() { return size == maxSize; }

   private:
    struct DualNode {
        DualNode *next;
        DualNode *prev;
        int val;
        DualNode() : next(nullptr), prev(nullptr), val(-1) {}
        DualNode(int val) : next(nullptr), prev(nullptr), val(val) {}
    };
    // 队列头
    DualNode *front;
    // 队列尾
    DualNode *last;
    // 最大容量
    int maxSize;
    // 当前大小
    int size;
};

/**
 * 使用数组实现 可以存满
 */
class MyVectorCircularDeque {
   public:
    MyVectorCircularDeque(int k) : maxSize(k), array(vector<int>(k)) {}

    // 插入队头
    bool insertFront(int value) {
        if (isFull()) return false;
        if (!isEmpty()) {
            front = backward(front);
        }
        array[front] = value;
        size++;
        return true;
    }

    // 插入队尾
    bool insertLast(int value) {
        if (isFull()) return false;
        if (!isEmpty()) {
            last = forward(last);
        }
        array[last] = value;
        size++;
        return true;
    }

    // 删除队头元素
    bool deleteFront() {
        if (isEmpty()) return false;
        array[front] = -1;
        size--;
        if (!isEmpty()) {
            front = forward(front);
        }
        return true;
    }

    // 删除队尾元素
    bool deleteLast() {
        if (isEmpty()) return false;
        array[last] = -1;
        size--;
        if (!isEmpty()) {
            last = backward(last);
        }
        return true;
    }

    // 获取队头元素
    int getFront() {
        if (isEmpty()) return -1;
        return array[front];
    }

    // 获取队尾元素
    int getRear() {
        if (isEmpty()) return -1;
        return array[last];
    }

    bool isEmpty() { return size == 0; }

    bool isFull() { return size == maxSize; }

   private:
    vector<int> array;
    int maxSize;
    int front = 0;
    int last = 0;
    int size = 0;

    int backward(int i) { return (i - 1 + maxSize) % maxSize; }

    int forward(int i) { return (i + 1) % maxSize; }
};

typedef MyVectorCircularDeque CircularDeque;

int main() {
    CircularDeque *s = new CircularDeque(3);
    int result = s->insertLast(1);
    cout << result << endl;
    result = s->insertLast(2);
    cout << result << endl;
    result = s->insertFront(3);
    cout << result << endl;
    result = s->insertFront(4);
    cout << result << endl;
    result = s->getRear();
    cout << result << endl;
    result = s->isFull();
    cout << result << endl;
    result = s->deleteLast();
    cout << result << endl;
    result = s->insertFront(4);
    cout << result << endl;
    result = s->getFront();
    cout << result << endl;

    // CircularDeque *s = new CircularDeque(8);
    // int result = s->insertFront(5);
    // cout << result << endl;
    // result = s->getFront();
    // cout << result << endl;
    // result = s->isEmpty();
    // cout << result << endl;
    // result = s->deleteFront();
    // cout << result << endl;
    // result = s->insertLast(3);
    // cout << result << endl;
    // result = s->getRear();
    // cout << result << endl;
    // result = s->insertLast(7);
    // cout << result << endl;
    // result = s->insertFront(7);
    // cout << result << endl;
    // result = s->deleteLast();
    // cout << result << endl;
    // result = s->insertLast(4);
    // cout << result << endl;
    // result = s->isEmpty();
    // cout << result << endl;

    // CircularDeque *s = new CircularDeque(5);
    // int result = s->insertFront(7);
    // cout << result << endl;
    // result = s->insertLast(0);
    // cout << result << endl;
    // result = s->getFront();
    // cout << result << endl;
    // result = s->insertLast(3);
    // cout << result << endl;
    // result = s->getFront();
    // cout << result << endl;
    // result = s->insertFront(9);
    // cout << result << endl;
    // result = s->getRear();
    // cout << result << endl;
    // result = s->getFront();
    // cout << result << endl;
    // result = s->getFront();
    // cout << result << endl;
    // result = s->deleteLast();
    // cout << result << endl;
    // result = s->getRear();
    // cout << result << endl;

    // CircularDeque *s = new CircularDeque(2);
    // int result = s->insertFront(7);
    // cout << result << endl;
    // result = s->deleteLast();
    // cout << result << endl;
    // result = s->getFront();
    // cout << result << endl;
    // result = s->insertLast(5);
    // cout << result << endl;
    // result = s->insertFront(0);
    // cout << result << endl;
    // result = s->getFront();
    // cout << result << endl;
    // result = s->getRear();
    // cout << result << endl;
    // result = s->getFront();
    // cout << result << endl;
    // result = s->getFront();
    // cout << result << endl;
    // result = s->getRear();
    // cout << result << endl;
    // result = s->insertLast(0);
    // cout << result << endl;
}