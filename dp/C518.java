
/**
 * 518: 零钱兑换II
 * 给你一个整数数组 coins 表示不同面额的硬币，另给一个整数 amount 表示总金额。
 * 请你计算并返回可以凑成总金额的硬币组合数。如果任何硬币组合都无法凑出总金额，返回 0 。
 * 假设每一种面额的硬币有无限个。
 * 题目数据保证结果符合 32 位带符号整数。
 *
 * https://leetcode.cn/problems/coin-change-ii/description/
 */
public class C518 {
    /**
     * 转化为完全背包问题
     * 物品：硬币
     * 背包容量 amount
     * 重量 = 价值
     */
    static public int change(int amount, int[] coins) {
        int n = coins.length;
        // dp[i][j]: [0,i) 的硬币能组成 j 的组合数
        int[][] dp = new int[n + 1][amount + 1];
        // 初始化 选0个硬币组成金额0组合数 视为1
        dp[0][0] = 1;
        // 转移方程为 :
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < amount + 1; j++) {
                if (j >= coins[i - 1]) {
                    // 金额够
                    // 不选 i + 选 i 的组合数
                    // 选 i 的组合数：前面已经凑齐了 j-coin ，现在就差 coin 的组合数
                    dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]];
                } else {
                    // 金额不够，只能不选
                    // 不选 i 的组合数
                    dp[i][j] = dp[i - 1][j];

                }
            }
        }

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < amount + 1; j++) {
                System.out.print(dp[i][j] + " ");
            }
            System.out.println();
        }

        return dp[n][amount];
    }

    /**
     * 动态规划 空间压缩
     * dp[i][j] 只与 dp[i-1][j] 和 dp[i][..] 上方和左侧有关
     */
    static public int change2(int amount, int[] coins) {
        int n = coins.length;
        // dp[i][j]: [0,i) 的硬币能组成 j 的组合数
        int[] dp = new int[amount + 1];
        // 初始化 选0个硬币组成金额0组合数 视为1
        dp[0] = 1;
        // 转移方程为 : 
        for (int i = 0; i < n; i++) {
            for (int j = coins[i]; j < amount + 1; j++) {
                // 金额够
                // 不选 i + 选 i 的组合数
                // 选 i 的组合数：前面已经凑齐了 j-coin ，现在就差 coin 的组合数
                dp[j] = dp[j] + dp[j - coins[i]];
            }
        }

        for (int j = 0; j < amount + 1; j++) {
            System.out.print(dp[j] + " ");
        }
        System.out.println();

        return dp[amount];
    }

    public static void main(String[] args) {
        int[][] coins = { { 1, 2, 5 }, { 2 }, { 10 } };
        int[] amount = { 5, 3, 10 };

        for (int i = 0; i < coins.length; i++) {
            int ans = change2(amount[i], coins[i]);
            System.out.println(ans);
        }
    }
}
