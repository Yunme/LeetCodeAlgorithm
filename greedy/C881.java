package greedy;

import java.util.Arrays;

/**
 * 881: 救生艇
 * 给定数组 people 。people[i]表示第 i 个人的体重 ，船的数量不限，每艘船可以承载的最大重量为 limit。、
 * 每艘船最多可同时载两人，但条件是这些人的重量之和最多为 limit。
 * 返回 承载所有人所需的最小船数 。
 * 
 * 1 <= people.length <= 5 * 104
 * 1 <= people[i] <= limit <= 3 * 104
 * 
 * https://leetcode.cn/problems/boats-to-save-people/description/
 */
public class C881 {

    /**
     * 贪心 双指针
     * 贪心的尽可能载更多。直到大于载重量
     */
    static public int numRescueBoats(int[] people, int limit) {
        // 升序排序
        Arrays.sort(people);
        int ans = 0;
        // i 指向体重轻的
        // j 指向体重重的
        int i = 0, j = people.length - 1;
        while (i <= j) {
            // 由于只能载两个人
            // 如果两人 体重和小于等于载重量 则这两人上船
            if (people[i] + people[j] <= limit) {
                i++;
                j--;
            } else {
                // 之和大于载重，则体重重的人上船
                j--;
            }
            ans++;
        }
        return ans;
    }

    public static void main(String[] args) {
        int[][] array1 = { { 1, 2 },
                { 3, 2, 2, 1 },
                { 3, 5, 3, 4 } };
        int[] array2 = { 3, 3, 5 };
        for (int i = 0; i < array1.length; i++) {
            Object ans = numRescueBoats(array1[i], array2[i]);
            System.out.println(ans);
        }
    }
}
