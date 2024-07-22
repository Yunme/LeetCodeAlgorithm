#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 860：柠檬水找零
 *
 * 在柠檬水摊上，每一杯柠檬水的售价为 5 美元。顾客排队购买你的产品，（按账单
 * bills 支付的顺序）一次购买一杯。 每位顾客只买一杯柠檬水，然后向你付 5
 * 美元、10 美元或 20
 * 美元。你必须给每个顾客正确找零，也就是说净交易是每位顾客向你支付 5 美元。
 * 注意，一开始你手头没有任何零钱。
 * 给你一个整数数组 bills ，其中 bills[i] 是第 i 位顾客付的账。
 * 如果你能给每位顾客正确找零，返回 true ，否则返回 false 。
 *
 * bills[i] 不是 5 就是 10 或是 20
 * https://leetcode.cn/problems/lemonade-change/description/
 */

class Solution {
   public:
    /**
     * 贪心思想
     * 找钱先找面额大的
     */
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;
        int n = bills.size();
        for (int i = 0; i < n; i++) {
            int bill = bills[i];
            if (bill == 5) {
                five++;
            } else {
                if (bill == 10) {
                    five--;
                    ten++;
                } else if (bill == 20) {
                    if (ten > 0) {
                        ten--;
                        five--;
                    } else {
                        five -= 3;
                    }
                }
            }
            if (five < 0 || ten < 0) return false;
        }
        return true;
    }
};

int main() {
    Solution* solution = new Solution();
    vector<vector<int>> bills = {{5, 5, 5, 10, 20},
                                 {5, 5, 10, 10, 20},
                                 {5, 5, 5, 5, 20, 20, 5, 5, 5, 5}};
    for (int i = 0; i < bills.size(); i++) {
        int ans = solution->lemonadeChange(bills[i]);
        cout << ans << endl;
    }
}