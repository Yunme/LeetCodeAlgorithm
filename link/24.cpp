#include "link.h"

/**
 * 24: 两两交换链表中的节点
 * 给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。
 * 你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。
 * https://leetcode.cn/problems/swap-nodes-in-pairs/description/
 */
class Solution {
   public:
    /**
     * 法1：递归版本（自己实现）
     */
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        // 第2个
        ListNode* next = head->next;
        // 第1个的下一个变成 第3个
        head->next = swapPairs(next->next);
        // 第2个的下一个是第1个
        next->next = head;
        return next;
    }
    /**
     * 法2：迭代版本（自己实现）
     */
    ListNode* swapPairs2(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode* dummy = new ListNode;
        dummy->next = head;
        ListNode* p = dummy->next;
        ListNode* pre = dummy;
        while (p && p->next) {
            // 第2个
            ListNode* second = p->next;
            // 第3个
            ListNode* next = second->next;
            // 第2个的下一个是当前
            second->next = p;
            // 与前一组相连
            pre->next = second;
            // 更新前一组
            p->next = nullptr;  // 第1个下一个先断开
            pre = p;
            // 更新当前为第3个
            p = next;
        }
        pre->next = p;

        return dummy->next;
    }
};

int main() {
    Solution* s = new Solution;
    vector<vector<int>> array = {{1, 2, 3, 4, 5}, {2, 4, 6, 8}, {1},
                                 {1, 2},          {},           {1, 2, 3}};

    for (size_t i = 0; i < array.size(); i++) {
        auto arr = array[i];
        s->swapPairs2(new ListNode(arr))->print();
    }
}