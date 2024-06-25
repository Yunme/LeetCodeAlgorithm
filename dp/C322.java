import java.util.Arrays;

/**
 * 322: 零钱兑换
 * 给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。
 * 计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。
 * 
 * 你可以认为每种硬币的数量是无限的。
 *
 * https://leetcode.cn/problems/coin-change/description/
 */
public class C322 {
    /**
     * 动态规划
     * dp 数组表示 兑换金额i所需最少的硬币数量
     * 转换为子问题的解
     * 状态转移方程为： i 数额减去各个面额后的 dp[i-c(j)] 最小值 + 1；
     * 比如 11 {1，2，5}
     * dp[11] = min(dp[11 - 1], dp[11 - 2], dp[11 - 5]) + 1;
     */
    static public int coinChange(int[] coins, int amount) {
        int[] dp = new int[amount + 1];
        dp[0] = 0; // 金额0无法用硬币组成
        for (int i = 1; i <= amount; i++) {
            // 找出减去一个各面额 剩余金额的dp
            int min = Integer.MAX_VALUE;
            for (int coin : coins) {
                // 硬币面额要小于等于金额
                if (i - coin >= 0 && min > dp[i - coin]) {
                    // 状态转移，找到最小硬币数
                    min = dp[i - coin] + 1;
                }
            }
            dp[i] = min;
            System.out.print(dp[i] + " ");
        }
        System.out.println();
        return dp[amount] == Integer.MAX_VALUE ? -1 : dp[amount];
    }

    /**
     * 动态规划
     * 这里需要求的是个数，与顺序无关，排列(在意顺序) 组合(不在意顺序，比排列数要小)
     * 完全背包问题（一维空间）：求排列：先遍历背包，后物品，求组合：先物品，后背包
     */
    static public int coinChange2(int[] coins, int amount) {
        int[] dp = new int[amount + 1];
        Arrays.fill(dp, amount + 1);
        dp[0] = 0; // 金额0无法用硬币组成
        for (int coin : coins) {
            for (int i = coin; i <= amount; i++) {
                // 找出减去一个各面额 剩余金额的dp
                // 硬币面额要小于等于金额
                dp[i] = Math.min(dp[i], dp[i - coin] + 1);
                // System.out.print(dp[i] + " ");
            }
        }
        System.out.println();
        return dp[amount] == amount + 1 ? -1 : dp[amount];
    }

    public static void main(String[] args) {
        int re = (int) Math.pow(10, Math.floor(Math.log10(1999)));
        // System.out.println(re);
        int[][] coins = { { 1, 2, 5 }, { 2 }, { 1 }, { 1, 2, 5 }, { 186, 419, 83, 408 } };
        int[] amount = { 11, 3, 0, 2002, 6249 };

        for (int i = 0; i < coins.length; i++) {
            int ans = coinChange2(coins[i], amount[i]);
            System.out.println(ans);
        }
    }
}
