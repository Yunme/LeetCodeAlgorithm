#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iomanip>
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
 * hj16 购物单
 * 物品分为主件附件（附件可没有），每个物品有重要程度
 * 只要买附件，必须买主见。每个物品只能买一次，每个物品附件最多2个。
 * 满意度：累加：物品的价格 x 重要程度 （物品价格是10的整数倍）
 * 给出一定的总钱数和购买件数，算出最大的满意度
 * https://www.nowcoder.com/practice/f9c6f980eeec43ef85be20755ddbeaf4
 */

struct Goods {
    int price;
    int value;
    int attachIndex;  // 是数组中某个的附件 从1开始。
    vector<Goods> attachments = vector<Goods>(2);  // 附件
    Goods() : price(0), value(0), attachIndex(0), attachments({}){};
    Goods(int price) : price(price), value(0), attachIndex(0){};
    Goods(int price, int value) : price(price), value(value), attachIndex(0){};
    Goods(int price, int value, int attachIndex)
        : price(price), value(value), attachIndex(attachIndex){};
};

/**
 * 不考虑附件的情况
 * 所有的物品只有主件
 *
 * 即经典 0-1背包问题
 * 货物：物品
 * 价格：重量
 * 满足感：价值
 * 只不过 这里的总满足感是价格*满足感
 */
