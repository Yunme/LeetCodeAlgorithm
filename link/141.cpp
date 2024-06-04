#include "link.h"

/**
 * 141: 环形链表
 * 给你一个链表的头节点 head ，判断链表中是否有环。
 * 如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。
 * https://leetcode.cn/problems/linked-list-cycle/description/
 */
class Solution {
   public:
    /**
     * 法1：set集合判断
     * 时间 O(n), 空间 O(n)
     */
    bool hasCycle(ListNode* head) {
        ListNode* p = head;
        unordered_set<ListNode*> set;
        while (p) {
            // set 中已有 说明有环
            if (set.count(p) > 0) return true;
            set.insert(p);
            p = p->next;
        }
        return false;
    }

    /**
     * 法2：双指针法
     * 慢指针slow：从头开始，每次走一步
     * 快指针fast：从头开始，每次走两步，
     * 如果有环，那么快慢指针必将会重合
     * 如果快指针指向null 则无环
     */
    bool hasCycle2(ListNode* head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            // 慢指针移动一步
            slow = slow->next;
            // 快指针移动两步
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }
};

int main() {
    Solution* s = new Solution;
    vector<vector<int>> array = {{3, 2, 0, -4}, {1, 2}, {1}, {1,2}};
    vector<int> indexs = {1, 0, -1, -1};
    // 创建环
    for (int i = 0; i < array.size(); i++) {
        auto arr = array[i];
        ListNode* head = new ListNode(arr);
        ListNode* tail = head;
        for (; tail->next;) {
            tail = tail->next;
        }
        if (indexs[i] >= 0) {
            ListNode* p = head;
            for (int j = 0; j < indexs[i]; j++) {
                p = p->next;
            }
            tail->next = p;
        }
        // head->print();
        cout << s->hasCycle2(head) << endl;
    }
}