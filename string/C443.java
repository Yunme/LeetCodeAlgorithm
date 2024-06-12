
/**
 * 443：压缩字符串
 *
 * 给你一个字符数组 chars ，请使用下述算法压缩：
 * 从一个空字符串 s 开始。对于 chars 中的每组 连续重复字符 ：
 * 如果这一组长度为 1 ，则将字符追加到 s 中。
 * 否则，需要向 s 追加字符，后跟这一组的长度。
 * 压缩后得到的字符串 s 不应该直接返回 ，需要转储到字符数组 chars 中。需要注意的是，如果组长度为 10 或 10 以上，则在 chars 数组中会被拆分为多个字符。
 * 请在 修改完输入数组后 ，返回该数组的新长度。
 * 
 * 你必须设计并实现一个只使用常量额外空间的算法来解决此问题。
 * 
 * https://leetcode.cn/problems/string-compression/description/
 */
public class C443 {

    /**
     * 法1：双指针法（自己实现） 时间：O(n) 空间O(1)
     * left 从左边开始逐一向前保存记录
     * right 一直向前寻找连续相等的序列长度
     * 寻找完成
     * left 处拼接当前寻找的字符
     * 判断寻找的个数 是否大于1，大于在 left 处开始记录
     * 等于1，不记录，left++；
     */
    static int compress(char[] chars) {
        int n = chars.length;
        int left = 0, right = 0;
        while (right < n) {
            // right 指针开始计数
            int start = right;
            char startC = chars[start];
            // 直到数组中元素跟前一个不相等
            while (right < n - 1 && chars[right] == chars[right + 1]) {
                right++;
            }
            chars[left++] = startC; // 拼接字符
            // 当前连续相等元素的个数
            int count = right - start + 1;
            if (count > 1) { // 个数大于1时。写入字符后面
                // 计算出一个数字各位的数
                // 个数最多是多少位，比如 1999 是1000；
                // 1999 log10 = 3；floor 向下取整，pow：10的3次方 = 1000
                int divisor = (int) Math.pow(10, Math.floor(Math.log10(count)));
                // divisor 从 1000、100、10、1
                while (divisor > 0) {
                    // 当前位的数
                    int digit = count / divisor;
                    // 拼接到 left 后
                    chars[left++] = (char) (digit + '0');
                    // 数变小 1999 -> 999
                    count %= divisor;
                    divisor /= 10; // 除数变小 1000 -> 100
                }
            }
            right++;
        }
        return left;
    }

    public static void main(String[] args) {
        int re = (int) Math.pow(10, Math.floor(Math.log10(1999)));
//        System.out.println(re);
        char[][] arr = {{'a', 'a', 'b', 'b', 'c', 'c', 'c'}, {'a'},
                {'a', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},
                {'a', 'a', 'a', 'b', 'b'},
                {'a', 'a', 'a', 'a', 'a', 'b'}};

        for (char[] a : arr) {
            int ans = compress(a);
            for (int i = 0; i < ans; i++) {
                System.out.print(a[i]);
            }
            System.out.println();
            System.out.println(ans);
        }
    }
}
