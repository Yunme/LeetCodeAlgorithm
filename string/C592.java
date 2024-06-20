
/**
 * 592: 分数加减运算
 *
 * 给定一个表示分数加减运算的字符串 expression ，你需要返回一个字符串形式的计算结果。
 * 这个结果应该是不可约分的分数，即最简分数。 如果最终结果是一个整数，例如 2，你需要将它转换成分数形式，其分母为 1。所以在上述例子中, 2 应该被转换为
 * 2/1。
 * 
 * 输入和输出字符串只包含 '0' 到 '9' 的数字，以及 '/', '+' 和 '-'。
 * 输入和输出分数格式均为 ±分子/分母。如果输入的第一个分数或者输出的分数是正数，则 '+' 会被省略掉。
 * https://leetcode.cn/problems/fraction-addition-and-subtraction/description/
 */
public class C592 {

    /**
     * 解析 分数相加 x1/y1 + x2/y2 = (x1y2 + x2y1)/y1y2
     */
    static public String fractionAddition(String expression) {
        int n = expression.length();
        int i = 0;
        // 默认分数
        int top = 0;
        int bottom = 1;
        while (i < n) {
            // 符号
            char c = expression.charAt(i);
            int sign = 1;
            if (c == '-' || c == '+') {
                sign = c == '-' ? -1 : 1;
                i++;
            }
            // 分子
            int tempTop = 0;
            while (i < n && Character.isDigit(expression.charAt(i))) {
                tempTop = 10 * tempTop + Character.getNumericValue(expression.charAt(i));
                i++;
            }
            // 正数还是负数
            tempTop = sign * tempTop;
            // /斜杠
            i++;
            // 分母
            int tempBottom = 0;
            while (i < n && Character.isDigit(expression.charAt(i))) {
                tempBottom = 10 * tempBottom + Character.getNumericValue(expression.charAt(i));
                i++;
            }
            // 两个分数相加
            top = top * tempBottom + tempTop * bottom;
            bottom = bottom * tempBottom;
        }
        if (top == 0) {
            return "0/1";
        }
        System.out.println(top + "/" + bottom);
        // 约分。分子分母的最大公约数
        int gcd = gcd(Math.abs(top), bottom);
        top = top / gcd;
        bottom = bottom / gcd;
        return Integer.toString(top) + "/" + bottom;
    }

    /**
     * 求 a 和 b 的最大公约数
     * 等于 较小的那个数 和 较小的数与较大数的余数的最大公约数
     * 
     * 两个数的最小公倍数 LCM(a,b)= abs(a * b) / gcd(a,b) 乘积的绝对值 / 最大公约数
     */
    static public int gcd(int a, int b) {
        int remainder = a % b;
        while (remainder != 0) {
            a = b;
            b = remainder;
            remainder = a % b;
        }
        return b;
    }

    public static void main(String[] args) {
        String[] list = { "-1/2+1/2", "-1/2+1/2+1/3", "1/3-1/2" };

        for (String str : list) {
            Object ans = fractionAddition(str);
            System.out.println(ans);
        }
    }
}
