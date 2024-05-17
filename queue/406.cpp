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
using namespace std;

/**
 * 406: 根据身高重建队列
 * 数组中元素是一对数据，(h, k) h 表示身高和 k
 * 表示前面正好有几个人身高大于等于自己；
 * 排序数组中数据，使其位置正确，确保前面身高大于等于自己的数据位置正确。
 * https://leetcode.cn/problems/queue-reconstruction-by-height/description/
 */

class Solution {
   public:
    /**
     * 身高从大到小
     * 大的优先放，因为大的位置会影响小的位置，
     * 但小的位置不会影响大的位置
     */
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // 原数组按身高从大到小排序
        // 身高一样时，按 k 从小到大，小的表示前面高于或等于自己的少。
        // 排序后，元素前面的个数，就是大于或等于自己的个数
        sort(people.begin(), people.end(),
             [](const vector<int>& u, const vector<int>& v) {
                 return u[0] > v[0] || (u[0] == v[0] && u[1] < v[1]);
             });
        // [7,0] [7,1] [6,1] [5,0] [5,2] [4,4]

        vector<vector<int>> result;
        // [7,0]
        // [7,0] [7,1]
        // [7,0] [6,1] [7,1]
        // [5,0] [7,0] [6,1] [7,1]
        // [5,0] [7,0] [5,2] [6,1] [7,1]
        // [5,0] [7,0] [5,2] [6,1] [4,4] [7,1]
        // 根据 k 依次插到第k个位置
        for (auto& i : people) {
            // for (int j : i) {
            //     cout << j << ",";
            // }
            // cout << endl;
            result.insert(result.begin() + i[1], i);
        }

        return result;
    }

    vector<vector<int>> reconstructQueue2(vector<vector<int>>& people) {
        // 原数组按身高从小到大排序
        // 身高一样时，按 k 从大到小
        sort(people.begin(), people.end(),
             [](const vector<int>& u, const vector<int>& v) {
                 return u[0] < v[0] || (u[0] == v[0] && u[1] > v[1]);
             });
        // [4,4] [5,2] [5,0] [6,1] [7,1] [7,0]

        vector<vector<int>> result(people.size());

        // 根据 k 依次插到第k个空位置
        for (auto& p : people) {
            for (int j : p) {
                cout << j << ",";
            }
            cout << endl;
            // 寻找放置位置： 第 k 个空位置
            // 前面有k个数大于等于他，那么他在 k+1 处
            int emptyCount = 0;
            for (int i = 0; i < people.size(); i++) {
                if (result[i].empty()) {
                    emptyCount++;
                    if (emptyCount == p[1] + 1) {
                        result[i] = p;
                        break;
                    }
                }
            }
        }
        return result;
    }
};

int main() {
    Solution* s = new Solution();

    vector<vector<int>> people = {{7, 0}, {4, 4}, {7, 1},
                                  {5, 0}, {6, 1}, {5, 2}};
    auto result = s->reconstructQueue2(people);
    cout << endl;

    for (auto i : result) {
        for (int j : i) {
            cout << j << ",";
        }
        cout << endl;
    }
}