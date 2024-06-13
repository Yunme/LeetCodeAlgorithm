import java.util.*;

/**
 * 139：单词拆分
 * 给你一个字符串 s 和一个字符串列表 wordDict 作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。
 * 注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。
 * 
 * https://leetcode.cn/problems/word-break/description/
 */

public class C139 {

    /**
     * 字符串分配问题 O(n^2) O(n)
     * 动态规划
     * dp 数组为: 前 i 个字符组成的字符串能否被拆分成若干个字典里的单词
     * 转移方程为 检查 0~i中的位置 j，dp[j] == true && j~i部分是在词典里
     */
    static public boolean wordBreak(String s, List<String> wordDict) {
        int n = s.length();
        // 转成 set 方便查找
        Set<String> set = new HashSet<>(wordDict);
        // 定义 dp 数组为: 前 i 个字符组成的字符串能否被拆分成若干个字典里的单词
        boolean[] dp = new boolean[n + 1];
        // 空字符可以找到
        dp[0] = true;
        // 转移方程为 检查 i 前的 dp[j] && j~i部分是在单词里
        for (int i = 1; i <= n; i++) {
            // 检查 0~i中的字符串
            for (int j = 0; j < i; j++) {
                if (dp[j] && set.contains(s.substring(j, i))) {
                    dp[i] = true;
                    break;
                }
            }
            System.out.print(dp[i] + " ");
        }
        System.out.println();
        return dp[n];
    }

    /**
     * 同上，
     * 内层不通过 set 查找 word
     * 通过遍历 wordDict
     */
    static public boolean wordBreak2(String s, List<String> wordDict) {
        int n = s.length();
        // 定义 dp 数组为: 前 i 个字符组成的字符串能否被拆分成若干个字典里的单词
        boolean[] dp = new boolean[n + 1];
        // 空字符可以找到
        dp[0] = true;
        // 转移方程为 检查 i 前的 dp[j] && j~i部分是在单词里
        for (int i = 1; i <= n; i++) {
            for (String word : wordDict) {
                // i 前面单词是否在字典里，
                // 如果在，且 dp[i-word.length] = true
                // 那么 dp[i] = true;
                if (i - word.length() >= 0 && s.substring(i - word.length(), i).equals(word)) {
                    if (dp[i - word.length()]) {
                        dp[i] = true;
                    }
                    // dp[i] = dp[i] || dp[i - word.length()];
                }
            }
            System.out.print(dp[i] + " ");
        }
        System.out.println();
        return dp[n];
    }

    public static void main(String[] args) {
        String[] ss = { "huawei", "applepenapple", "catsandog", "cars" };
        String[][] dicts = { { "hua", "wei" }, { "apple", "pen" }, { "cats", "dog", "sand", "and", "cat" },
                { "car", "ca", "rs" } };
        boolean[] answer = { true, true, false, true };

        for (int i = 0; i < ss.length; i++) {
            boolean ans = wordBreak2(ss[i], Arrays.asList(dicts[i]));
            assert ans == answer[i];
            System.out.println(ans);
        }

    }
}
