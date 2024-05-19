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
 * https://blog.csdn.net/qfc_128220/article/details/127914382
 *
 * 4. 身高体重排序
 * 对 n 个同学进行排序，其序号是 1、2、3...n
 * 先按身高由低到高，对身高相同的，按体重由轻到重。
 * 对于都相同的，维持原有编号顺序。
 *
 * https://blog.csdn.net/weixin_48157259/article/details/138011048
 *
 * 输入
 * 第一行：n 代表n个学生
 * 第二行：身高序列
 * 第三行：体重序列
 * 输出：原序号顺序
 */
struct Student {
    int no;
    int height;
    int weight;
};

/**
 * 🤭 库函数大法
 */
void sortList(vector<Student> &list) {
    sort(list.begin(), list.end(), [](const Student &s1, const Student &s2) {
        return s1.height < s2.height ||
               s1.height == s2.height && s1.weight < s2.weight;
    });
}

int main() {
    int n = 2;
    cin >> n;
    vector<Student> list(n);
    for (int i = 0; i < n; i++) {
        list[i].no = i + 1;
        cin >> list[i].height;
    }
    for (int i = 0; i < n; i++) {
        cin >> list[i].weight;
    }
    sortList(list);

    for (Student &s : list) {
        cout << s.no << " ";
    }
    cout << endl;
}