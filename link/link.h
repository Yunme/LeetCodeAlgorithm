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

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
    ListNode(int array[], int size) : ListNode() {
        ListNode *p = this;
        if (size <= 0) {
            return;
        }

        p->val = array[0];
        for (int i = 1; i < size; i++) {
            auto newNode = new ListNode(array[i]);
            p->next = newNode;
            p = newNode;
        }
    }
    ListNode(vector<int> array) : ListNode() {
        ListNode *p = this;
        if (array.size() <= 0) {
            return;
        }

        p->val = array[0];
        for (int i = 1; i < array.size(); i++) {
            auto newNode = new ListNode(array[i]);
            p->next = newNode;
            p = newNode;
        }
    }
    void print() {
        for (ListNode *p = this; p; p = p->next) {
            cout << p->val << " ";
        }
        cout << endl;
    }
};