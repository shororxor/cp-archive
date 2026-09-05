// #java | #kattis | #sliding_window #binary_search #basic_programming
// Voff
// https://open.kattis.com/problems/voff

import java.io.*;
import java.util.*;

class Solution {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(System.out);

    int n, k;
    int[] a;

    public void run() throws IOException {
        String[] token = br.readLine().split(" ");
        n = Integer.parseInt(token[0]);
        k = Integer.parseInt(token[1]);

        a = new int[n + 1];
        token = br.readLine().split(" ");

        for (int i = 1; i <= n; i++) {
            a[i] = Integer.parseInt(token[i - 1]);
        }

        int left = 1;
        int right = 1;
        int ans = 1;

        while (left <= n && right <= n) {
            while (a[left] + k > a[right]) {
                right++;
                if (right > n)
                    break;
            }
            ans = Math.max(right - left, ans);
            left++;
        }

        out.printf("%d\n", ans);
    }
}

public class Main {
    static Solution solution = new Solution();
    public static void main(String[] args) throws Exception {
        solution.run();
        solution.out.close();
    }
}
