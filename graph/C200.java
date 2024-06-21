import java.util.LinkedList;
import java.util.Queue;

/**
 * 200: 岛屿数量
 *
 * 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
 * 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
 * 此外，你可以假设该网格的四条边均被水包围。
 * 
 * https://leetcode.cn/problems/string-compression/description/
 */
public class C200 {

    /**
     * BFS 广度优先遍历 使用 visited 矩阵存储访问过的结点
     */
    static public int numIslands(char[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        int[] y = { -1, 0, 1, 0 }; // i
        int[] x = { 0, -1, 0, 1 }; // j
        boolean[][] visited = new boolean[m][n];
        // 岛屿的个数 为 BFS的个数。
        int ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // 对每一个岛屿且没访问过的 进行 BFS
                if (grid[i][j] == '1' && !visited[i][j]) {
                    ans++;
                    // 一次 BFS 就访问完一个完整的岛屿
                    Queue<int[]> queue = new LinkedList<>();
                    queue.add(new int[] { i, j });
                    while (!queue.isEmpty()) {
                        int[] front = queue.poll();
                        int ii = front[0];
                        int jj = front[1];
                        if (!visited[ii][jj]) {
                            visited[ii][jj] = true;
                        }
                        for (int k = 0; k < x.length; k++) {
                            int newI = ii + y[k];
                            int newJ = jj + x[k];
                            if (newI >= 0 && newI < m && newJ >= 0 && newJ < n && grid[newI][newJ] == '1'
                                    && !visited[newI][newJ]) {
                                queue.offer(new int[] { newI, newJ });
                            }
                        }
                    }
                }
            }
        }
        return ans;
    }

    /**
     * BFS 广度优先遍历 使用 visited 矩阵存储访问过的结点
     * 空间优化 不使用visited 数组，使用原数组存储访问过的结点
     * 访问过的修改成 2
     */
    static public int numIslands2(char[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        int[] y = { -1, 0, 1, 0 }; // i
        int[] x = { 0, -1, 0, 1 }; // j
        // 岛屿的个数 为 BFS的个数。
        int ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // 对每一个岛屿且没访问过的 进行 BFS
                if (grid[i][j] == '1') {
                    ans++;
                    // 一次 BFS 就访问完一个完整的岛屿
                    Queue<int[]> queue = new LinkedList<>();
                    queue.add(new int[] { i, j });
                    grid[i][j] = '2';
                    while (!queue.isEmpty()) {
                        int[] front = queue.poll();
                        int ii = front[0];
                        int jj = front[1];
                        // grid[ii][jj] = '2';
                        for (int k = 0; k < x.length; k++) {
                            int newI = ii + y[k];
                            int newJ = jj + x[k];
                            if (newI >= 0 && newI < m && newJ >= 0 && newJ < n && grid[newI][newJ] == '1') {
                                queue.offer(new int[] { newI, newJ });
                                grid[ii][jj] = '2';
                            }
                        }
                    }
                }
            }
        }
        return ans;
    }

    /**
     * DFS 广度优先搜索
     */
    static public int numIslands3(char[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        int ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    ans++;
                    dfs(grid, i, j);
                }
            }
        }
        return ans;
    }

    static int[] y = { -1, 0, 1, 0 }; // i
    static int[] x = { 0, -1, 0, 1 }; // j

    static public void dfs(char[][] grid, int i, int j) {
        int m = grid.length;
        int n = grid[0].length;
        grid[i][j] = '2';
        for (int k = 0; k < x.length; k++) {
            int newI = i + y[k];
            int newJ = j + x[k];
            if (newI >= 0 && newI < m && newJ >= 0 && newJ < n && grid[newI][newJ] == '1') {
                dfs(grid, newI, newJ);
            }
        }
    }

    public static void main(String[] args) {
        char[][][] grids = { { { '1', '1', '1', '1', '0' },
                { '1', '1', '0', '1', '0' },
                { '1', '1', '0', '0', '0' },
                { '0', '0', '0', '0', '0' } },

                { { '1', '1', '0', '0', '0' },
                        { '1', '1', '0', '0', '0' },
                        { '0', '0', '1', '0', '0' },
                        { '0', '0', '0', '1', '1' } } };

        for (int i = 0; i < grids.length; i++) {
            int ans = numIslands3(grids[i]);
            System.out.println(ans);
        }
    }
}
