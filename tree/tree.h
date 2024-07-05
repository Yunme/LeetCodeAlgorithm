#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

#define null INT_MIN

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *next = nullptr;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
    TreeNode(vector<int> &array) : TreeNode() {
        if (array.empty()) return;
        this->val = array[0];
        int count = array.size();
        vector<TreeNode *> temp(count);
        temp[0] = this;
        for (int i = 1; i < count; i++) {
            temp[i] = array[i] != null ? new TreeNode(array[i]) : nullptr;
        }

        for (int i = 0; 2 * i + 1 < count; i++) {
            int left = 2 * i + 1;
            if (temp[left]) {
                temp[i]->left = temp[left];
            }
            int right = left + 1;
            if (right < count && temp[right]) {
                temp[i]->right = temp[right];
            }
        }
    }
    /**
     * 层序打印
     */
    void print() {
        queue<TreeNode *> queue;
        queue.push(this);
        while (!queue.empty()) {
            int size = queue.size();
            cout << "[";
            for (int i = 0; i < size; i++) {
                auto front = queue.front();
                queue.pop();
                if (front->left) queue.push(front->left);
                if (front->right) queue.push(front->right);
                cout << front->val;
                if (i != size - 1) {
                    cout << " ";
                }
            }
            cout << "] ";
        }
    }

    /**
     * 根据 next 域输出
     * 只需要找到最左边的
     */
    void printNext() {
        TreeNode *current = this;
        while (current) {
            // 当前层
            TreeNode *node = current;
            cout << "[";
            while (node) {
                cout << node->val;
                node = node->next;
                if (node) cout << " ";
            }
            cout << "]";
            if (current->left) {
                current = current->left;
            } else if (current->right) {
                current = current->right;
            } else if (current->next) {
                current = current->next->left ? current->next->left
                                              : current->next->right;
            } else {
                current = nullptr;
            }
        }
    }
};
