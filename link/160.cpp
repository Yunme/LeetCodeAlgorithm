#include "link.h"

/**
 * 160：相交链表
 * 给你两个单链表的头节点 headA 和 headB
 * ，请你找出并返回两个单链表相交的起始节点。 如果两个链表不存在相交节点，返回
 * null 。
 *
 * 图示两个链表在节点 c1 开始相交：
 * 题目数据 保证 整个链式结构中不存在环。
 *
 * 注意，函数返回结果后，链表必须 保持其原始结构 。
 *
 * https://leetcode.cn/problems/intersection-of-two-linked-lists/description/
 */
class Solution {
   public:
    /**
     * 法1：哈希法 O(m+n), O(m)
     * 存储到 set 中，如果已有说明相交
     */
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode *> set;
        // 遍历链表 A，插入到 set 中
        while (headA) {
            set.insert(headA);
            headA = headA->next;
        }
        // 遍历链表 B，如果在 set 中已有了，说明相交，直接返回当前结点
        while (headB) {
            if (set.count(headB) > 0) {
                return headB;
            }
            headB = headB->next;
        }
        // 遍历 B 完，都没有，说明无相交
        return nullptr;
    }

    /**
     * 法2：双指针遍历法 O(m+n) O(1)
     * 两个指针分别指向 A 和 B；
     * pA 遍历 A, 遍历完后遍历 B
     * pB 遍历 B, 遍历完后遍历 A
     * 如果 A 和 B 相交，那么 pA 和 pB 就会相遇
     *
     * 因为：
     * 假设 A 的长度为 a，B 的长度为 b，相交部分长度为 c
     * 那么 pA 走过 a + (b - c), pB 走过 b + (a - c)
     * a + (b - c) 等于 b + (a - c) 所以相遇
     */
    ListNode *getIntersectionNode2(ListNode *headA, ListNode *headB) {
        ListNode *pA = headA;
        ListNode *pB = headB;
        while (pA != pB) {
            // pA 走到底 遍历 pB
            pA = pA == nullptr ? headB : pA->next;
            // pB 走到底 遍历 pA
            pB = pB == nullptr ? headA : pB->next;
        }
        return pA;
    }
};

int main() {
    Solution *s = new Solution;

    vector<vector<int>> array = {{4, 1}, {5, 6, 1}, {1, 9, 1},
                                 {3},    {2, 6, 4}, {1, 5}};
    vector<vector<int>> common = {{8, 4, 5}, {2, 4}, {}};

    for (int i = 0; i < common.size(); i++) {
        ListNode *a = new ListNode(array[2 * i]);
        ListNode *b = new ListNode(array[2 * i + 1]);
        if (common[i].size() > 0) {
            ListNode *c = new ListNode(common[i]);
            a->next = b->next = c;
        }
        s->getIntersectionNode2(a, b)->print();
    }
}