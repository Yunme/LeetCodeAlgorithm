#include "link.h"

/**
 * k 个一组翻转链表
 * https://leetcode.cn/problems/reverse-nodes-in-k-group/description/
 */
class Solution {
   public:
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

    // 利用 92 中的解法，分批翻转
    // 循环了多次
    ListNode *reverseKGroup(ListNode *head, int k) {
        int n = 0;
        ListNode *p = head;
        while (p) {
            n++;
            p = p->next;
        }

        ListNode *newHead = nullptr;
        for (int i = 1; i + k - 1 <= n; i += k) {
            if (newHead == nullptr) {
                newHead = reverseBetweenLoopOpt(head, i, i + k - 1);
            } else {
                newHead = reverseBetweenLoopOpt(newHead, i, i + k - 1);
            }
        }
        return newHead;
    }

    // 206 里，翻转整个链表
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

    // 只循环一次
    ListNode *reverseKGroupOpt(ListNode *head, int k) {
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;
        ListNode *pre = dummy, *end = dummy;

        while (end->next) {
            // 寻找第k个，若剩下不足k个则跳出
            for (int i = 0; i < k && end; i++) {
                end = end->next;
            }

            if (end == nullptr) {
                break;
            }
            // 分割从start 到 end 的链表并翻转
            ListNode *start = pre->next;
            // 下一段的起始
            ListNode *next = end->next;
            // 分割
            end->next = nullptr;
            // 局部翻转 并于前面相连
            pre->next = reverseListLoop(start);
            // start 变为一段中的尾结点，与下一段起始相连
            start->next = next;

            // 下一段
            pre = start;
            end = start;
        }
        return dummy->next;
    }

    ListNode *reverseKGroupRecursive(ListNode *head, int k) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode *end = head;
        for (int i = 0; i < k; i++) {
            if (end == nullptr) {
                return head;
            }
            end = end->next;
        }
        // 翻转从 head 到 end
        ListNode *current = head;
        ListNode *pre = nullptr;
        while (current != end) {
            ListNode *next = current->next;
            // 与上一个翻转
            current->next = pre;
            pre = current;
            current = next;
        }

        head->next = reverseKGroupRecursive(end, k);
        return pre;
    }
};

int main() {
    Solution *s = new Solution;
    int a[] = {1, 2, 3, 4, 5};
    ListNode head(a, 5);
    head.print();

    //   s->reverseKGroup(&head, 1)->print();
    //   s->reverseKGroupOpt(&head, 2)->print();
    s->reverseKGroupRecursive(&head, 3)->print();
}