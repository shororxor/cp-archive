// #java | #kattis | #sorting #implementation
// Gini Stuðull
// https://open.kattis.com/problems/ginistudull

import java.io.*;
import java.util.*;

class Solution {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(System.out);

    public void run() throws IOException {
        int n = Integer.parseInt(br.readLine());
        int[] a = new int[n + 1];
        int[] d = new int[n + 1];
        double[] col = new double[n + 1];
        double[] prefix = new double[n + 1];

        double denumerator = 0;
        for (int i = 1; i <= n; i++) {
            a[i] = Integer.parseInt(br.readLine());
            denumerator += a[i];
        }

        Arrays.sort(a, 1, n + 1);
        prefix[1] = 0;
        for (int i = 2; i <= n; i++) {
            d[i] = a[i] - a[i - 1];
            col[i] = (n - i + 1) * d[i];
            prefix[i] = prefix[i - 1] + col[i];
        }

        double numerator = 0;
        for (int i = 2; i <= n; i++) {
            numerator += (prefix[n] - prefix[i - 1]) * 2;
        }

        out.printf("%.17f\n", numerator / (2 * denumerator * n));
    }
}

public class Main {
    static Solution solution = new Solution();

    public static void main(String[] args) throws Exception {
        solution.run();
        solution.out.close();
    }
}
