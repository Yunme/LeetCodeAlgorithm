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
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * hj17 坐标移动
 * 坐标计算工具，输入指令，计算最后的坐标
 * A表示向左移动，D表示向右移动，W表示向上移动，S表示向下移动。
 * 指令按;隔开
 * 从（0,0）点开始移动，
 * 下面是一个简单的例子 如：A10;S20;W10;D30;X;A1A;B10A11;;A10;
 * https://www.nowcoder.com/practice/119bcca3befb405fbe58abe9c532eb29
 */

/**
 * 字符串按字符分割
 */
vector<string> splitString(string s, char delimiter) {
    vector<string> result;
    int start = 0;
    for (int i = 0; i < s.length(); i++) {
        char a = s[i];
        if (a == delimiter) {
            result.push_back(s.substr(start, i - start));
            start = i + 1;
        }
    }
    result.push_back(s.substr(start, s.length() - start));
    return result;
}

/**
 * 坐标移动
 */
pair<int, int> moveCoordinate(string commands) {
    vector<string> commandList = splitString(commands, ';');
    for (string s : commandList) {
        cout << s << " ";
    }
    cout << endl;
    // 命令
    vector<char> moveCommands = {'A', 'D', 'W', 'S'};
    pair<int, int> poistion(0, 0);
    for (string &s : commandList) {
        // 移动距离 <= 99
        if (s.length() > 1 && s.length() <= 3 &&
            find(moveCommands.begin(), moveCommands.end(), s[0]) !=
                moveCommands.end()) {
            int distance = 0;
            char move = s[0];
            if (s.length() == 2 && s[1] >= '0' && s[1] <= '9') {
                distance = s[1] - '0';
            } else if (s.length() == 3 && s[1] >= '0' && s[1] <= '9' &&
                       s[2] >= '0' && s[2] <= '9') {
                distance = 10 * (s[1] - '0') + s[2] - '0';
            }
            cout << distance << " " << endl;
            switch (move) {
                case 'A':
                    poistion.first -= distance;
                    break;
                case 'D':
                    poistion.first += distance;
                    break;
                case 'W':
                    poistion.second += distance;
                    break;
                case 'S':
                    poistion.second -= distance;
                    break;
                default:
                    break;
            }
        }
    }
    return poistion;
}

int main() {
    string commands = "A10;S20;W10;D30;X;A1A;B10A11;;A10";
    // cin >> commands;
    pair<int, int> position = moveCoordinate(commands);
    cout << position.first << "," << position.second << endl;
    return 0;
}