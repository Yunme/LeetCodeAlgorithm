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

/**
 * 274：H 指数
 * 给你一个整数数组 citations ，其中 citations[i] 表示研究者的第 i
 * 篇论文被引用的次数。计算并返回该研究者的 h 指数。
 *
 * 根据维基百科上 h 指数的定义：h 代表“高引用次数” ，
 * 一名科研人员的 h 指数 是指他（她）至少发表了 h 篇论文，并且 至少 有 h
 * 篇论文被引用次数大于等于 h 。 如果 h 有多种可能的值，h 指数
 * 是其中最大的那个。
 *
 *  https://leetcode.cn/problems/h-index/description/
 */
class Solution {
   public:
    /**
     * 法1：排序 时间复杂度 O(nLogN)
     * 最多有h个数是大于等于h的
     * h=0
     * 升序排序后，每找一个元素大于当前h的，h+1. 直到元素不大于h
     */
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        sort(citations.begin(), citations.end());
        // h 从 0 开始
        int h = 0;
        // for (int i = n - 1; i >= 0 && citations[i] > h; i--) {
        //     h++;
        // }
        for (int i = n - 1; i >= 0 && citations[i] > h; i--, h++);
        return h;
    }

    /**
     * 法2：计数排序 时间复杂度 O(n)
     * 计数排序可以将复杂度降到 O(n)
     */
    int hIndex2(vector<int>& citations) {
        int n = citations.size();
        vector<int> counter(n + 1);
        // H 指数不可能大于 论文发表数
        for (int i = 0; i < n; i++) {
            // 大于论文发表数的 按照最大发表数计算
            if (citations[i] >= n) {
                counter[n]++;
            } else {
                counter[citations[i]]++;
            }
        }
        for (int i : counter) {
            cout << i << " ";
        }
        cout << endl;

        int total = 0;
        // 向前遍历计数数组，得到大于等于当前引用次数的总论文数
        // 找到一个后跳出循环
        for (int i = n; i >= 0; i--) {
            total += counter[i];
            if (total >= i) {
                return i;
            }
        }
        return 0;
    }

    /**
     * 法3：二分查找
     * 从 0 到 n 查找满足 有h篇论文的引用次数至少为h次
     */
    int hIndex3(vector<int>& citations) {
        if (citations.size() == 1) {
            return citations[0] > 0 ? 1 : 0;
        }

        int left = 0, right = citations.size();
        while (left < right) {
            int mid = (left + right + 1) / 2; // +1 防止死循环
            int temp = 0;
            // 对于当前 mid 判断是否满足
            for (int i = 0; i < citations.size(); i++) {
                if (citations[i] >= mid) temp++;
            }
            if (temp >= mid) {  // [mid, right]
                left = mid;
            } else {
                right = mid - 1;  // [0, mid)
            }
        }
        return left;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> array = {{3, 0, 6, 1, 5}, {1, 3, 1}, {0, 1}};
    for (int i = 0; i < array.size(); i++) {
        auto ans = s->hIndex3(array[i]);
        cout << ans << endl;
    }
}