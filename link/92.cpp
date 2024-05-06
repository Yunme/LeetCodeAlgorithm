#include "link.h"

/**
 * 反转链表II 反转局部链表
 * https://leetcode.cn/problems/reverse-linked-list-ii/
 */
class Solution {
   public:
    ListNode *reverseBetween(ListNode *head, int left, int right) {
        if (left > right) {
            return head;
        }

        stack<ListNode *> stack;
        int i = 1;
        ListNode *p = head;
        ListNode *leftPrev = nullptr;
        while (p && i <= right) {
            if (i >= left) {
                stack.push(p);
            }
            if (i == left - 1) {
                leftPrev = p;
            }
            i++;
            p = p->next;
        }

        ListNode *t = leftPrev;
        ListNode *newHead = nullptr;
        if (leftPrev == nullptr) {
            newHead = stack.top();
            stack.pop();
            t = newHead;
        }
        while (!stack.empty()) {
            t->next = stack.top();
            t = t->next;
            stack.pop();
        }
        t->next = p;
        if (!leftPrev) {
            return newHead;
        }
        return head;
    }

    ListNode *reverseBetweenRecursive(ListNode *head) {}

    ListNode *reverseBetweenLoop(ListNode *head, int left, int right) {
        ListNode *prev = nullptr;
        ListNode *leftPrev = nullptr;
        ListNode *current = head;
        int i = 1;
        while (current != nullptr && i <= right) {
            ListNode *next = current->next;
            if (i > left) {
                current->next = prev;
            }
            if (i == left) {
                leftPrev = prev;
            }

            i++;
            prev = current;
            current = next;
        }
        if (leftPrev) {
            leftPrev->next->next = current;
            leftPrev->next = prev;
        } else {
            head->next = current;
            return prev;
        }
        return head;
    }

    ListNode *reverseBetweenLoopOpt(ListNode *head, int left, int right) {
        ListNode *dummyNode = new ListNode(-1);
        dummyNode->next = head;
        ListNode *leftPre = dummyNode;
        for (int i = 0; i < left - 1; i++) {
            leftPre = leftPre->next;
        }
        ListNode *current = leftPre->next;
        for (int i = 0; i < right - left; i++) {
            ListNode *next = current->next;
            current->next = next->next;
            // 翻转
            next->next = leftPre->next;
            // 逐步更新
            leftPre->next = next;
        }
        return dummyNode->next;
    }
};

int main() {
    Solution *s = new Solution;
    int a[] = {1, 2, 3, 4, 5};
    ListNode head(a, 5);
    head.print();
    //   s->reverseBetweenLoop(&head, 1, 3)->print();
    //   s->reverseList(&head)->print();
    //   s->reverseBetween(&head, 1, 3)->print();
    s->reverseBetweenLoopOpt(&head, 1, 4)->print();
}