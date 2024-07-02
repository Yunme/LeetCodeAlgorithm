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
 * 116：填充每个节点的下一个右侧节点指针
 * 给定一个 完美二叉树 ，其所有叶子节点都在同一层，每个父节点都有两个子节点。
 * 二叉树定义 (增加一个 next 指针)
 *
 * 填充它的每个 next
 * 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next
 * 指针设置为 NULL。 初始状态下，所有 next 指针都被设置为 NULL。
 *
 * https://leetcode.cn/problems/populating-next-right-pointers-in-each-node/description/
 */
typedef TreeNode Node;
class Solution {
   public:
    /**
     * 法1：层序遍历，O(n) O(n)
     * 同一层添加 next 指针
     */
    Node* connect(Node* root) {
        if (root == nullptr) return root;
        // 层序遍历
        queue<Node*> queue;
        queue.push(root);
        while (!queue.empty()) {
            int size = queue.size();
            Node* prev = nullptr;
            // 遍历同一层
            for (int i = 0; i < size; i++) {
                Node* front = queue.front();
                queue.pop();
                if (prev) {
                    // 添加 next 指针
                    prev->next = front;
                }
                prev = front;
                if (front->left) queue.push(front->left);
                if (front->right) queue.push(front->right);
            }
        }
        return root;
    }

    /**
     * 法1：层序遍历，O(n) O(n)
     * 同一层添加 next 指针
     * 直接连接下一个
     */
    Node* connect2(Node* root) {
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
        // 逐层向下
        Node* leftMost = root;  // root 节点不需要
        while (leftMost->left) {
            Node* node = leftMost;
            // 当前层 为下一层建立关联
            // 从左向右
            while (node) {
                // 同一父节点 左->右
                node->left->next = node->right;
                if (node->next) {
                    // 不是同一个父节点
                    node->right->next = node->next->left;
                }
                // 向右
                node = node->next;
            }
            // 向下一层
            leftMost = leftMost->left;
        }
        return root;
    }

    /**
     * 法3：递归版本 利用上一层的 next 指针建立 O(n) O(1) 递归栈可算可不算
     * 在当前层为下一层建立 next 指针
     * 属于同一个父节点的
     * node.left.next = node.right
     *
     * 不属于同一个父节点的
     * node.right.next = node.next.left   // node 所处层已经建立
     */
    Node* connect4(Node* root) {
        if (root == nullptr || root->left == nullptr) return root;
        root->left->next = root->right;
        if (root->next) {
            root->right->next = root->next->left;
        }
        connect4(root->left);
        connect4(root->right);
        return root;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> arr = {{1, 2, 3, 4, 5, 6, 7}, {}, {1, 2, 3}};
    for (auto& i : arr) {
        Node* ans = s->connect4(new TreeNode(i));
        ans->printNext();
        cout << endl;
    }
}