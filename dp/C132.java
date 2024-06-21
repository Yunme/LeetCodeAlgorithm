
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Deque;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * 132: 分割回文串 II
 * 
 * 给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是回文串。
 * 返回符合要求的 最少分割次数 。
 *
 * https://leetcode.cn/problems/palindrome-partitioning-ii/description/
 */

public class C132 {

    /**
     * 两次动态规划
     */
    static public int minCut(String s) {
        int n = s.length();
        // check[i][j] : s中 i到j 的子串是否是回文 s[i, j]
        boolean[][] check = new boolean[n][n];
        // 初始化
        // 单个字符都为回文
        for (int i = 0; i < n; i++) {
            check[i][i] = true;
        }
        // 转移方程为：check[i][j] = check[i+1][j-1] && s[i] == s[j]
        // i,j 的值依赖于左下角 i+1，j-1
        // 从列开始构建 dp 数组
        for (int j = 0; j < n; j++) {
            // j >= i 才有用
            for (int i = 0; i <= j; i++) {
                // 两头字符相等 且 j - i <= 2 长度为 2 或 3 时，肯定是回文
                if (s.charAt(i) == s.charAt(j) && (j - i <= 2 || check[i + 1][j - 1])) {
                    check[i][j] = true;
                }
            }
        }

        for (int i = 0; i < check.length; i++) {
            for (int j = 0; j < check.length; j++) {
                System.out.print(check[i][j] + " ");
            }
            System.out.println();
        }

        // 前缀 [0,i]的最少分割次数
        int[] dp = new int[n];
        Arrays.fill(dp, Integer.MAX_VALUE);
        // 转移方程为 [0, j, i] dp[j] + 1; 其中 s[j+1][i] 是回文
        for (int i = 0; i < dp.length; i++) {
            if (check[0][i]) { // s[0,i] 本身是回文串 不需要分割
                dp[i] = 0;
            } else {
                for (int j = 0; j < i; j++) { // 不是回文 从前面转移过来。
                    if (check[j + 1][i]) {
                        dp[i] = Math.min(dp[i], dp[j] + 1);
                    }
                }
            }
        }
        return dp[n - 1];
    }

    public static void main(String[] args) {
        String[] array = { "aab", "a", "ab" };
        for (int i = 0; i < array.length; i++) {
            int ans = minCut(array[i]);
            System.out.println(ans);
        }
    }
}
