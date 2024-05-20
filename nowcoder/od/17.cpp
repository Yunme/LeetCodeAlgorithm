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
 * 17. 石头剪刀步游戏
 * 石头剪刀布游戏有 3 种出拳形状：石头、剪刀、布。分别用字母 A , B , C 表示。
 * 游戏规则:
 * 1. 出拳形状之间的胜负规则如下： A > B；B > C；C >
 *    A；">"左边一个字母，表示相对优势形状。右边一个字母，表示相对劣势形状。
 *
 * 2.当本场次中有且仅有一种出拳形状优于其它出拳形状，则该形状的玩家是胜利者。否则认为是平局。
 * 3. 当发生平局，没有赢家。有多个胜利者时，同为赢家。
 * https://blog.csdn.net/weixin_48157259/article/details/138228565
 *
 * 输入:
 * 若干行
 * 第一个为玩家名称（小写字母和数字组成） 第二个为玩家出拳（A、B、C）空格隔开
 * 输出：
 * 赢家的玩家名称一个或多个，每个id一行，按字符串升序排序。
 * 如果没有赢家（平局）输出 NULL。
 */

/**
 * 只有 A 和 B，A赢
 * 只有 A 和 C，C赢
 * 只有 B 和 C，B赢
 */
vector<string> getWinner(unordered_map<string, vector<string>> map) {
    vector<string> ans;
    // 三种情况，A、B、C只有一个赢。
    if (map.count("A") > 0 && map.count("B") > 0) {
        return map["A"];
    } else if (map.count("A") > 0 && map.count("C") > 0) {
        return map["C"];
    } else if (map.count("B") > 0 && map.count("C") > 0) {
        return map["B"];
    }
    return {};
}

int main() {
    string name, cc;
    unordered_map<string, vector<string>> map;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) break;
        istringstream iss(line);
        if (iss >> name >> cc) {
            map[cc].push_back(name);
        }
    }

    // 三种都有 或只有一种，就是平局
    if (map.size() == 3 || map.size() == 1) {
        cout << "NULL" << endl;
    } else {
        auto ans = getWinner(map);
        sort(ans.begin(), ans.end());
        for (auto i : ans) {
            cout << i << endl;
        }
    }
}