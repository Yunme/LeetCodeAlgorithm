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
 * 26：删除有序数组中的重复项
 * 返回移除后数组的个数
 * https://leetcode.cn/problems/remove-duplicates-from-sorted-array/solutions
 */
class Solution {
   public:
    /**
     * 双指针： 时间 O(n) 空间 O(1)
     * i 慢指针，[0..i] 中的是不重复的；
     * j 快指针，[1, n) 寻找下个与 i 不相等的；赋值给i的下一个位置。
     * 直到j到达最后一个元素，i所在的位置就是最后一个不重复的元素。
     */
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size();
        int i = 0;
        for (int j = 1; j < nums.size(); j++) {
            if (nums[i] != nums[j]) {
                nums[++i] = nums[j];
            }
        }
        return i + 1;
    }
};

int main() {
    Solution* s = new Solution();
    int array1[] = {1, 2, 3, 4};
    vector<int> v1(array1, array1 + size(array1));

    int count = s->removeDuplicates(v1);

    for (int i = 0; i < count; i++) {
        cout << v1[i] << " ";
    }
}