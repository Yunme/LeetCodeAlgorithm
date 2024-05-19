#include <math.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * https://blog.csdn.net/qfc_128220/article/details/127914382
 *
 * 3.寻找最富裕家庭
 *
 * 在一棵树中，每个节点代表一个家庭成员，节点的数字表示其个人的财富值，
 * 一个节点及其直接相连的子节点被定义为一个小家庭。现给你一棵树，请计算出最富裕的小家庭的财富和。
 * https://blog.csdn.net/weixin_48157259/article/details/137877290
 *
 * 本质就是寻找 树中直接相连的子树权值最大的结点的总和
 * 输入：
 * 1. n 结点个数 编号为 1~n
 * 2. 1 ~ n 结点的财富值
 * 3. n-1 行的 结点关系，n1 n2，n1 是 n2 的父节点
 */

/**
 * 直接遍历
 * 计算所有结点及其直接子孩子的财富
 * 取最大值
 */
int maxWealth(int n, vector<int> &wealth, unordered_map<int, vector<int>> map) {
    int maxSum = 0;
    for (int i = 1; i <= n; i++) {
        int tempSum = wealth[i - 1];
        // 计算孩子的财富
        for (auto j : map[i]) {
            tempSum += wealth[j - 1];
        }
        maxSum = max(maxSum, tempSum);
    }
    return maxSum;
}

/**
 * 广度优先, 队列实现
 * 看作是树来遍历
 */
int bfs(int n, vector<int> &wealth, unordered_map<int, vector<int>> map) {
    // 先找到根
    // 没有父节点的节点就是根
    set<int> children;
    for (auto &[_, v] : map) {
        for (auto i : v) children.insert(i);
    }
    int root;
    for (int i = 1; i <= n; i++) {
        if (children.count(i) == 0) {
            root = i;
            break;
        }
    }

    // 队列实现，先进先出
    int ans = 0;
    queue<int> queue;
    queue.push(root);
    // 广度优先：先父节点，再所有子节点
    while (!queue.empty()) {
        int front = queue.front();
        queue.pop();
        cout << front << ", ";
        int tempWealth = wealth[front - 1];
        for (int child : map[front]) {
            queue.push(child);
            tempWealth += wealth[child - 1];
        }
        ans = max(ans, tempWealth);
    }
    return ans;
}

/**
 * 深度优先 栈实现
 */
int dfs(int n, vector<int> &wealth, unordered_map<int, vector<int>> map) {
    // 先找到根
    // 没有父节点的节点就是根
    int maxWealth = 0;
    set<int> children;
    for (auto &[_, v] : map) {
        for (auto i : v) children.insert(i);
    }
    int root;
    for (int i = 1; i <= n; i++) {
        if (children.count(i) == 0) {
            root = i;
            break;
        }
    }

    stack<int> stack;
    stack.push(root);
    while (!stack.empty()) {
        int top = stack.top();
        stack.pop();
        cout << top << ", ";
        int tempWealth = wealth[top - 1];
        for (auto child : map[top]) {
            stack.push(child);
            tempWealth += wealth[child - 1];
        }
        maxWealth = max(maxWealth, tempWealth);
    }
    return maxWealth;
}

int main() {
    int n = 4;
    cin >> n;
    vector<int> wealth(n);
    for (int i = 0; i < n; i++) {
        cin >> wealth[i];
    }
    unordered_map<int, vector<int>> map;
    for (size_t i = 0; i < n - 1; i++) {
        int p;
        int q;
        cin >> p >> q;
        map[p].push_back(q);
    }
    // int minWealth = maxWealth(n, wealth, map);
    int minWealth = bfs(n, wealth, map);
    // int minWealth = dfs(n, wealth, map);

    cout << minWealth;
}