int maxValueTest(int totalMoney, vector<Goods> list) {
    int m = list.size();
    // 买前i个物品当中的物品(买i-1或买 i-2或都买)，花费<= j 元钱时的最大满意度
    // int dp[m + 1][totalMoney + 1] = {0};
    vector<vector<int>> dp(m + 1, vector<int>(totalMoney + 1));

    for (int i = 1; i < m + 1; i++) {
        int price = list[i - 1].price;
        int value = list[i - 1].value;
        for (int j = 1; j < totalMoney + 1; j++) {
            // 第 i 个物品，最大j元钱
            // 当前钱数 j 能否购买物品 i ；
            if (j >= price) {
                // 不买当前物品i，花费不超过j的最大满意度
                int nobuyI = dp[i - 1][j];
                // 买当前物品i，花费不超过j的最大满意度

                // 等于 当前物品的满意度 +
                // 不买当前物品，花费剩下的钱的最大满意度
                int buyI = value + dp[i - 1][j - price];
                dp[i][j] = max(nobuyI, buyI);
            } else {
                // 当前物品i 价格大于当前钱数 j
                // 买当前物品i，花费不超过j元钱的最大满意度
                // 等于 不买当前物品i 花费不超过j元钱的最大满意度
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    for (int i = 0; i < m + 1; i++) {
        for (int j = 0; j < totalMoney + 1; j++) {
            cout << setw(2) << right << dp[i][j] << " ";
        }
        cout << endl;
    }
    return dp[m][totalMoney];
}

/**
 * 考虑附件情况
 * 购买有附件的物品时，可以购买0，1，2个
 * 即：主件、主件+附件1、主件+附件2、主件+附件1+附件2
 */
int maxValue(int totalMoney, const vector<Goods> &list) {
    int m = list.size();
    // 买前i个物品当中的物品(买i-1或买 i-2或都买)，花费<= j 元钱时的最大满意度
    // int dp[m + 1][totalMoney + 1] = {0};
    vector<vector<int>> dp(m + 1, vector<int>(totalMoney + 1));

    for (int i = 1; i < m + 1; i++) {
        int price = list[i - 1].price;
        int value = list[i - 1].value;
        vector<Goods> attachments = list[i - 1].attachments;
        // 枚举三种附件情况
        int attachPrice1 = attachments[0].price;
        int attachValue1 = attachments[0].value;
        int attachPrice2 = attachments[1].price;
        int attachValue2 = attachments[1].value;
        int attachPrice3 = attachPrice1 + attachPrice2;
        int attachValue3 = attachValue1 + attachValue2;
        for (int j = 1; j < totalMoney + 1; j++) {
            // 第 i 个物品，最大j元钱
            // 当前钱数 j 能否购买物品 i ；
            // 只购买主件
            if (j >= price) {
                // 不买当前物品i，花费不超过j的最大满意度
                int nobuyI = dp[i - 1][j];
                // 买当前物品i，花费不超过j的最大满意度
                // 当有附件时，找出购买附件组合中的最大满意度
                //
                // 等于 当前物品的满意度 +
                // 不买当前物品，花费剩下的钱的最大满意度
                int buyI = value + dp[i - 1][j - price];
                dp[i][j] = max(nobuyI, buyI);
            } else {
                // 当前物品i 价格大于当前钱数 j
                // 买当前物品i，花费不超过j元钱的最大满意度
                // 等于 不买当前物品i 花费不超过j元钱的最大满意度
                dp[i][j] = dp[i - 1][j];
            }

            // 有限个附件，枚举
            int nobuy = dp[i][j];
            int buy = 0;
            // 买主件 + 第一个附件
            if (j >= price + attachPrice1) {
                buy =
                    dp[i - 1][j - price - attachPrice1] + value + attachValue1;
            }
            // 买主件 + 第二个附件
            if (j >= price + attachPrice2) {
                buy =
                    dp[i - 1][j - price - attachPrice2] + value + attachValue2;
            }
            // 买主件 + 第一个 + 第二个附件
            if (j >= price + attachPrice3) {
                buy =
                    dp[i - 1][j - price - attachPrice3] + value + attachValue3;
            }
            dp[i][j] = max(nobuy, buy);
        }
    }
    for (int i = 0; i < m + 1; i++) {
        for (int j = 0; j < totalMoney + 1; j++) {
            cout << setw(2) << right << dp[i][j] << " ";
        }
        cout << endl;
    }
    return dp[m][totalMoney];
}

/**
 * 空间复杂度优化
 * 因为只依赖前一个状态。
 * 所以 dp 里存的就是当前状态。
 * 访问时从后向前遍历，数组里存的就是上一次的状态
 */
int maxValue2(int totalMoney, const vector<Goods> &list) {
    int m = list.size();
    // 买前i个物品当中的物品(买i-1或买 i-2或都买)，花费<= j 元钱时的最大满意度
    // int dp[m + 1][totalMoney + 1] = {0};
    vector<int> dp(totalMoney + 1);

    for (int i = 1; i < m + 1; i++) {
        int price = list[i - 1].price;
        int value = list[i - 1].value;
        vector<Goods> attachments = list[i - 1].attachments;
        // 枚举三种附件情况
        int attachPrice1 = attachments[0].price;
        int attachValue1 = attachments[0].value;
        int attachPrice2 = attachments[1].price;
        int attachValue2 = attachments[1].value;
        int attachPrice3 = attachPrice1 + attachPrice2;
        int attachValue3 = attachValue1 + attachValue2;
        for (int j = totalMoney; j >= 1; j--) {
            // 第 i 个物品，最大j元钱
            // 当前钱数 j 能否购买物品 i ；
            // 只购买主件
            if (j >= price) {
                // 不买当前物品i，花费不超过j的最大满意度
                int nobuyI = dp[j];
                // 买当前物品i，花费不超过j的最大满意度
                // 当有附件时，找出购买附件组合中的最大满意度
                //
                // 等于 当前物品的满意度 +
                // 不买当前物品，花费剩下的钱的最大满意度
                int buyI = value + dp[j - price];
                dp[j] = max(nobuyI, buyI);
            } else {
                // 当前物品i 价格大于当前钱数 j
                // 买当前物品i，花费不超过j元钱的最大满意度
                // 等于 不买当前物品i 花费不超过j元钱的最大满意度
                dp[j] = dp[j];
            }

            // 有限个附件，枚举
            int nobuy = dp[j];
            int buy = 0;
            // 买主件 + 第一个附件
            if (j >= price + attachPrice1) {
                buy = dp[j - price - attachPrice1] + value + attachValue1;
            }
            // 买主件 + 第二个附件
            if (j >= price + attachPrice2) {
                buy = dp[j - price - attachPrice2] + value + attachValue2;
            }
            // 买主件 + 第一个 + 第二个附件
            if (j >= price + attachPrice3) {
                buy = dp[j - price - attachPrice3] + value + attachValue3;
            }
            dp[j] = max(nobuy, buy);
        }
    }

    for (int j = 0; j < totalMoney + 1; j++) {
        cout << setw(2) << right << dp[j] << " ";
    }
    cout << endl;
    return dp[totalMoney];
}

int main() {
    // 输入
    // 所有钱是10的整数倍 除以10，以节省DP的复杂度
    int factor = 10;
    int totalMoney = 2000, goodsCount = 10;
    // cin >> totalMoney >> goodsCount;

    vector<Goods> list;
    // vector<Goods> list(goodsCount);
    // list.emplace_back(60, 8);
    // list.emplace_back(20, 4, 1);
    // list.emplace_back(30, 6);
    // list.emplace_back(50, 10, 1);

    list.emplace_back(500, 1, 0);
    list.emplace_back(400, 4, 0);
    list.emplace_back(300, 5, 1);
    list.emplace_back(400, 5, 1);
    list.emplace_back(200, 5, 0);
    list.emplace_back(500, 4, 5);
    list.emplace_back(400, 4, 0);
    list.emplace_back(320, 2, 0);
    list.emplace_back(410, 3, 0);
    list.emplace_back(400, 3, 5);

    vector<Goods> goods;
    totalMoney /= factor;
    // for (int i = 0; i < goodsCount; i++) {
    //     int price, value, attachIndex;
    //     cin >> price >> value >> attachIndex;
    //     Goods s(price, value, attachIndex);
    //     list[i] = s;
    // }

    // 数据处理
    // 将附件物品作为主件的成员存储
    for (int i = 0; i < list.size(); i++) {
        Goods &goods = list[i];
        goods.price /= factor;
        // 直接算好单个物品的总满意度
        goods.value *= goods.price;
        // 附件最多两个
        if (goods.attachIndex) {
            vector<Goods> &attachments =
                list[goods.attachIndex - 1].attachments;
            if (attachments[0].price) {
                attachments[1] = goods;
            } else {
                attachments[0] = goods;
            }
        }
    }

    // 删除列表中的附件物品
    auto it = list.begin();
    while (it != list.end()) {
        if ((*it).attachIndex > 0) {
            list.erase(it);
        } else {
            it++;
        }
    }

    for (Goods good : list) {
        cout << good.price << " " << good.value << ": attach:";
        for (Goods a : good.attachments) {
            cout << a.price << " " << a.value << ",";
        }
        cout << endl;
    }

    cout << maxValue2(totalMoney, list) * factor;
}