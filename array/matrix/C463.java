package matrix;

/**
 * 463: 岛屿的周长
 * 定一个 row x col 的二维网格地图 grid ，其中：grid[i][j] = 1 表示陆地， grid[i][j] = 0 表示水域。
 * 网格中的格子 水平和垂直 方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，一个或多个表示陆地的格子相连组成的岛屿）。
 * 岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。格子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100
 * 。计算这个岛屿的周长。
 * 
 * https://leetcode.cn/problems/island-perimeter/description/
 */
public class C463 {

    /**
     * 迭代判断
     */
    public static int islandPerimeter(int[][] grid) {
        int[][] vector = { { -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 } };
        int ans = 0;
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                if (grid[i][j] == 1) {
                    int temp = 0;
                    for (int[] v : vector) {
                        int newI = i + v[0];
                        int newJ = j + v[1];
                        if (newI < grid.length && newI >= 0
                                && newJ >= 0 && newJ < grid[i].length) {
                            // 四个方向没有岛屿则周长 +1
                            if (grid[i + v[0]][j + v[1]] == 0) {
                                temp++;
                            }
                        } else {
                            // 矩阵边界，也是周长
                            temp++;
                        }
                    }
                    System.out.println(i + "," + j + ":" + temp);
                    ans += temp;
                }
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        // int[][] array1 = {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}};
        // int[][] array1 = {{1}};
        int[][] array1 = { { 1, 0 } };
        int[] array2 = { 2, 3, 4, 3, 0 };
        for (int i = 0; i < array1.length; i++) {
            Object ans = islandPerimeter(array1);
            System.out.println(ans);
        }
    }
}
