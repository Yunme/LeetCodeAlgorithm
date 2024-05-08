#include "link.h"

/**
 * 排序链表
 * 进阶：时间：nLogN，空间：常数
 * https://leetcode.cn/problems/sort-list/description/
 */
class Solution {
   public:
    ListNode *findMid(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *slow = head, *fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode *Sort_MergeLink(ListNode *low, ListNode *midNext) {
        if (low == nullptr) return midNext;
        if (midNext == nullptr) return low;
        ListNode *p1 = low;
        ListNode *p2 = midNext;
        ListNode *dummyNode = new ListNode;
        ListNode *p = dummyNode;
        while (p1 && p2) {
            if (p1->val < p2->val) {
                p->next = p1;
                p1 = p1->next;
            } else {
                p->next = p2;
                p2 = p2->next;
            }
            p = p->next;
        }
        p->next = p1 ? p1 : p2;
        return dummyNode->next;
    }

    //
    /**
     * 归并递归 空间 logN
     * 递归直到剩单个元素比较大小后， 归并（合并有序链表）
     */
    ListNode *sortList(ListNode *list) {
        if (list == nullptr || list->next == nullptr) return list;
        // 起始
        ListNode *low = list;
        // 中间
        ListNode *mid = findMid(list);
        ListNode *midNext = mid->next;
        // 中间next 置空，从中断开。
        mid->next = nullptr;

        // 左部分
        low = sortList(low);
        // 右部分
        midNext = sortList(midNext);

        // 合并有序链表
        return Sort_MergeLink(low, midNext);
    }

    /**
     * 归并迭代 空间 O(1)
     */
    ListNode *sortListIteration(ListNode *list) {
        // 长度
        int len = 0;
        ListNode *p = list;
        while (p) {
            p = p->next;
            len++;
        }
        auto *dummy = new ListNode;
        dummy->next = list;
        for (int size = 1; size < len; size *= 2) {
            ListNode *current = dummy->next;
            ListNode *prev = dummy;
            while (current) {
                ListNode *leftHead = current;

                // 从左开始的 size 个分割
                ListNode *rightHead = Sort_subLinkList(leftHead, size);
                // 从右开始的 size 个分割
                // current 后移
                current = Sort_subLinkList(rightHead, size);
                // 合并后的与之前相连
                ListNode *merged = Sort_MergeLink(leftHead, rightHead);
                prev->next = merged;

                // prev 指针后移到合并之后的末尾，开始下次循环
                while (prev->next) {
                    prev = prev->next;
                }
            }
        }
        return dummy->next;
    }

    /**
     * 从头开始的第 size 个后断开链表，并返回剩下的
     */
    ListNode *Sort_subLinkList(ListNode *list, int size) {
        if (list == nullptr) return list;
        for (int i = 1; i < size && list->next; ++i) {
            list = list->next;
        }
        ListNode *remain = list->next;
        list->next = nullptr;
        return remain;
    }
};

int main() {
    Solution *s = new Solution;
    int a[] = {4, 2, 3, 5, 1};
    ListNode head(a, 5);
    head.print();

    // s->sortList(&head)->print();
    s->sortListIteration(&head)->print();
}