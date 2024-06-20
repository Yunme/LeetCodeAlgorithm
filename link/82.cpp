#include "link.h"

/**
 * 82: 删除排序链表中的重复元素 II
 *
 * 给定一个已排序的链表的头 head ，
 * 删除原始链表中所有重复数字的节点，只留下不同的数字 。返回 已排序的链表 。
 *
 * https://leetcode.cn/problems/reverse-linked-list-ii/
 */
class Solution {
   public:
    /**
     * 一次遍历删除（自己实现）
     * 快慢指针
     * 慢指针指向：重复的结点之前的一个。
     * 快指针指向：重复的结点的下一个
     */
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) return head;
        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* fast = head;
        ListNode* slow = dummy;  // pre 是已兑换
        while (fast) {
            ListNode* start = fast;  // 暂存 fast 寻找重复结点的第一个结点
            while (fast->next && fast->val == fast->next->val) {
                fast = fast->next;
            }
            // fast 指向了重复结点的最后一个
            // 如果不同，说明至少两个重复了
            if (start != fast) {
                // fast 指向重复结点的下一个
                fast = fast->next;
                // cout << pre->val << " ";
                slow->next = fast;  // 重复之前的 -> 重复之后的
            } else {
                // 无重复 向后遍历
                slow = fast;
                fast = fast->next;
            }
        }
        // cout << endl;
        return dummy->next;
    }
};

int main() {
    Solution* s = new Solution;
    vector<vector<int>> list = {{1, 2, 3, 3, 4, 4, 5}, {1, 1, 1, 2, 3}};

    for (int i = 0; i < list.size(); i++) {
        auto ans = s->deleteDuplicates(new ListNode(list[i]));
        ans->print();
    }
}