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
using namespace std;

/**
 * 202: 快乐数
 *
 * 编写一个算法来判断一个数 n 是不是快乐数。
 * 「快乐数」 定义为：
 *
 * 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
 * 然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
 * 如果这个过程 结果为 1，那么这个数就是快乐数。
 * 如果 n 是 快乐数 就返回 true ；不是，则返回 false 。
 *
 * https://leetcode.cn/problems/happy-number/description/
 */

class Solution {
   public:
    /**
     * 法1：map 存储
     * 快乐数: 计算结果
     * 1. 最终得到1
     * 2. 最终进入死循环
     * 不会越来越大，因为 较大的数比如 999 的下一个是 81 * 3 = 324 < 999
     */
    bool isHappy(int n) {
        // 根据快乐数的计算规则
        // 记录当前数的下一个数
        unordered_map<int, int> map;
        // 如果不等于 1，且 不在 map 中
        while (n != 1 && map.find(n) == map.end()) {
            // 计算下一个数
            int next = 0;
            int temp = n;
            while (temp > 0) {
                // 个位
                int digit = temp % 10;
                next += digit * digit;
                // 去掉个位
                temp /= 10;
            }
            cout << next << " ";
            // 保存下个
            map[n] = next;
            // 更新 n
            n = next;
        }
        // 等于1  是快乐数
        // 存在与 map 不是快乐数
        return n == 1 || map.find(n) == map.end();
    }

    /**
     * 法2：快慢指针法
     * 本质是判断是否有循环，可以参照判断链表有环的方法 141: 环形链表
     * 龟兔赛跑法
     */
    int getNext(int n) {
        // 计算下一个数
        int next = 0;
        int temp = n;
        while (temp > 0) {
            // 个位
            int digit = temp % 10;
            next += digit * digit;
            // 去掉个位
            temp /= 10;
        }
        // cout << next << " ";
        return next;
    }
    bool isHappy2(int n) {
        int slow = getNext(n);
        int fast = getNext(getNext(n));
        while (slow != fast) {
            slow = getNext(slow);
            fast = getNext(getNext(fast));
        }
        if (slow == 1 || fast == 1) return true;
        return false;
    }
};

int main() {
    Solution *s = new Solution();
    vector<int> list = {19, 2, 10};

    for (int i = 0; i < list.size(); i++) {
        auto ans = s->isHappy2(list[i]);
        cout << ans << endl;
    }
}