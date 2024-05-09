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
 * 80: 删除有序数组中的重复项 II 出现超过两次的只出现两次
 * 返回移除后数组的个数
 * https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii/description/
 */
class Solution {
   public:
    /**
     * 双指针： 时间 O(n) 空间 O(1)
     * 从 i = 2 开始，如果和 i - 2 不相等，赋值给 i
     * i 慢指针，[0..i] 中重复的不超过2个
     * j 快指针，[2, n) 寻找下个与 i - 2 不相等的；赋值给 i 的位置。
     * 直到j到达最后一个元素，i所在的位置就是最后一个不重复的元素。
     */
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) {
            return nums.size();
        }
        int i = 2;
        for (int j = 2; j < nums.size(); j++) {
            if (nums[j] != nums[i - 2]) {
                nums[i] = nums[j];
                i++;
            }
        }
        return i;
    }
};

int main() {
    Solution* s = new Solution();
    int array1[] = {0, 0, 1, 1, 1, 1, 2, 3, 3};
    vector<int> v1(array1, array1 + size(array1));

    int count = s->removeDuplicates(v1);

    for (int i = 0; i < count; i++) {
        cout << v1[i] << " ";
    }
}