#include "link.h"

// @lcpr-template-end
// @lc code=start

/**
 * 反转链表
 * https://leetcode.cn/problems/reverse-linked-list/description/
 */
class Solution {
   public:
    ListNode *reverseList(ListNode *head) {
        stack<ListNode *> stack;
        for (ListNode *p = head; p; p = p->next) {
            stack.push(p);
        }

        ListNode *newHead = nullptr;
        if (!stack.empty()) {
            newHead = stack.top();
            stack.pop();
        }

        ListNode *p = newHead;
        while (!stack.empty()) {
            p->next = stack.top();
            stack.pop();
            p = p->next;
        }
        if (p) {
            p->next = nullptr;
        }

        return newHead;
    }

    ListNode *reverseListRecursive(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode *last = reverseListRecursive(head->next);
        head->next->next = head;
        head->next = nullptr;
        return last;
    }

    ListNode *reverseListLoop(ListNode *head) {
        ListNode *prev = nullptr;
        ListNode *current = head;
        while (current) {
            ListNode *next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        return prev;
    }
};

int main() {
    Solution *s = new Solution;
    int a[] = {1, 2, 3, 4, 5};
    ListNode head(a, 2);
    head.print();
    //   s->reverseList(&head)->print();
    //   s->reverseListRecursive(&head)->print();
    s->reverseListLoop(&head)->print();
}