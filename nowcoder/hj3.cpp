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
 * hj3 明明的随机数
 * 从n个随机数中去除重复的数字，然后排序
 * https://www.nowcoder.com/practice/3245215fffb84b7b81285493eae92ff0
 */

/**
 * 冒泡
 */
void sortArray(vector<int>& nums) {
    int len = nums.size();
    for (int i = 0; i < len; i++) {
        for (int j = 1; j < len - i; j++) {
            if (nums[j - 1] > nums[j]) {
                swap(nums[j - 1], nums[j]);
            }
        }
    }
}

bool contain(vector<int>& nums, int i) {
    for (int j : nums) {
        if (j == i) {
            return true;
        }
    }
    return false;
}

int main() {
    int n = 0;
    cin >> n;
    vector<int> nums;
    // unordered_set<int> nums; 无序
    // set<int> nums; 有序 从小到达  java TreeSet
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (!contain(nums, a)) {
            nums.push_back(a);
        }
    }
    sortArray(nums);
    for (int i : nums) {
        cout << i << endl;
    }
}