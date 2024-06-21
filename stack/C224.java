import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedList;
import java.util.Stack;

/**
 * 224: 基本计算器
 * 
 * 给你一个字符串表达式 s ，请你实现一个基本计算器来计算并返回它的值。
 * 注意:不允许使用任何将字符串作为数学表达式计算的内置函数，比如 eval() 。
 * 
 * https://leetcode.cn/problems/basic-calculator/description/
 * 
 * 1 <= s.length <= 3 * 105
 * s 由数字、'+'、'-'、'('、')'、和 ' ' 组成
 * s 表示一个有效的表达式
 * '+' 不能用作一元运算(例如， "+1" 和 "+(2 + 3)" 无效)
 * '-' 可以用作一元运算(即 "-1" 和 "-(2 + 3)" 是有效的)
 * 输入中不存在两个连续的操作符
 * 每个数字和运行的计算将适合于一个有符号的 32位 整数
 */
public class C224 {

    static public int calculate(String s) {
        // 负号带入到括号里
        Deque<Integer> stack = new LinkedList<>(); // 存储正负号
        int ans = 0;
        int num = 0;
        int operation = 1; // 默认正号
        stack.offerFirst(operation);

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == ' ') {
                // 空格跳过
                continue;
            }
            if (c >= '0' && c <= '9') {
                // 数字累加
                num = 10 * num + (c - '0');
            } else {
                ans += operation * num;
                num = 0;
                // 符号 或 括号
                if (c == '+') {
                    // 当前为正号 符号还是栈顶的
                    operation = stack.peekFirst();
                } else if (c == '-') {
                    // 当前为负号 符号取反
                    operation = -stack.peekFirst();
                } else if (c == '(') {
                    // 是左括号，括号前的符号入栈
                    stack.offerFirst(operation);
                } else {
                    // 是右括号，出栈符号
                    stack.pollFirst();
                }
            }
        }
        return ans + operation * num;
    }

    public static void main(String[] args) {
        String[] list = { "1 + 1", "2-1 + 2", "(1+(4+5+2)-3)+(6+8)" };

        for (int i = 0; i < list.length; i++) {
            int ans = calculate(list[i]);
            System.out.println(ans);
        }
    }
}
