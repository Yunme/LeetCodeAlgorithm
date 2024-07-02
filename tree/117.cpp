#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "tree.h"
using namespace std;

/**
 * 117：填充每个节点的下一个右侧节点指针 II
 * 填充它的每个 next
 * 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next
 * 指针设置为 NULL 。 初始状态下，所有 next 指针都被设置为 NULL 。
 *
 * 非完全二叉树
 * https://leetcode.cn/problems/populating-next-right-pointers-in-each-node-ii/description
 */
typedef TreeNode Node;
class Solution {
   public:
    /**
     * 法1：层序遍历，O(n) O(n) 与完全二叉树版本一致
     * 同一层添加 next 指针
     * 直接连接下一个
     */
    Node* connect(Node* root) {
        if (root == nullptr) return root;
        // 层序遍历
        queue<Node*> queue;
        queue.push(root);
        while (!queue.empty()) {
            int size = queue.size();
            // 遍历同一层
            for (int i = 0; i < size; i++) {
                Node* front = queue.front();
                queue.pop();
                // 判断是否达到末尾
                if (i < size - 1) {  // 直接连接下一个
                    front->next = queue.front();
                }
                if (front->left) queue.push(front->left);
                if (front->right) queue.push(front->right);
            }
        }
        return root;
    }

    /**
     * 法2：利用上一层的 next 指针建立 O(n) O(1)
     * 在当前层为下一层建立 next 指针
     * 属于同一个父节点的
     * node.left.next = node.right
     *
     * 不属于同一个父节点的
     * node.right.next = node.next.left   // node 所处层已经建立
     */
    Node* connect3(Node* root) {
        if (root == nullptr) return root;
        Node* dummy = new Node();
        Node* current = root;
        while (current) {
            // 开始下一层 清空
            dummy->next = nullptr;
            // pre ：上一个 虚拟节点 简化判空
            Node* pre = dummy;
            // 当前层
            while (current) {
                // 连接左孩子
                if (current->left) {
                    pre->next = current->left;
                    pre = pre->next;  // 更新 pre
                }
                // 连接右孩子
                if (current->right) {
                    pre->next = current->right;
                    pre = pre->next;  // 更新 pre
                }
                current = current->next;
            }
            // 下一层
            current = dummy->next;  // 第一个非空的
        }
        return root;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {
        {1, 2, 3, 4, 5, null, 7}, {}, {1, 2, 3}, {3, 9, 20, null, null, 15, 7}};
    for (auto& i : arr) {
        Node* ans = s->connect3(new TreeNode(i));
        ans->printNext();
        cout << endl;
    }
}