import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Solution {
    public int cntSum = 0;
    public List<List<String>> solveNQueens(int n) {
        List<List<String>> ans = new ArrayList<List<String>>();
        int[] queens = new int[n];
        //Arrays.fill(queens, -1);
        dfs(ans, queens, n, 0, 0, 0, 0);
        return ans;
    }
    public void dfs(List<List<String>> ans, int[] queens, int n, int row, int cols, int dias1, int dias2) {
        if (row == n) {
            ans.add(generateBoard(queens, n));
            cntSum++;
        } else {
            int validBits = ((1 << n) - 1) & (~(cols | dias1 | dias2));
            while (validBits != 0) {
                int leastValidBit = validBits & (-validBits);
                int col = Integer.bitCount(leastValidBit - 1);
                queens[row] = col;
                dfs(ans, queens, n, row + 1, cols | leastValidBit, (dias1 | leastValidBit) << 1, (dias2 | leastValidBit) >> 1);
                //queens[row] = -1;
                validBits = validBits & (validBits - 1);
            }
        }
    }
    public List<String> generateBoard(int[] queens, int n) {
        List<String> res = new ArrayList<String>();
        for (int i = 0; i < n; i++) {
            char[] temp = new char[n];
            Arrays.fill(temp, '.');
            temp[queens[i]] = 'Q';
            res.add(new String(temp));
        }
        return res;
    }
}
