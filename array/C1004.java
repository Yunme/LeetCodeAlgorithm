/**
 * 1004:最大连续1的个数 III
 * 给定一个二进制数组 nums 和一个整数 k，如果可以翻转最多 k 个 0 ，则返回 数组中连续 1 的最大个数 。
 * 
 * https://leetcode.cn/problems/max-consecutive-ones-iii/description/
 */
public class C1004 {

    /**
     * 滑动窗口法 O(n) O(1)
     */
    static public int longestOnes(int[] nums, int k) {
        int n = nums.length;
        int start = 0, end = 0;
        int ans = 0;
        // 窗口内 0 的个数
        int windowZero = 0;
        while (end < n) {
            int i = nums[end];
            if (i == 0) { // 是0
                // 个数+1
                windowZero++;
            }
            // 个数大于0，左侧收缩，直到窗口里0 <= k
            while (windowZero > k) {
                if (nums[start] == 0) windowZero--;
                start++;
            }
            // 更新结果
            ans = Math.max(ans, end - start + 1);
            end++;
        }
        return ans;
    }


    public static void main(String[] args) {
        int[][] array1 = {{1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0},
                {0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1},
                {0, 0, 0, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 0, 0, 0, 1, 1, 1, 1}};
        int[] array2 = {2, 3, 4, 3, 0};
        for (int i = 0; i < array1.length; i++) {
            Object ans = longestOnes(array1[i], array2[i]);
            System.out.println(ans);
        }
    }
}
