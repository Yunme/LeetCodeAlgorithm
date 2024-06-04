#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 704: 二分查找
 * 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，
 * 写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
 *
 * https://leetcode.cn/problems/binary-search/description/
 */
class Solution {
   public:
    /**
     * 常规二分查找
     * 注意边界
     */
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        int low = 0;
        int high = nums.size() - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (target == nums[mid]) {
                return mid;
            } else if (target < nums[mid]) {
                high = mid - 1; // mid 已经在上面检查过了 排除
            } else {
                low = mid + 1;
            }
        }
        return -1;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> array = {{-1, 0, 3, 5, 9, 12}, {-1, 0, 3, 5, 9, 12}};
    vector<int> target = {9, 2};

    for (size_t i = 0; i < array.size(); i++) {
        vector<int> arr = array[i];
        auto ans = s->search(arr, target[i]);
        cout << ans << endl;
    }
}