#include <math.h>

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
#include <sstream>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

/**
 * https://blog.csdn.net/weixin_48157259/article/details/138087531
 *
 * 14. 启动多任务排序
 * 一个应用启动时，会有多个初始化任务需要执行，并且任务之间有依赖关系，
 * 例如A任务依赖B任务，那么必须在B任务执行完成之后，才能开始执行A任务。
 * 现在给出多条任务依赖关系的规则，请输入任务的顺序执行序列，规则采用贪婪策略，
 * 即一个任务如果没有依赖的任务，则立刻开始执行，如果同时有多个任务要执行，则根据任务名称字母顺序排序。
 *
 * https://blog.csdn.net/weixin_48157259/article/details/138138400
 *
 * 输入:
 * 输入参数每个元素都表示任意两个任务之间的依赖关系，
 * 输入参数中符号->表示依赖方向，例A->B表示A依赖B，多个依赖之间用单个空格分割
 * 输出：
 * 排序后的启动任务列表，多个任务之间用单个空格分割
 */

/**
 * 拓扑排序思想：
 * 都输出了，代表没有环，输出的顺序就是图中顶点的先后循序
 */
vector<string> topologicalSort(map<string, int> indgree,
                               map<string, set<string>> map) {
    vector<string> ans;
    queue<string> queue;
    for (auto &[k, v] : map) {
        // 先找到入度为0的，作为起点
        if (indgree.count(k) == 0) {
            queue.push(k);
            ans.push_back(k);
        }
    }
    // 队列里的是 入度为0的，
    while (!queue.empty()) {
        set<string> set;  // 用于排序
        int size = queue.size();
        for (int i = 0; i < size; i++) {
            string front = queue.front();
            queue.pop();
            // 该顶点已移除，遍历所有是他的后驱的，入度减一
            for (auto &s : map[front]) {
                if (--indgree[s] == 0) {
                    // 此时入度为0的在同一级，添加 set 里排序输出
                    set.insert(s);
                    queue.push(s);
                }
            }
        }
        for (auto &s : set) ans.push_back(s);
    }
    return ans;
}

int main() {
    vector<string> arr = {"B->A", "C->A", "D->B", "D->C", "D->E"};
    // 图 边关系
    map<string, set<string>> graph;
    // 结点入度数 //0个的没存
    map<string, int> indgree;
    string input;
    getline(cin, input);
    stringstream ss(input);
    string token;
    vector<pair<string, string>> pair;
    while (getline(ss, token, ' ')) {
        int start = 0;
        int pos = token.find("->");
        string a = token.substr(0, 1);
        string b = token.substr(pos + 2, 1);
        pair.push_back({a, b});
        indgree[a]++;
        graph[b].insert(a);
    }

    // for (auto &[k, v] : graph) {
    //     cout << k << "<-";
    //     for (auto i : v) {
    //         cout << i << ",";
    //     }
    //     cout << endl;
    // }
    // for (auto &[k, v] : indgree) {
    //     cout << k << ":" << v << endl;
    // }

    auto ans = topologicalSort(indgree, graph);
    for (string &s : ans) {
        cout << s << " ";
    }
    cout << endl;
}