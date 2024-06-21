package backtrack;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * LCR 157：套餐内商品的排列顺序
 * 
 * 某店铺将用于组成套餐的商品记作字符串 goods，其中 goods[i] 表示对应商品。请返回该套餐内所含商品的 全部排列方式 。
 * 返回结果 无顺序要求，但不能含有重复的元素。
 *
 * https://leetcode.cn/problems/zi-fu-chuan-de-pai-lie-lcof/description/
 */

/**
 * 
 * result = []
 * 
 * def backtrack(路径, 选择列表):
 * if 满足结束条件:
 * \t result.add(路径)
 * return
 * for 选择 in 选择列表:
 * # 做选择
 * 将该选择从选择列表移除
 * 路径.add(选择)
 * backtrack(路径, 选择列表)
 * # 撤销选择
 * 路径.remove(选择)
 * 将该选择再加入选择列表
 */
public class LCR157 {

    /**
     * 回溯
     */
    static String[] goodsOrder(String goods) {
        int n = goods.length();
        char[] array = goods.toCharArray();
        // 先排序 保证重复字符在一起
        Arrays.sort(array);
        // used 数组标记每个元素是否使用
        boolean[] used = new boolean[n];
        // 结果集
        List<String> result = new ArrayList<>();
        int i = 0;
        backtracking(array, i, used, new StringBuilder(), result);
        String[] ans = new String[result.size()];
        result.toArray(ans);
        return ans;
    }

    static void backtracking(char[] array, int index, boolean[] used, StringBuilder sb, Collection<String> ans) {
        // 收集结果，当字符串长度与总长度相同
        if (sb.length() == array.length) {
            ans.add(sb.toString());
            return;
        }
        // 做选择
        for (int i = 0; i < array.length; i++) {
            // 去重 前一个相同且未使用过时 继续下个循环
            // 前一个未使用过 当前不能选，比如 a1, a2, b。
            // a1 只能出现在 a2 左侧，才能保证不重复。
            if (i > 0 && array[i] == array[i - 1] && !used[i - 1]) {
                continue;
            }
            // 当前没被使用
            if (!used[i]) {
                // 选择
                used[i] = true;
                // 路径 add
                sb.append(array[i]);
                // 回溯下一个
                backtracking(array, index + 1, used, sb, ans);
                // 撤销选择
                sb.deleteCharAt(sb.length() - 1);
                used[i] = false;
            }
        }
    }

    public static void main(String[] args) {
        String[] array = { "agew", "baba" };
        for (int i = 0; i < array.length; i++) {
            String[] ans = goodsOrder(array[i]);
            System.out.println(Arrays.toString(ans));
        }
    }
}
