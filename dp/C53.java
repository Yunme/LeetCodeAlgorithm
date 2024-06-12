
/**
 * 53：最大子数组之和
 * 
 * 给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
 * 
 * 子数组是数组中的一个连续部分。
 *
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/description/
 */
public class C53 {

    /**
     * 法1：动态规划
     * dp 数组表示 以第i个数结尾的 连续子数组的最大和
     * 转移方程：dp[i] = 取决于 nums[i] 加入 dp[i-1] 还是 不加入
     * 这又取决于 max(dp[i-1] + nums[i] , nums[i])
     */
    public static int maxSubArray(int[] nums) {
        int n = nums.length;
        // 空间可以压缩
        int[] dp = new int[n];
        dp[0] = nums[0];
        int ans = nums[0];
        for (int i = 1; i < n; i++) {
            // 状态转移：取大者
            dp[i] = Math.max(nums[i], dp[i - 1] + nums[i]);
            ans = Math.max(ans, dp[i]);
        }
        return ans;
    }

    /**
     * 上述动态规划 压缩空间
     * 当前状态只跟上一个有关
     */
    public static int maxSubArray2(int[] nums) {
        int n = nums.length;
        // 空间可以压缩
        int pre = nums[0];
        int ans = nums[0];
        for (int i = 1; i < n; i++) {
            pre = Math.max(nums[i], pre + nums[i]);
            ans = Math.max(ans, pre);
        }
        return ans;
    }

    public static void main(String[] args) {
        int[][] array1 = {{-2, 1, -3, 4, -1, 2, 1, -5, 4}, {1}, {5, 4, -1, 7, 8}};
        int[][] array2 = {{1}};
        for (int i = 0; i < array1.length; i++) {
            Object ans = maxSubArray2(array1[i]);
            System.out.println(ans);
        }
    }
}
