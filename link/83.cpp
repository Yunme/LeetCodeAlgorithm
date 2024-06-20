#include "link.h"

/**
 * 83：删除排序链表中的重复元素
 *
 * 给定一个已排序的链表的头 head ， 删除所有重复的元素，使每个元素只出现一次
 * 。返回 已排序的链表 。
 *
 * https://leetcode.cn/problems/remove-duplicates-from-sorted-list/description/
 */
class Solution {
   public:
    /**
     * 链表操作 一次遍历 （自己实现）
     */
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) return head;
        ListNode* p = head;
        ListNode* pre = nullptr;
        while (p) {
            if (pre && pre->val == p->val) {
                // 与前一个相等时 删除
                ListNode* temp = p;
                // 指向下一个
                p = temp->next;
                pre->next = temp->next;
                delete temp;
            } else {
                pre = p;
                p = p->next;
            }
        }
        return head;
    }

    /**
     * 链表操作 一次遍历 简洁版
     * 没有释放元素结点
     */
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) return head;
        ListNode* p = head;
        while (p->next) {
            if (p->val == p->next->val) {
                p->next = p->next->next;
            } else {
                p = p->next;
            }
        }
        return head;
    }
};

int main() {
    Solution* s = new Solution;
    vector<vector<int>> list = {{1, 1, 2}, {1, 1, 2, 3, 3}};

    for (int i = 0; i < list.size(); i++) {
        auto ans = s->deleteDuplicates(new ListNode(list[i]));
        ans->print();
    }
}