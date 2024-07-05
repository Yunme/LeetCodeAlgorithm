#include "link.h"

/**
 * 203: 移除链表元素
 *
 * 给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val ==
 * val 的节点，并返回 新的头节点 。
 *
 * https://leetcode.cn/problems/remove-linked-list-elements/description/
 */
class Solution {
   public:
    /**
     * 法1：迭代：遍历删除 O(n) O(1)
     */
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* p = dummy;
        while (p && p->next) {
            if (p->next->val == val) {
                ListNode* temp = p->next;
                p->next = p->next->next;
                delete temp;
                continue;
            }
            p = p->next;
        }
        return dummy->next;
    }

    /**
     * 法2：递归
     */
    ListNode* removeElements(ListNode* head, int val) {
        if (head == nullptr) return head;
        head->next = removeElements(head->next, val);
        return head->val == val ? head->next : head;
    }
};

int main() {
    Solution* s = new Solution;
    vector<vector<int>> array = {{1, 2, 6, 3, 4, 5, 6}, {}, {7, 7, 7, 7}};
    vector<int> removes = {6, 1, 7};
    for (int i = 0; i < array.size(); i++) {
        auto arr = array[i];
        s->removeElements(new ListNode(array[i]), removes[i])->print();
        // head->print();
    }
}