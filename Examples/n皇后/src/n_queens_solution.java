import java.util.List;
import java.util.Scanner;

/**
 * This is a Project to Solve the N_QUEENS Problem
 * Input an Integer n As the Number of Queens
 * Created by Wjj
 */

public class n_queens_solution {
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        int n = reader.nextInt();
        reader.close();
        Solution createAns = new Solution();
        List<List<String>> ans = createAns.solveNQueens(n);
        for (List<String> x : ans) {
            for (String y : x) {
                System.out.println(y);
            }
            System.out.println();
        }
        System.out.print("The Number of Answers is : " + createAns.cntSum);
    }
}
