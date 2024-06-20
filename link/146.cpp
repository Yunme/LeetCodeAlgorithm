#include "link.h"

/**
 * 146：LRU 缓存
 * 你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
 *
 * 实现 LRUCache 类：
 * LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
 * int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1
 * void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value
 *
 * 如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过
 * capacity ，则应该 逐出 最久未使用的关键字。
 *
 * 函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。
 *
 * https://leetcode.cn/problems/lru-cache/description/
 */
class LRUCache {
   private:
    /**
     * 双向链表存储先后关系
     */
    struct Node {
        int key;
        int val;
        Node *prev;
        Node *next;
        Node(int key, int val)
            : key(key), val(val), prev(nullptr), next(nullptr) {}
    };
    // 首尾结点
    // 变成虚拟结点 更好操作
    Node *head, *tail;
    int cap;                         // 容量
    unordered_map<int, Node *> map;  // 存储键值对

    /**
     * 移动结点到链表尾部
     */
    void moveToTail(Node *node) {
        // 已经是尾结点 不需要移动
        if (node == tail) {
            return;
        }
        Node *prev = node->prev;  // 当前的前驱
        Node *next = node->next;  // 当前的后继
        node->next = nullptr;

        // 更新 next 指针
        if (prev == nullptr) {  // 前驱为空
            head = next;        // 头结点更新为 next
        } else {
            prev->next = next;  // 否则 前驱的后继为 next
        }

        // 更新 prev 指针
        Node *last = tail;
        if (next != nullptr) {  // next 不为空
            next->prev = prev;  // next 前驱指向当前的前驱
        } else {
            last = prev;  // next 为空,尾结点
        }

        if (last == nullptr) {  // 空链表情况
            head = node;
        } else {  // 非空
            node->prev = last;
            last->next = node;
        }
        tail = node;  // 更新结点
    }

    /**
     * 移除结点
     */
    void removeNode(Node *node) {
        Node *next = node->next;
        Node *prev = node->prev;
        // 更新 next 指针
        if (prev == nullptr) {  // prev 为空 当前为头结点
            head = next;        // 头结点更新为下个结点
        } else {
            prev->next = next;  // prev 不为空
        }

        // 更新 prev 指着
        if (next == nullptr) {  // next 为空, 尾结点
            tail = prev;
        } else {
            next->prev = prev;  // next 不为空
        }
    }

    void print() {
        Node *p = head;
        cout << "[";
        while (p) {
            cout << p->val << " ";
            p = p->next;
        }
        cout << "]" << endl;
    }

   public:
    LRUCache(int capacity)
        : head(nullptr),
          tail(nullptr),
          cap(capacity),
          map(unordered_map<int, Node *>()) {}

    /**
     * get
     * 如果在map 里不存在 返回-1；
     * 存在，将该结点移动到链表尾部
     */
    int get(int key) {
        if (map.count(key) == 0) return -1;
        Node *node = map[key];
        moveToTail(node);
        print();
        return node->val;
    }

    /**
     * put 操作
     * 如果 key 已存在，则更新 value，移动到链表尾部
     * 如果不存在：
     * 如果容量已满，移除链表头部元素
     * 插入新结点到链表尾部
     */
    void put(int key, int value) {
        if (map.count(key) > 0) {
            Node *node = map[key];
            node->val = value;
            moveToTail(node);
            print();
            return;
        }

        if (map.size() == cap) {
            // 移除头结点元素
            map.erase(head->key);
            removeNode(head);
        }
        // 新结点
        Node *node = new Node(key, value);
        map[key] = node;
        if (tail == nullptr) {
            // 尾结点为空
            tail = node;
            head = tail;
        } else {
            // 尾结点不为空
            tail->next = node;
            node->prev = tail;
            tail = tail->next;
        }
        print();
    }
};

int main() {
    // LRUCache *lRUCache = new LRUCache(2);
    // lRUCache->put(1, 1);             // 缓存是 {1=1}
    // lRUCache->put(2, 2);             // 缓存是 {1=1, 2=2}
    // auto result = lRUCache->get(1);  // 返回 1
    // cout << result << endl;
    // lRUCache->put(3, 3);  // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    // result = lRUCache->get(2);  // 返回 -1 (未找到)
    // cout << result << endl;
    // lRUCache->put(4, 4);  // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    // result = lRUCache->get(1);  // 返回 -1 (未找到)
    // cout << result << endl;
    // result = lRUCache->get(3);  // 返回 3
    // cout << result << endl;
    // result = lRUCache->get(4);  // 返回 4
    // cout << result << endl;

    // LRUCache *lRUCache = new LRUCache(1);
    // lRUCache->put(2, 1);
    // auto result = lRUCache->get(2);
    // cout << result << endl;
    // lRUCache->put(3, 2);
    // result = lRUCache->get(2);
    // cout << result << endl;
    // result = lRUCache->get(3);
    // cout << result << endl;

    // LRUCache *lRUCache = new LRUCache(2);
    // auto result = lRUCache->get(2);
    // cout << result << endl;
    // lRUCache->put(2, 6);
    // result = lRUCache->get(1);
    // cout << result << endl;
    // lRUCache->put(1, 5);
    // lRUCache->put(1, 2);
    // result = lRUCache->get(1);
    // cout << result << endl;
    // result = lRUCache->get(2);
    // cout << result << endl;

    // LRUCache *lRUCache = new LRUCache(3);
    // lRUCache->put(1, 1);
    // lRUCache->put(2, 2);
    // lRUCache->put(3, 3);
    // lRUCache->put(4, 4);
    // auto result = lRUCache->get(4);
    // cout << result << endl;
    // result = lRUCache->get(3);
    // cout << result << endl;
    // result = lRUCache->get(2);
    // cout << result << endl;
    // result = lRUCache->get(1);
    // cout << result << endl;
    // lRUCache->put(5, 5);
    // result = lRUCache->get(1);
    // cout << result << endl;
    // result = lRUCache->get(2);
    // cout << result << endl;
    // result = lRUCache->get(3);
    // cout << result << endl;
    // result = lRUCache->get(4);
    // cout << result << endl;
    // result = lRUCache->get(5);
    // cout << result << endl;

    LRUCache *lRUCache = new LRUCache(1);
    auto result = lRUCache->get(6);
    cout << result << endl;
    result = lRUCache->get(8);
    cout << result << endl;
    lRUCache->put(12, 1);
    result = lRUCache->get(2);
    cout << result << endl;
    lRUCache->put(15, 11);
    lRUCache->put(5, 2);
    lRUCache->put(1, 15);
    lRUCache->put(4, 2);
    result = lRUCache->get(5);
    cout << result << endl;
    lRUCache->put(15, 15);
}