#include "link.h"

/**
 * 2: 两数相加
 * 你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序
 * 的方式存储的，并且每个节点只能存储 一位 数字。
 * 请你将两个数相加，并以相同形式返回一个表示和的链表。
 *
 * 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 *
 * https://leetcode.cn/problems/add-two-numbers/description/
 */
class Solution {
   public:
    /**
     * 链表法（自己实现）
     */
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode();
        ListNode* p = dummy;
        bool over = false;  // 是否需要进位
        // 当某个没到尾指针继续
        while (l1 || l2) {
            // 上一位是否进位
            int v = over ? 1 : 0;
            if (l1) {
                // 加上 l1
                v += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                // 加上 l2
                v += l2->val;
                l2 = l2->next;
            }
            // 结果的后一位
            p->next = new ListNode(v % 10);
            p = p->next;
            // 下一位是否需要进位
            over = v >= 10;
        }
        // 最后一位是否需要进位
        if (over) {
            p->next = new ListNode(1);
        }
        return dummy->next;
    }
};

int main() {
    Solution* s = new Solution;
    vector<vector<int>> array1 = {{2, 4, 3}, {0}, {9, 9, 9, 9, 9, 9, 9}};
    vector<vector<int>> array2 = {{5, 6, 4}, {0}, {9, 9, 9, 9}};

    for (size_t i = 0; i < array1.size(); i++) {
        s->addTwoNumbers(new ListNode(array1[i]), new ListNode(array2[i]))
            ->print();
    }
}