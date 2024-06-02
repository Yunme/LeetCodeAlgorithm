/// @brief
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "../link/link.h"
using namespace std;

/**
 * 23: 合并k个升序链表
 * 给你一个链表数组，每个链表都已经按升序排列。
 * 请你将所有链表合并到一个升序链表中，返回合并后的链表。
 * https://leetcode.cn/problems/merge-k-sorted-lists/description/
 */
class Solution {
   public:
    /**
     * 合并两个有序链表
     */
    ListNode* mergeListNode(ListNode* node1, ListNode* node2) {
        // ListNode* node1 = nodeA;
        // ListNode* node2 = nodeB;
        if (node1 == nullptr) return node2;
        if (node2 == nullptr) return node1;

        ListNode* dummy = new ListNode();
        ListNode* p = dummy;
        while (node1 && node2) {
            if (node1->val <= node2->val) {
                p->next = node1;
                node1 = node1->next;
            } else {
                p->next = node2;
                node2 = node2->next;
            }
            p = p->next;
        }
        if (node1) p->next = node1;
        if (node2) p->next = node2;
        return dummy->next;
    }
    /**
     * 法1：分治 合并有序链表（自己实现）
     * 逐个两两合并，合并后存到新list，
     * 再对新的list两两合并，直到新list 里只有一个链表
     * 返回这个链表
     */
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        vector<ListNode*> oldLists = lists;
        int count = oldLists.size();
        // 列表个数大于1 执行两两合并
        while (count > 1) {
            vector<ListNode*> newLists;
            // 每两个进行合并
            for (int i = 0; i + 1 < count; i += 2) {
                newLists.push_back(mergeListNode(oldLists[i], oldLists[i + 1]));
            }
            // 奇数个，最后一个剩下的加入
            if (count % 2 == 1) newLists.push_back(oldLists[count - 1]);
            // 更新新列表
            oldLists = newLists;
            count = oldLists.size();
        }
        return oldLists[0];
    }

    /**
     * 法2：分治 递归
     * 上述的递归版本
     */
    ListNode* merge(vector<ListNode*>& list, int left, int right) {
        if (left == right) return list[left];
        if (left > right) return nullptr;
        int mid = (left + right) / 2;
        // 递归找到最小相邻的两个
        return mergeListNode(merge(list, left, mid),
                             merge(list, mid + 1, right));
    }
    ListNode* mergeKLists2(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        return merge(lists, 0, lists.size() - 1);
    }

    /**
     * 法3：优先级队列
     * 先把每个链表头加入队列，按小的优先，
     * 取出队头的，再将该队头的下个结点入队
     */
    ListNode* mergeKLists3(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        // 小的优先
        auto compare = [](ListNode*& a, ListNode*& b) {
            return a->val > b->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(compare)> queue(
            compare);
        // 每个链表头入队
        for (auto& i : lists) {
            if (i) queue.push(i);
        }
        ListNode* dummy = new ListNode();
        ListNode* p = dummy;
        while (!queue.empty()) {
            // 队头最小的出队
            auto top = queue.top();
            // 存到结果后
            p->next = top;
            // 当前列表后还有，入队
            if (top->next) {
                queue.push(top->next);
            }
            queue.pop();
            p = p->next;
        }
        return dummy->next;
    }
};

int main() {
    Solution* s = new Solution;
    vector<ListNode*> array = {new ListNode({1, 4, 5}), new ListNode({1, 3, 4}),
                               new ListNode({2, 6})};
    // vector<ListNode*> array1 = {};

    s->mergeKLists3(array)->print();
}