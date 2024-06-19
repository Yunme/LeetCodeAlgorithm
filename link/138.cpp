#include "link.h"

/**
 * 138: 随机链表的复制
 * 给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random
 * ，该指针可以指向链表中的任何节点或空节点。 构造这个链表的 深拷贝。
 * 深拷贝应该正好由 n 个 全新
 * 节点组成，其中每个新节点的值都设为其对应的原节点的值。新节点的 next 指针和
 * random
 *
 * 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。
 * 复制链表中的指针都不应指向原链表中的节点。
 * 例如，如果原链表中有 X 和 Y 两个节点，其中 X.random --> Y。
 * 那么在复制链表中对应的两个节点 x 和 y ，同样有 x.random --> y 。
 * 返回复制链表的头节点。
 * 用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val,
 * random_index] 表示： val：一个表示 Node.val 的整数。
 * random_index：随机指针指向的节点索引（范围从 0 到
 * n-1）；如果不指向任何节点，则为  null 。 你的代码 只 接受原链表的头节点 head
 * 作为传入参数。
 * https://leetcode.cn/problems/copy-list-with-random-pointer/description
 */
typedef ListNode Node;
class Solution {
   public:
    /**
     * 法1：根据创建过程模拟，比较繁琐
     */
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return head;
        // 每个结点与 index 存储到 map 中
        unordered_map<Node*, int> map;
        vector<Node*> oldList;
        Node* p = head;
        while (p) {
            oldList.push_back(p);
            map[p] = oldList.size() - 1;
            p = p->next;
        }

        // 创建新结点列表
        vector<Node*> newList(oldList.size());
        for (int i = 0; i < oldList.size(); i++) {
            Node* old = oldList[i];
            newList[i] = new Node(old->val);
        }

        // 根据 map 关联 random 指针
        for (int i = 0; i < oldList.size(); i++) {
            Node* oldRandom = oldList[i]->random;
            if (oldRandom == nullptr) {
                newList[i]->random = nullptr;
            } else {
                newList[i]->random = newList[map[oldRandom]];
            }
        }
        // 链接新链表
        Node* dummy = new Node();
        p = dummy;
        for (int i = 0; i < newList.size(); i++) {
            p->next = newList[i];
            p = p->next;
        }
        return dummy->next;
    }

    /**
     * 法2：构建 map 存储旧结点和新结点的对应关系
     * 再遍历原链表构建 新链表的 next 和 random 指针
     */
    Node* copyRandomList2(Node* head) {
        if (head == nullptr) return nullptr;
        // 存储旧结点、对应新结点
        unordered_map<Node*, Node*> map;
        Node* p = head;
        // 复制每个结点，并建立映射
        while (p) {
            map[p] = new Node(p->val);
            p = p->next;
        }
        // 构建新链表的 next 和 random
        p = head;
        while (p) {
            map[p]->next = map[p->next];
            map[p]->random = map[p->random];
            p = p->next;
        }
        return map[head];
    }

    /**
     * 法3：复制 拼接 拆分 O(n) O(1)
     * 在原链表上 原结点 next 指向复制的结点
     * old1 -> new1 -> old2 -> new2;
     * 访问旧结点 old1 时。old1.next.random = old1.random.next;
     * 拆分链表 返回新链表
     */
    Node* copyRandomList3(Node* head) {
        if (head == nullptr) return nullptr;
        // 复制
        // old1 -> new1 -> old2 -> new2;
        Node* p = head;
        while (p) {
            Node* next = p->next;
            Node* newNode = new Node(p->val);
            p->next = newNode;
            newNode->next = next;
            p = next;
        }

        // 设置 random 指针
        p = head;
        while (p && p->next) {
            if (p->random) {
                // p->next :新结点
                // p->random :random 的新结点
                p->next->random = p->random->next;
            }
            // 跳两个 下一个旧结点
            p = p->next->next;
        }

        // 拆分链表
        p = head;
        Node* newHead = head->next;
        Node* q = newHead;
        while (q->next) {
            p->next = p->next->next;
            q->next = q->next->next;
            p = p->next;
            q = q->next;
        }
        p->next = nullptr;  // 旧链表尾部断开
        return newHead;
    }
};

int main() {
    Solution* s = new Solution;
    // 每个元素为一个链表
    // 后一个是 随机链表指向的 index
    vector<vector<pair<int, int>>> array = {
        {{7, -1}, {13, 0}, {11, 4}, {10, 2}, {1, 0}},
        {{1, 1}, {2, 1}},
        {{3, -1}, {3, 0}, {3, -1}}};
    for (int i = 0; i < array.size(); i++) {
        auto list = array[i];
        vector<Node*> nodes(list.size());
        for (int j = 0; j < list.size(); j++) {
            nodes[j] = new Node(list[j].first);
        }
        Node* head = nodes[0];
        for (int j = 0; j < list.size(); j++) {
            int randomIndex = list[j].second;
            if (randomIndex >= 0) {
                nodes[j]->random = nodes[randomIndex];
            }
            if (j > 0) {
                nodes[j - 1]->next = nodes[j];
            }
        }
        s->copyRandomList3(head)->print();
    }
}