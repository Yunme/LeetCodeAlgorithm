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
 * 15: 三数之和
 * 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]]
 * 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0
 * 请你返回所有和为 0 且不重复的三元组。
 * https://leetcode.cn/problems/3sum/description/
 */
class Solution {
   public:
    /**
     * 升序排序后，从第1个 nums[1] 开始遍历，
     * i指针从第2个开始，j指针从最后一个，
     * 向中间逼近，找 nums[i] + nums[j] = -nums[1].
     * 那么 nums[i] + nums[j] + nums[1] = 0
     */
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        int count = nums.size();
        for (int k = 0; k < count - 2; k++) {
            int pivot = nums[k];
            // 基准跟上个相同
            if (k > 0 && pivot == nums[k - 1]) {
                continue;
            }
            int target = -pivot;
            int j = count - 1;
            for (int i = k + 1; i < count - 1; i++) {
                int left = nums[i];
                // 跟上个相同
                if (i > k + 1 && nums[i - 1] == left) {
                    continue;
                }

                // 太大了 right 处的大值左移，找较小的值
                while (j > i && left + nums[j] > target) j--;
                if (j <= i) break;
                int right = nums[j];
                if (left + right == target) {
                    // 得到一组
                    ans.push_back({pivot, left, right});
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> array = {{-1, 0, 1, 2, -1, -4},
                                 {0, 1, 1},
                                 {0, 0, 0},
                                 {0, 0, 0, 0},
                                 {-2, 0, 0, 2, 2}};

    for (size_t i = 0; i < array.size(); i++) {
        vector<vector<int>> arr = s->threeSum(array[i]);
        for (auto j : arr) {
            for (auto k : j) cout << k << " ";
            cout << ",";
        }
        cout << endl;
    }
}