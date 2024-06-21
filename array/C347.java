import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Map.Entry;

/**
 * 347: 前 k 个高频元素
 * 给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。
 * 
 * 进阶：你所设计算法的时间复杂度 必须 优于 O(n log n) ，其中 n 是数组大小。
 * https://leetcode.cn/problems/top-k-frequent-elements/description/
 */
public class C347 {

    /**
     * 计数 并使用 堆 找出最大值
     */
    static public int[] topKFrequent(int[] nums, int k) {
        // 计数
        HashMap<Integer, Integer> countHashMap = new HashMap<>();
        for (int i : nums) {
            countHashMap.put(i, countHashMap.getOrDefault(i, 0) + 1);
        }

        // 找最次数最多的
        // 使用优先队列 次数多的优先，次数相同时
        PriorityQueue<Integer[]> queue = new PriorityQueue<>(new Comparator<Integer[]>() {
            @Override
            public int compare(Integer[] i1, Integer[] i2) {
                if (i1[1] == i2[1]) {
                    return i2[0].compareTo(i1[0]);
                }
                return i2[1].compareTo(i1[1]);
            }
        });
        for (Entry<Integer, Integer> entry : countHashMap.entrySet()) {
            queue.offer(new Integer[] { entry.getKey(), entry.getValue() });
        }
        List<Integer> ans = new ArrayList<>();
        for (int i = 0; i < k; i++) {
            ans.add(queue.poll()[0]);
        }
        return ans.stream().mapToInt(Integer::intValue).toArray();
    }

    public static void main(String[] args) {
        int[][] array1 = { { 1, 1, 1, 2, 2, 3 },
                { 1 } };
        int[] array2 = { 2, 1 };
        for (int i = 0; i < array1.length; i++) {
            int[] ans = topKFrequent(array1[i], array2[i]);
            System.out.println(Arrays.toString(ans));
        }
    }
}
