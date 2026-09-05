// #java | #kattis | #basic_programming
// Playing piano
// https://open.kattis.com/problems/spelapiano

import java.io.*;
import java.util.*;

class Solution {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(System.out);

    int n, m;

    public void run() throws IOException {
        n = Integer.parseInt(br.readLine());
        m = Integer.parseInt(br.readLine());
        br.readLine();

        long max_diff = Long.MIN_VALUE;
        long min_diff = Long.MAX_VALUE;
        long sum = 0;
        int[] diff = new int[m];
        boolean all_pos = true;
        boolean all_neg = true;

        for (int i = 1; i <= m - 1; i++) {
            diff[i] = Integer.parseInt(br.readLine());
            sum += diff[i];
            max_diff = Math.max(max_diff, sum);
            min_diff = Math.min(min_diff, sum);
            all_pos &= (diff[i] >= 0);
            all_neg &= (diff[i] <= 0);
        }

        if (max_diff >= n || min_diff <= -n || max_diff - min_diff >= n) {
            out.printf("%s\n", "finns ingen");
            return;
        }

        if (all_pos) {
            out.printf("%d\n", 1);
            return;
        }

        if (all_neg) {
            out.printf("%d\n", n);
            return;
        }

        if (max_diff >= 0 && min_diff >= 0) {
            out.printf("%d\n", 1);
            return;
        }

        if (min_diff <= 0 && max_diff <= 0) {
            out.printf("%d\n", n);
            return;
        }

        out.printf("%d\n", 1 - min_diff);
        return;
    }
}

public class Main {
    static Solution solution = new Solution();

    public static void main(String[] args) throws Exception {
        solution.run();
        solution.out.close();
    }
}
