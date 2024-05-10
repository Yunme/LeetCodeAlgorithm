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
#include <utility>
#include <vector>
using namespace std;

/**
 * hj8 合并表记录
 * 输入n行 index value
 * 相同的 index 的 value 相加
 * 按 index 升序输出 index value
 * https://www.nowcoder.com/practice/de044e89123f4a7482bd2b214a685201
 */

/**
 * 直接用 map 自带 index 有序和去重
 *
 * 自己实现 新建一个类或结构体成员 index value，放入到 vector 中；
 * 在插入数据时，查找 index 是否存在，存在则相加
 * 在 vector 中 按 index 排序。
 */
int main() {
    map<int, int> map;
    int index, value;
    int n = 5;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> index >> value;
        map[index] += value;
    }
    for (const auto& [key, value] : map) {
        cout << key << " " << value << endl;
    }
    return 0;
}