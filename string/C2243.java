

/**
 * 2243：计算字符串的数字和
 *
 * 给你一个由若干数字（0 - 9）组成的字符串 s ，和一个整数。
 * 如果 s 的长度大于 k ，则可以执行一轮操作。在一轮操作中，需要完成以下工作：
 * 将 s 拆分 成长度为 k 的若干 连续数字组 ，使得前 k 个字符都分在第一组，接下来的 k 个字符都分在第二组，依此类推。注意，最后一个数字组的长度可以小于 k 。
 * 用表示每个数字组中所有数字之和的字符串来 替换 对应的数字组。例如，"346" 会替换为 "13" ，因为 3 + 4 + 6 = 13 。
 * 合并 所有组以形成一个新字符串。如果新字符串的长度大于 k 则重复第一步。
 * 
 * 返回在完成所有轮操作后的 s 。
 * 
 * https://leetcode.cn/problems/calculate-digit-sum-of-a-string/description/
 */
public class C2243 {

    /**
     * 法1：模拟
     * 每 k 个字符相加。
     */
    static public String digitSum(String s, int k) {
        StringBuilder sb = new StringBuilder(s);
        while (sb.length() > k) {
            // 每轮相加后的结果
            StringBuilder temp = new StringBuilder();
            int sum = 0, count = 0;
            for (int i = 0; i < sb.length(); i++) {
                sum += sb.charAt(i) - '0';
                count++;
                if (count == k) {
                    temp.append(sum);
                    count = 0;
                    sum = 0;
                }
            }
            // 最后不足 k 个的
            if (count > 0) temp.append(sum);
            // 更新
            sb = temp;
        }
        return sb.toString();
    }


    public static void main(String[] args) {
        String[] coins = {"11111222223", "00000000"};
        int[] array2 = {3, 3};
        for (int i = 0; i < coins.length; i++) {
            String ans = digitSum(coins[i], array2[i]);
            System.out.println(ans);
        }
    }
}
