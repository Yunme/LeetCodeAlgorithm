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
 * hj25 数据分类处理
 * 输入：一组输入整数序列I和一组规则整数序列R，I和R序列的第一个整数为序列的个数（个数不包含第一个整数）
 * 从R依次中取出R<i>，对I进行处理，找到满足条件的I：
 * I整数对应的数字需要连续包含R<i>对应的数字。比如R<i>为23，I为231，那么I包含了R<i>，条件满足
 *
 * 输出：
 * 后续输出整数的个数、
 * R<i>、I与R<i>满足条件的个数、
 * 依次输出满足条件的数在I中的索引 和 I。
 *
 * 注意：
 * 1. 按 R<i> 的由小到大输出，并去重，即先对 R<i> 进行排序；
 * 2. 如果对于 R<i> 在 I 中没有满足的条件的数，则 R<i> 不输出。
 *
 * https://www.nowcoder.com/practice/9a763ed59c7243bd8ab706b2da52b7fd
 */

/**
 * sourceNum 是否包含 num
 * 比如 23445 包含 23、234 344等
 */
bool numberContains(int sourceNum, int num) {
    return to_string(sourceNum).find(to_string(num)) != string::npos;
}

/**
 * 处理数据
 */
vector<int> processData(vector<int> &sourceNums, vector<int> &nums) {
    map<int, vector<int>> map;
    // map 存储 nums 数据为 key。自带排序
    // value 为对应的符合条件的 sourceNums 中的index
    for (int i = 0; i < nums.size(); i++) {
        int num = nums[i];
        map[num] = vector<int>();
        for (int j = 0; j < sourceNums.size(); j++) {
            int sourceNum = sourceNums[j];
            if (numberContains(sourceNum, num)) {
                map[num].push_back(j);
            }
        }
    }

    // 按照输出顺序保存到数组中。
    vector<int> result;
    for (auto &[k, v] : map) {
        if (v.size() > 0) {
            result.push_back(k);
            result.push_back(v.size());
            for (int i = 0; i < v.size(); i++) {
                int sourceIndex = v[i];
                result.push_back(sourceIndex);
                result.push_back(sourceNums[sourceIndex]);
            }
        }
    }
    result.insert(result.begin(), result.size());
    return result;
}

int main() {
    int iCount = 0;
    cin >> iCount;
    vector<int> sourceNums(iCount);
    for (int i = 0; i < iCount; i++) {
        cin >> sourceNums[i];
    }

    int rCount;
    cin >> rCount;
    vector<int> nums(rCount);
    for (int i = 0; i < rCount; i++) {
        cin >> nums[i];
    }

    // vector<int> sourceNums = {123, 456,    786, 453, 46,  7,   5,  3,
    //                           665, 453456, 745, 456, 786, 453, 123};
    // vector<int> nums = {6, 3, 6, 3, 0};
    vector<int> data = processData(sourceNums, nums);
    for (int i : data) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}