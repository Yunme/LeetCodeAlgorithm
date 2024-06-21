package backtrack;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Deque;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * 131: 分割回文串
 * 
 * 给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是 回文串。
 * 返回 s 所有可能的分割方案。
 *
 * https://leetcode.cn/problems/palindrome-partitioning/description/
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
public class C131 {

    /**
     * 检查字符数组 从 i 到 j 处是否是回文
     * [i, j]
     */
    static boolean check(char[] array, int i, int j) {
        while (i <= j) {
            if (array[i] != array[j]) {
                return false;
            }
            i++;
            j--;
        }
        return true;
    }

    /**
     * @param index    当前所在位置
     * @param array    字符数组
     * @param currList 当前分割结果集
     * @param ans      总的结果集
     */
    static void backtracking(int index, char[] array, List<String> currList, List<List<String>> ans) {
        System.out.println();
        System.out.println(index);
        if (index == array.length) {
            ans.add(new ArrayList<>(currList));
            return;
        }
        // 选择列表
        // 从 index 开始找一个回文串
        for (int i = index; i < array.length; i++) {
            // 检查当前子串是否是回文
            boolean re = check(array, index, i);
            if (!re) {
                continue;
            }
            String string = new String(array, index, i - index + 1);
            // 当前是回文串 加入结果
            currList.add(string);
            // 下一个
            backtracking(i + 1, array, currList, ans);
            // 回溯
            currList.remove(currList.size() - 1);
        }
    }

    /**
     * 回溯 O(n * 2^n)
     */
    static public List<List<String>> partition(String s) {
        List<List<String>> ans = new ArrayList<>();
        List<String> temp = new ArrayList<>();
        backtracking(0, s.toCharArray(), temp, ans);
        return ans;
    }

    /**
     * 优化版本 可以将字符数组判断回文的预存到 dp 数组中
     * O(2^n)
     */
    static public List<List<String>> partition2(String s) {
        List<List<String>> ans = new ArrayList<>();
        List<String> temp = new ArrayList<>();
        backtracking(0, s.toCharArray(), temp, ans);
        return ans;
    }

    public static void main(String[] args) {
        String[] array = { "aab", "a" };
        for (int i = 0; i < array.length; i++) {
            List<List<String>> ans = partition(array[i]);
            System.out.println(ans);
        }
    }
}
