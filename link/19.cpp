#include "link.h"

/**
 * 19:删除链表的倒数第 N 个结点
 * https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/
 */
class Solution {
   public:
    /**
     * 自己实现：
     * 双指针：p 指针每次前移1个，
     * q 指针每次从 p 移动 n 个，当q指针移到末尾时，q就时倒数第n个
     *
     * 不过可以更简单些：
     * 快慢指针：快指针直接定位到第n个，慢指针从头开始；
     * 同时移动，直到快指针到末尾
     */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* prev = dummy;
        ListNode* p = dummy->next;
        while (p) {
            ListNode* q = p;
            int i = n;
            while (i > 0) {
                q = q->next;
                i--;
            }
            if (q == nullptr) {
                cout << "倒数第" << n << "个是:" << p->val << endl;
                ListNode* temp = p;
                prev->next = p->next;
                delete temp;
                break;
            }
            prev = p;
            p = p->next;
        }
        return dummy->next;
    }

    /**
     * 双指针简洁版：
     * 快慢指针：快指针直接定位到第n个，慢指针从dummy开始；
     * 同时移动，直到快指针到末尾, 这样满指针就指向倒数第n个的前驱
     */
    ListNode* removeNthFromEnd2(ListNode* head, int n) {
        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* fast = dummy->next;
        ListNode* slow = dummy;
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }
        while (fast) {
            slow = slow->next;
            fast = fast->next;
        }
        cout << "倒数第" << n << "个是:" << slow->val << endl;
        ListNode* temp = slow->next;
        slow->next = slow->next->next;
        delete temp;
        return dummy->next;
    }
};

int main() {
    Solution* s = new Solution;
    vector<vector<int>> array = {{1, 2, 3, 4, 5}, {1}, {1, 2}};
    vector<int> indexs = {2, 1, 1};

    for (size_t i = 0; i < array.size(); i++) {
        auto arr = array[i];
        s->removeNthFromEnd2(new ListNode(arr), indexs[i])->print();
    }
}