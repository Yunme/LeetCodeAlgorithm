#include "link.h"

/**
 * 142: 环形链表 II
 *
 * 给定一个链表的头节点  head ，返回链表开始入环的第一个节点。
 * 如果链表无环，则返回 null。 如果链表中有某个节点，可以通过连续跟踪 next
 * 指针再次到达，则链表中存在环。
 *
 * https://leetcode.cn/problems/linked-list-cycle-ii/description/
 */
class Solution {
   public:
    /**
     * 法1：hash 法 O(n) O(n)
     * 遍历链表将结点加入set，如果重复了，说明有环，并且重复的是入环的节点
     */
    ListNode* detectCycle(ListNode* head) {
        unordered_set<ListNode*> set;
        ListNode* p = head;
        while (p) {
            if (set.count(p) > 0) {
                return p;
            } else {
                set.insert(p);
            }
            p = p->next;
        }
        return nullptr;
    }

    /**
     * 法2：双指针法 O(n) O(1)
     * - 根据快慢双指针 龟兔赛跑；
     * - slow fast 都从 head 开始，slow 每次走一步，fast 每次走两步
     * - 如果有环，那么 fast 肯定会追上 slow 指针的。
     * - 假设链表从头到入环结点距离为 a，入环结点到双指针相遇为
     * b，相遇结点再到入环结点为 c
     * - 此时 slow 走了: a + b;
     * - 此时 fast 走了：a + b + c + b
     * - 因为 fast 是 slow 的两倍: 2(a + b) = a + b + c + b 推导出：a = c;
     */
    ListNode* detectCycle2(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            // 相遇代表有环
            if (slow == fast) {
                // 此时指针 index1 再从 head 出发,
                // index2 从相遇点出发；根据上面推到 a = c;
                ListNode* index1 = head;
                ListNode* index2 = slow;
                while (index1 != index2) {
                    // 每步走一样的距离，相遇后 就是入环结点
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index1;
            }
        }
        return nullptr;
    }
};

int main() {
    Solution* s = new Solution;
    vector<vector<int>> array = {{3, 2, 0, -4}, {1, 2}, {1}, {1, 2}};
    vector<int> indexs = {1, 0, -1, -1};  // 入环的index
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
        auto node = s->detectCycle2(head);
        if (node) {
            cout << node->val << endl;
        } else {
            cout << nullptr << endl;
        }
    }
}