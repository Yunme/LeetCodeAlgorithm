#include "link.h"

/**
 * 92：反转链表II 反转局部链表
 * 给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。
 * 请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。
 * https://leetcode.cn/problems/reverse-linked-list-ii/
 */
class Solution {
   public:
    /**
     * 法1：使用栈暂存 O(n) O(n)
     * 暂存区间里的结点，对依次出栈的前后连接
     */
    ListNode *reverseBetween(ListNode *head, int left, int right) {
        if (left > right || left == right) {
            return head;
        }
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;
        ListNode *leftPre = dummy;  // 要翻转的第一个的前驱
        for (int i = 0; i < left - 1; i++) {
            leftPre = leftPre->next;
        }
        // 对区间结点入栈
        stack<ListNode *> stack;
        ListNode *nextRightEnd = leftPre->next;  // 区间里的最后一个元素
        for (int i = 0; i < right - left + 1; i++) {
            stack.push(nextRightEnd);
            nextRightEnd = nextRightEnd->next;
        }
        // if (leftPre) {
        //     cout << leftPre->val << " ";
        // }
        // if (nextRightEnd) {
        //     cout << nextRightEnd->val << endl;
        // }

        // 区间结点前后 结点断开
        // leftPre 是区间的前一个元素
        leftPre->next = nullptr;

        // 出栈，并相连
        ListNode *q = leftPre;
        while (!stack.empty()) {
            q->next = stack.top();
            stack.pop();
            q = q->next;
        }
        // 与区间外下个相连
        q->next = nextRightEnd;
        return dummy->next;
    }

    /**
     * 法2：一次循环 O(n) O(1)
     */
    ListNode *reverseBetween2(ListNode *head, int left, int right) {
        ListNode *prev = nullptr;
        ListNode *leftPrev = nullptr;
        ListNode *current = head;
        int i = 1;
        while (current != nullptr && i <= right) {
            ListNode *next = current->next;
            if (i > left) {
                // 需要翻转的 下一个指向前一个
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
            // 区间里的第一个指向 当前的（区间后一个）
            leftPrev->next->next = current;
            leftPrev->next = prev;
        } else {
            head->next = current;
            return prev;
        }
        return head;
    }

    /**
     * 一次循环翻转 O(n) O(1)
     */
    ListNode *reverseBetweenLoopOpt(ListNode *head, int left, int right) {
        ListNode *dummyNode = new ListNode(-1);
        dummyNode->next = head;
        ListNode *leftPre = dummyNode;
        for (int i = 0; i < left - 1; i++) {
            leftPre = leftPre->next;
        }
        // left = 2, right = 5
        // 1，2，3，4，5，6
        // leftPre: 1
        // current = 2;
        ListNode *current = leftPre->next;
        for (int i = 0; i < right - left; i++) {
            // 3
            ListNode *next = current->next;
            // 2 -> 4
            current->next = next->next;
            // 翻转 3 -> 2
            next->next = leftPre->next;
            // 逐步更新
            // 1 -> 3
            leftPre->next = next;
        }
        return dummyNode->next;
    }
};

int main() {
    Solution *s = new Solution;
    vector<vector<int>> list = {{1, 2, 3, 4, 5}, {5}, {3, 5}, {1, 2, 3, 4, 5}};
    vector<pair<int, int>> section = {{2, 4}, {1, 1}, {1, 2}, {1, 2}};

    for (int i = 0; i < list.size(); i++) {
        auto ans = s->reverseBetween2(new ListNode(list[i]), section[i].first,
                                      section[i].second);
        ans->print();
    }
}