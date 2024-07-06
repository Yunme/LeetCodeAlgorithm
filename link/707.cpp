#include "link.h"

// @lcpr-template-end
// @lc code=start

/**
 * 707：设计链表
 *
 * 你可以选择使用单链表或者双链表，设计并实现自己的链表。
 * 单链表中的节点应该具备两个属性：val 和 next 。val 是当前节点的值，next
 * 是指向下一个节点的指针/引用。 如果是双向链表，则还需要属性 prev
 * 以指示链表中的上一个节点。假设链表中的所有节点下标从 0 开始。
 *
 * 实现 MyLinkedList 类：
 * MyLinkedList() 初始化 MyLinkedList 对象。
 * int get(int index) 获取链表中下标为 index 的节点的值。如果下标无效，则返回 -1
 * 。 void addAtHead(int val) 将一个值为 val
 * 的节点插入到链表中第一个元素之前。在插入完成后，新节点会成为链表的第一个节点。
 * void addAtTail(int val) 将一个值为 val
 * 的节点追加到链表中作为链表的最后一个元素。 void addAtIndex(int index, int
 * val) 将一个值为 val 的节点插入到链表中下标为 index 的节点之前。 如果 index
 * 等于链表的长度，那么该节点会被追加到链表的末尾。如果 index
 * 比长度更大，该节点将 不会插入 到链表中。 void deleteAtIndex(int index)
 * 如果下标有效，则删除链表中下标为 index 的节点。
 *
 * https://leetcode.cn/problems/design-linked-list/description/
 */
class MyLinkedList {
   private:
    // 使用哨兵节点 方便
    ListNode *head = new ListNode(-1);
    ListNode *tail = new ListNode(-1);

   public:
    MyLinkedList() { head->next = tail; }

    int get(int index) {
        // 查找元素 找到具体元素
        ListNode *p = head->next;
        int i = 0;
        for (; i < index && p; i++) {
            p = p->next;
        }
        if (p && i == index && p != tail) {
            return p->val;
        }
        return -1;
    }

    void addAtHead(int val) { addAtIndex(0, val); }

    // 尾部添加元素
    void addAtTail(int val) {
        // 原尾指针作为真实元素
        tail->val = val;
        // 添加新的尾指针
        tail->next = new ListNode();
        // 更新尾指针
        tail = tail->next;
    }

    void addAtIndex(int index, int val) {
        ListNode *p = head;
        int i = 0;
        // 添加元素 找到要添加的前一个结点
        for (; i < index && p; i++) {
            p = p->next;
        }
        if (p && i == index && p != tail) {
            ListNode *node = new ListNode(val);
            node->next = p->next;
            p->next = node;
        }
    }

    void deleteAtIndex(int index) {
        ListNode *p = head;
        int i = 0;
        // 删除元素 找到要添加的前一个结点
        for (; i < index && p; i++) {
            p = p->next;
        }
        if (p && i == index && p->next && p->next != tail) {
            ListNode *temp = p->next;
            p->next = p->next->next;
            delete temp;
        }
    }

    void print() {
        ListNode *p = head->next;
        while (p != tail) {
            cout << p->val << " ";
            p = p->next;
        }
        cout << endl;
    }
};

int main() {
    MyLinkedList myLinkedList;
    myLinkedList.addAtHead(1);
    myLinkedList.print();
    myLinkedList.addAtTail(3);
    myLinkedList.print();
    myLinkedList.addAtIndex(1, 2);  // 链表变为 1->2->3
    myLinkedList.print();

    auto result = myLinkedList.get(1);  // 返回 2
    cout << result << endl;
    myLinkedList.deleteAtIndex(1);  // 现在，链表变为 1->3
    myLinkedList.print();
    result = myLinkedList.get(4);  // 返回 3

    myLinkedList.addAtIndex(2, 5);
    myLinkedList.deleteAtIndex(3);
    myLinkedList.print();

    cout << result << endl;
}