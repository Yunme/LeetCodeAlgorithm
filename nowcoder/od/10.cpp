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
 * 10.表演赛游戏分组
 * 有10名游戏玩家，其游戏玩家的水平评分为 Si，
 * 分为两队，一队5人，队伍的水平为各玩家水平之和，
 * 两队的游戏水平尽可能小，输出其最小差值的绝对值。
 * https://blog.csdn.net/weixin_48157259/article/details/138081905
 *
 * 输入:
 * 10个玩家的游戏水平评分
 * 输出：
 * 分成两队的实力实力差绝对值的最小值。
 */

/**
 * 回溯法
 */
int totalSum = 0;
int ans = INT_MAX;
void dfs(vector<int> &score, int pathSum, int pathLength, int index,
         int target) {
    if (pathSum > target) return;
    if (pathLength == 5) {
        ans = min(ans, totalSum - 2 * pathSum);
        return;
    }
    for (int i = index; i < score.size(); i++) {
        dfs(score, pathSum + score[i], pathLength + 1, i + 1, target);
    }
}

vector<int> minGroup1;

// 深度优先搜索函数
void dfs2(vector<int> &score, int idx, int count, int currentSum,
          vector<int> &group1) {
    // 当我们为一个队伍选择了5名玩家时
    if (count == 5) {
        cout << "id:" << idx << " count:" << count
             << " currentSum:" << currentSum;
        cout << " group:";
        for (int i : group1) cout << i << ",";
        cout << endl;

        // 计算另一个队伍的总和
        int otherTeamSum = totalSum - currentSum;
        // 用较小的差值更新结果
        if (abs(currentSum - otherTeamSum) < ans) {
            ans = abs(currentSum - otherTeamSum);
            minGroup1 = group1;
        }
        return;
    }
    // 如果我们已经考虑了所有玩家，停止递归
    if (idx == 10) {
        return;
    }
    // 为第一个队伍选择当前玩家
    group1.push_back(score[idx]);
    dfs2(score, idx + 1, count + 1, currentSum + score[idx], group1);
    group1.pop_back();
    // 不为第一个队伍选择当前玩家
    dfs2(score, idx + 1, count, currentSum, group1);
}

int minSumDifference(vector<int> &scores) {
    int minDiff = INT_MAX;
    vector<int> group1, group2;
    int target = totalSum / 2;

    dfs2(scores, 0, 0, 0, group1);

    cout << " minGroup1:";
    for (int i : minGroup1) cout << i << ",";
    cout << endl;
    return ans;
}

int main() {
    int n = 10;
    vector<int> score(n);
    for (int i = 0; i < n; i++) {
        cin >> score[i];
        // score[i] = i + 1;
        totalSum += score[i];
    }
    // dfs(score, 0, 0, 0, totalSum / 2);
    ans = minSumDifference(score);
    cout << ans << endl;
}