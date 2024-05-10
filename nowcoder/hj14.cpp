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
 * hj14 字符串排序
 * 按字符顺序排序
 * https://www.nowcoder.com/practice/5af18ba2eb45443aa91a11e848aa6723
 */

/**
 * 法1：库函数
 */
void sortInput() {
    int n;
    cin >> n;
    vector<string> res(n);
    for (int i = 0; i < n; i++) cin >> res[i];
    sort(res.begin(), res.end());
    for (string s : res) cout << s << endl;
}

/**
 * 法2：自己实现
 * 快排
 */
int quickPartition(vector<string> &strings, int low, int high) {
    string pivot = strings[low];
    while (low < high) {
        while (low < high && strings[high] >= pivot) --high;
        strings[low] = strings[high];
        while (low < high && strings[low] <= pivot) ++low;
        strings[high] = strings[low];
    }
    strings[low] = pivot;
    return low;
}
void quickSort(vector<string> &strings, int low, int high) {
    if (low < high) {
        int pivot = quickPartition(strings, low, high);
        quickSort(strings, low, pivot - 1);
        quickSort(strings, pivot + 1, high);
    }
}

void sortStrings(vector<string> &strings) {
    quickSort(strings, 0, strings.size() - 1);
}

int main() {
    // string a[] = {"cap", "to", "cat", "card", "up"};
    // for (string s : a) {
    //     arr.push_back(s);
    // }
    int n;
    cin >> n;
    vector<string> arr(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        arr[i] = s;
    }
    sortStrings(arr);
    for (string s : arr) {
        cout << s << endl;
    }

    return 0;
}