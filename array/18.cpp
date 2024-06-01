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
 * 18: 四数之和
 * 给你一个由 n 个整数组成的数组 nums ，和一个目标值 target
 * 请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c],
 * nums[d]] （若两个四元组元素一一对应，则认为两个四元组重复）：
 * https://leetcode.cn/problems/4sum/description/
 */
class Solution {
   public:
    /**
     * 多指针法 自己实现
     * 升序排序后
     * i j 依次在左边
     * left = j + 1
     * right = n - 1
     */
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int count = nums.size();
        vector<vector<int>> ans;
        if (count < 4) return ans;
        sort(nums.begin(), nums.end());
        if (nums[0] > target) return ans;
        for (int i = 0; i < count - 3; i++) {
            // 跳过与上个重复的数
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < count - 2; j++) {
                // 跳过与上个重复的数
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;
                // 左边之和
                int sum1 = nums[i] + nums[j];
                // 小于右边最小的两个，无解
                if (((long)target - sum1) < nums[j + 1] + nums[j + 2]) break;
                // 右边之和
                if ((long)target - sum1 > nums[count - 2] + nums[count - 1])
                    continue;  // 左边太小，j需要右移

                // 接下来是 j 起始的三数之和
                int left = j + 1, right = count - 1;
                while (left < right) {
                    // 相等得到一组
                    if (target - sum1 == nums[left] + nums[right]) {
                        ans.push_back(
                            {nums[i], nums[j], nums[left], nums[right]});
                        // left ++ 找下个不同的
                        while (left < right && nums[left] == nums[++left]);
                        // right -- 找下个不同的
                        while (left < right && nums[right] == nums[--right]);
                    } else if (target - sum1 > nums[left] + nums[right]) {
                        // 太小 左边 left ++
                        left++;
                    } else {
                        right--;
                    }
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> array = {{1, 0, -1, 0, -2, 2},
                                 {2, 2, 2, 2, 2, 2, 3, 2},
                                 {-2, -1, 0, 1, 2, 3},
                                 {-3, -1, 0, 2, 4, 5}};
    vector<int> target = {0, 8, 2, 2};
    cout << INT_MAX << endl;

    for (size_t i = 0; i < array.size(); i++) {
        vector<vector<int>> arr = s->fourSum(array[i], target[i]);
        for (auto j : arr) {
            for (auto k : j) cout << k << " ";
            cout << ",";
        }
        cout << endl;
    }
}