#include "link.h"

/**
 * 86: 分割链表
 * 给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，
 * 使得所有小于 x 的节点都出现在 大于或等于 x 的节点之前。
 * 你应当 保留 两个分区中每个节点的初始相对位置。
 * https://leetcode.cn/problems/partition-list/description/
 */
class Solution {
   public:
    /**
     * 法1：在原链表上操作，双指针
     * 思路：
     * 1. 找到第一个大于x的结点，记录他的前驱指针1：firstLargePrev ；
     * 2. 向后遍历，找到小于 x 的结点，把他插到 firstLargePrev 之后，
     * 3. 更新相关指针
     * 指针2：当前遍历指针
     */
    ListNode* partition(ListNode* head, int x) {
        if (!head) return head;
        // 设置 dummy 处理头指针情况
        ListNode* dummy = new ListNode;
        dummy->next = head;
        ListNode* current = dummy->next;
        // 第一个大于x的结点的前驱
        ListNode* firstLargePrev = nullptr;
        ListNode* prev = dummy;
        while (current) {
            if (firstLargePrev == nullptr && current->val >= x) {
                firstLargePrev = prev;
            }
            if (firstLargePrev && current->val < x) {
                // 记录 下一个结点
                ListNode* next = current->next;
                // 记录第一个大于 x 的结点
                ListNode* firstLarge = firstLargePrev->next;
                // 把当前结点放到第一个 x 结点之前。
                firstLargePrev->next = current;
                current->next = firstLarge;
                // 当前已移除，prev 指向 next
                prev->next = next;
                // 因为要保证已有顺序不变，先遍历到的小于的插在前面，
                // 插完后，firstLargePrev 更新
                firstLargePrev = current;
                // 检查下一个
                current = next;
            } else {
                prev = current;
                current = current->next;
            }
        }
        // cout << firstLargePrev->val << endl;
        return dummy->next;
    }

    /**
     * 法2：通过分割原链表，找出小于x的链表和大于等x的链表
     * 把大于等于x的链表拼接到小于x的链表的末尾。
     * 返回小链表头
     */
    ListNode* partition2(ListNode* head, int x) {
        if (!head) return head;
        // 设置 dummy 处理头指针情况
        ListNode* dummySmall = new ListNode;
        ListNode* small = dummySmall;
        ListNode* dummyBig = new ListNode;
        ListNode* big = dummyBig;

        ListNode* current = head;
        while (current) {
            if (current->val < x) {
                small->next = current;
                small = small->next;
            } else {
                big->next = current;
                big = big->next;
            }
            current = current->next;
        }
        big->next = nullptr;
        small->next = dummyBig->next;
        return dummySmall->next;
    }
};

int main() {
    Solution* s = new Solution();
    int array[] = {1, 4, 3, 2, 5, 2};
    // int array[] = {8, 2, 4, 6, 7, 3, 2, 1, 5, 9};
    // int array[] = {1};
    ListNode* list = new ListNode(array, size(array));
    ListNode* result = s->partition2(list, 3);
    result->print();
}