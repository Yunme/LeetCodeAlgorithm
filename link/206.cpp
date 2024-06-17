#include "link.h"

// @lcpr-template-end
// @lc code=start

/**
 * 206: 反转链表
 *
 * 给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
 *
 * https://leetcode.cn/problems/reverse-linked-list/description/
 */
class Solution {
   public:
    /**
     * 法1：利用栈暂存 O(n) O(n)
     */
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

    /**
     * 法2：递归法 O(n) O(n) 递归栈
     */
    ListNode *reverseList2(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode *last = reverseList2(head->next);
        head->next->next = head;
        head->next = nullptr;
        return last;
    }

    ListNode *reverseList4(ListNode *head) { return reverse(head, nullptr); }

    /**
     * 法2：递归法 写法类似双指针
     */
    ListNode *reverse(ListNode *current, ListNode *prev) {
        if (current == nullptr) return prev;
        ListNode *temp = current->next;
        current->next = prev;
        return reverse(temp, current);
    }

    /**
     * 法3：迭代法 O(n) O(1)
     * 双指针
     */
    ListNode *reverseList3(ListNode *head) {
        ListNode *prev = nullptr;
        ListNode *current = head;
        while (current) {
            // 暂存下一位
            ListNode *temp = current->next;
            // 当前的 next 更改指向到 prev
            current->next = prev;
            // pre 和 current 后移
            prev = current;
            current = temp;
        }
        return prev;
    }
};

int main() {
    Solution *s = new Solution;
    vector<vector<int>> list = {{1, 2, 3, 4, 5}, {1, 2}};
    for (auto i : list) {
        s->reverseList4(new ListNode(i))->print();
    }
}