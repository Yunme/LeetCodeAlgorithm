import java.util.ArrayList;
import java.util.Arrays;
import java.util.Deque;
import java.util.LinkedList;
import java.util.Stack;

/**
 * 735: 小行星碰撞
 * 
 * 给定一个整数数组 asteroids，表示在同一行的小行星。
 * 对于数组中的每一个元素，其绝对值表示小行星的大小，正负表示小行星的移动方向（正表示向右移动，负表示向左移动）。
 * 每一颗小行星以相同的速度移动。
 * 找出碰撞后剩下的所有小行星。碰撞规则：两个小行星相互碰撞，较小的小行星会爆炸。
 * 如果两颗小行星大小相同，则两颗小行星都会爆炸。两颗移动方向相同的小行星，永远不会发生碰撞。
 * 
 * https://leetcode.cn/problems/remove-k-digits/description/
 */
public class C735 {

    /**
     * 栈模拟 O(n) O(n)
     */
    static public int[] asteroidCollision(int[] asteroids) {
        Deque<Integer> stack = new LinkedList<>();
        for (int i = 0; i < asteroids.length; i++) {
            int current = asteroids[i];
            // 当前行星 current 是否存在
            boolean alive = true;
            // current < 0 当前向左，前一个 > 0 向右，要碰撞
            while (alive && current < 0 && !stack.isEmpty() && stack.peekLast() > 0) {
                // 当前大于 栈顶的话 存在
                alive = stack.peekLast() < -current;
                if (stack.peekLast() <= -current) {
                    // 相等 或 栈顶较小，栈顶要爆炸 移除
                    stack.pollLast();
                }
            }
            // 还存活 入栈
            if (alive) {
                stack.offerLast(current);
            }
        }

        // 最后栈里保留的 就是剩余的
        // 从栈底取出
        System.out.println(stack);
        return new ArrayList<>(stack).stream().mapToInt(Integer::intValue).toArray();

    }

    public static void main(String[] args) {
        int[][] list = { { 5, 10, -5 }, { 8, -8 }, { 10, 2, -5 } };

        for (int i = 0; i < list.length; i++) {
            int[] ans = asteroidCollision(list[i]);
            System.out.println(Arrays.toString(ans));
        }
    }
}
