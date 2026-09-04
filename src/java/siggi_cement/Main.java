// #java | #kattis | #sorting #two_pointers
// Siggi sement
// https://open.kattis.com/problems/sement

import java.io.*;
import java.util.*;

class Solution {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(System.out);

    public void run() throws IOException {
        String[] token = br.readLine().split(" ");
        int n = Integer.parseInt(token[0]);
        long k = Long.parseLong(token[1]);
        long[] a = new long[n + 1];

        for (int i = 1; i <= n; i++) {
            a[i] = Long.parseLong(br.readLine());
        }

        Arrays.sort(a, 1, n + 1);
        int i = 1;
        int j = n;
        long ans = -1;

        while (i < j) {
            if (a[i] + a[j] == k) {
                ans = a[i];
                i++;
            } else if (a[i] + a[j] > k) {
                j--;
            } else {
                i++;
            }
        }

        if (ans == -1)
            out.printf("%s\n", "Neibb");
        else
            out.printf("%d %d\n", ans, k - ans);
    }
}

public class Main {
    static Solution solution = new Solution();
    public static void main(String[] args) throws Exception {
        solution.run();
        solution.out.close();
    }
}
