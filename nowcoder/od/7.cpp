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
 * https://blog.csdn.net/weixin_48157259/article/details/138087531
 *
 * 7. 社交距离
 * 会议室一共 N 个座位，编号 0~N-1，要求员工一个接一个进出会议室
 *
 * 要求：每当一个员工进入，需要坐到最大社交距离位置，
 * （例如：位置A与左右有员工落座的位置距离分别为2和2，
 * 位置B与左右有员工落座的位置距离分别为2和3，影响因素都为2个位置，
 * 则认为座位A和B与左右位置的社交距离是一样的)；
 * 如果有多个这样的座位，则坐到索引最小的那个座位。
 *
 * https://blog.csdn.net/weixin_48157259/article/details/138087347
 *
 * 输入:
 * 1.座位数 N
 * 2.员工进出顺序数组：1 表示进场，负数表示出场，-4代表 4号位出场。
 * 输出：
 * 最后进来的员工，会坐在第几个位置，如果已满，输出-1；
 */

int takeSeat(vector<int> &seat, int &seatedNum) {
    if (seat.size() == seatedNum) return -1;
    if (seatedNum == 0) {
        seatedNum++;
        seat[0] = 1;
        return 0;
    } else {
        // 算出最大距离的位置
        int index1 = -1;  // 第一个是1的位置
        int index2 = -1;  // 第二个是1的位置
        int dis = 0;      // 当前最大的距离
        int pos = 0;      // 当前可坐的位置

        for (int i = 0; i < seat.size(); i++) {
            if (index1 == -1 && seat[i] == 1) {
                index1 = i;
            } else if (index1 >= 0 && seat[i] == 1) {
                index2 = i;
                int tempDis = (index1 + index2) / 2 - index1;
                if (tempDis > dis) {
                    dis = tempDis;
                    pos = (index1 + index2) / 2;
                }
                index1 = index2;
                index2 = 0;
            }
        }
        if (index2 == -1) {
            pos = seat.size() - 1;
        }
        cout << "pos:" << pos << endl;
        seatedNum++;
        seat[pos] = 1;
        return pos;
    }
}

int lastPosition(int n, vector<int> &list) {
    vector<int> seat(n);
    int seatedNum = 0;
    int pos = 0;
    for (int ac : list) {
        if (ac == 1) {
            pos = takeSeat(seat, seatedNum);
        } else {
            seatedNum--;
            // 出场
            seat[abs(ac)] = 0;
        }
    }
    return pos;
}

int main() {
    int n = 100;
    vector<int> list = {1, 1, 1, 1, -4, 1, 1, 1, 1, 1};
    // vector<int> list = {1};

    int ans = lastPosition(n, list);
    cout << ans << endl;
}