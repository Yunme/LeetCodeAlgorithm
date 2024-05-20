#include <math.h>

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
// #include <sstream>
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
 * 18. 最多可以派出多少支队伍
 * 用数组代表每个人的能力，一个比赛活动要求参赛团队的最低能力值为N，
 * 每个团队可以由1人或2人组成，且1个人只能参加1个团队，请计算出最多可以派出多少支符合要求的团队?
 * https://blog.csdn.net/weixin_48157259/article/details/138868572
 *
 * 输入:
 * 第一行数组代表总人数，范围[1,500000]
 * 第二行数组代表每个人的能力，每个元素的取值范围[1,500000]，数组的大小范围[1,500000]
 * 第三行数值为团队要求的最低能力值，范围[1,500000]
 * 输出：
 * 最多可以派出的团队数量
 */

int maxTeam(vector<int> &array, int minVal) {
    // 排序
    sort(array.begin(), array.end());
    // 最小值都大于最低要求，每个人成一组
    if (array[0] >= minVal) return array.size();

    // 贪心 + 双指针
    int i = 0, j = array.size() - 1;
    int ans = 0;
    while (i < j) {
        // 左右逼近
        int left = array[i];
        int right = array[j];
        // 右边大的直接大于等于最小要求。单独一组。
        if (right >= minVal) {
            j--;
            ans++;
        } else if (left + right >= minVal) {
            // 左右相加大于等于最小要求，两人一组
            i++;
            j--;
            ans++;
        } else {
            // 左右相加小于最小要求，i右移
            i++;
        }
    }
    return ans;
}

int main() {
    int n;
    cin >> n;

    vector<int> array(n);
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }
    int minVal;
    cin >> minVal;

    cout << maxTeam(array, minVal) << endl;
}