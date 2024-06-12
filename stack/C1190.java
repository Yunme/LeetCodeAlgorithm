import java.util.ArrayList;
import java.util.Stack;

/**
 * 1190: 反转每队括号间的子串
 * 给出一个字符串 s（仅含有小写英文字母和括号）。
 * 请你按照从括号内到外的顺序，逐层反转每对匹配括号中的字符串，并返回最终的结果。
 * 
 * 注意，您的结果中 不应 包含任何括号。
 * 
 * https://leetcode.cn/problems/reverse-substrings-between-each-pair-of-parentheses/description/
 */
public class C1190 {

    /**
     * 法1：栈（自己实现）栈里保存字符
     * 从内到外，翻转后删除括号，放到外层
     * 利用栈翻转，翻转后再入栈，删除括号，直到所有右括号处理完
     * 复杂度 O(n^2)
     */
    static public String reverseParentheses(String s) {
        Stack<Character> stack = new Stack<>();
        int n = s.length();
        for (int i = 0; i < n; i++) {
            Character c = s.charAt(i);
            // 为空时，入栈
            if (!stack.isEmpty()) {
                // 找到第一个右括号
                if (c.equals(')')) {
                    // 开始出栈
                    ArrayList<Character> temp = new ArrayList<>();
                    // 字母出栈，添加到临时数组里
                    while (!stack.peek().equals('(')) {
                        temp.add(stack.peek());
                        stack.pop();
                    }
                    stack.pop();
                    // 再入栈参与外层括号反转
                    for (Character ch : temp) {
                        stack.push(ch);
                    }
                } else {
                    stack.push(c);
                }
            } else {
                stack.push(c);
            }
        }
        // 最后栈里的就是完整的
        String ans = "";
        while (!stack.empty()) {
            ans = stack.pop() + ans;
        }
        return ans;
    }

    /**
     * 法2：栈 简洁版本 栈里保存字符串
     * 复杂度 O(n^2)
     */
    static public String reverseParentheses2(String s) {
        Stack<String> stack = new Stack<>();
        // stringbuilder 存储最终字符
        StringBuilder stringBuilder = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '(') {
                // 前面一部分入栈
                stack.push(stringBuilder.toString());
                // 清空 sb
                stringBuilder.setLength(0);
            } else if (c == ')') {
                // 翻转
                stringBuilder.reverse();
                // 前面的插入到 sb 前面
                stringBuilder.insert(0, stack.pop());
            } else {
                // 字母，拼接
                stringBuilder.append(c);
            }
        }
        return stringBuilder.toString();
    }

    /**
     * 法3：预处理字符串。逆序的遍历括号
     * 找规律
     * 上面的复杂度都在要多次翻转字符串，
     * 但是其实只要按顺序输出字符串就行
     * <p>
     * 复杂度 O(n) 空间O(n)
     */
    static public String reverseParentheses3(String s) {
        int n = s.length();
        // 保存对应括号的坐标
        // 左括号处保存右括号的，右括号处保存左括号的
        // 比如: (u(love)i)
        // 9 0 7 0 0 0 0 2 0 0
        int[] pair = new int[n];
        Stack<Integer> stack = new Stack<>();
        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);
            if (c == '(') {
                stack.push(i);
            } else if (c == ')') {
                int leftIndex = stack.pop();
                pair[i] = leftIndex;
                pair[leftIndex] = i;
            }
        }
        StringBuilder sb = new StringBuilder();
        int index = 0;
        int direct = 1; // 1 表示向右，-1 表示向左
        while (index < n) {
            // 碰到括号，跳到其对应的位置，转换方向
            if (s.charAt(index) == '(' || s.charAt(index) == ')') {
                index = pair[index];
                direct = -direct;
            } else {
                sb.append(s.charAt(index));
            }
            // 到下一位，前进或后退
            index += direct;
        }
        return sb.toString();
    }


    public static void main(String[] args) {
        String[] coins = {"(abcd)", "(u(love)i)", "(ed(et(oc))el)", "a(bcdefghijkl(mno)p)q"};

        for (int i = 0; i < coins.length; i++) {
            String ans = reverseParentheses3(coins[i]);
            System.out.println(ans);
        }
    }
}
