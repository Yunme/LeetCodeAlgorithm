#include "link.h"

/**
 * 61:旋转链表
 * 给你一个链表的头节点 head ，旋转链表，将链表每个节点向右移动 k 个位置。
 *
 * https://leetcode.cn/problems/rotate-list/description
 */
class Solution {
   public:
    /**
     * 法1：暴力法：O(k * n)
     * 每次右移一次，移动 k 次
     */
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr || k == 0) return head;
        // k 有可能大于 链表的长度，大于后移动重复了
        ListNode* p = head;
        int n = 0;
        while (p) {
            n++;
            p = p->next;
        }
        // 等同于：
        k = k % n;
        // 循环 k 次
        for (int i = 0; i < k; i++) {
            // 右移一次
            ListNode* p = head;
            ListNode* pre = nullptr;
            while (p->next) {
                pre = p;
                p = p->next;
            }
            // p 为尾结点，pre 为 p 的前一个结点
            pre->next = nullptr;  // pre 变成新的尾结点
            p->next = head;       // 原尾结点变成头结点
            head = p;             // 更新头结点
        }
        return head;
    }

    /**
     * 法2：不需要移动 k 次 O(n)
     * 只需要把倒数第 k 个作为头结点
     */
    ListNode* rotateRight2(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr || k == 0) return head;
        // k 有可能大于 链表的长度，大于后移动重复了
        ListNode* p = head;
        int n = 0;
        while (p) {
            n++;
            p = p->next;
        }
        // 等同于：
        k = k % n;
        if (k == 0) return head;

        // 找出链表的倒数第k个结点
        ListNode* slow = head;
        ListNode* fast = head;
        for (int i = 0; i < k; i++) {
            fast = fast->next;
        }
        while (fast->next) {
            fast = fast->next;
            slow = slow->next;
        }
        cout << "倒数第k个：" << slow->val << endl; 
        // slow 是倒数第k个结点的前驱
        ListNode* newHead = slow->next;
        slow->next = nullptr;  // 变成尾结点
        fast->next = head;     // 连接到头结点
        return newHead;
    }
};

int main() {
    Solution* s = new Solution;
    vector<vector<int>> list = {{1, 2, 3, 4, 5}, {0, 1, 2}, {1, 2}};
    vector<int> count = {2, 4, 2};

    for (int i = 0; i < list.size(); i++) {
        s->rotateRight2(new ListNode(list[i]), count[i])->print();
    }
}