import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedList;
import java.util.Stack;

/**
 * 402: 移掉 K 位数字
 * 
 * 给你一个以字符串表示的非负整数 num 和一个整数 k ，移除这个数中的 k 位数字，使得剩下的数字最小。
 * 请你以字符串形式返回这个最小的数字。
 * 
 * https://leetcode.cn/problems/remove-k-digits/description/
 */
public class C402 {

    /**
     * 贪心 + 单调栈
     * 两个数比较时，却决于左边位的大小
     * 12a34 12b34 取决于 a 和 b 的大小关系
     * 1432 => 1左边没比他大的，4也是，3前面是4，移除 4 会让整个变小。
     * 
     * 实现：
     * 从左到右依次入栈，如果当前比栈顶小，则栈顶的出栈。直到出栈 k 个
     */
    static public String removeKdigits(String num, int k) {
        // 从高位移除，尽可能移除较大的
        int n = num.length();
        //
        Deque<Character> stack = new LinkedList<>();
        for (int i = 0; i < n; i++) {
            char c = num.charAt(i);
            // 遇到比栈顶大的 栈顶出栈
            // 直到出栈 k 次
            while (!stack.isEmpty() && k > 0 && stack.peekFirst() > c) {
                stack.pollFirst();
                k--;
            }
            stack.offerFirst(c);
        }
        // 最终 k 个出栈没够的话，剩余个数个出栈
        if (k > 0) {
            for (int i = 0; i < k; i++) {
                stack.pollFirst();
            }
        }
        System.out.println(stack.toString());

        // 栈中剩余元素就是结果
        // 栈从栈底到栈顶结果
        StringBuilder stringBuilder = new StringBuilder();
        boolean zero = true; // 前导 0
        while (!stack.isEmpty()) {
            // 双端队列尾部出
            char c = stack.pollLast();
            if (zero && c == '0') {
                continue;
            }
            zero = false;
            stringBuilder.append(c);
        }
        if (stringBuilder.length() == 0) {
            stringBuilder.append('0');
        }
        return stringBuilder.toString();
    }

    public static void main(String[] args) {
        String[] coins = { "1432219", "10200", "10" };
        int[] digits = { 3, 1, 2 };

        for (int i = 0; i < coins.length; i++) {
            String ans = removeKdigits(coins[i], digits[i]);
            System.out.println(ans);
        }
    }
}
