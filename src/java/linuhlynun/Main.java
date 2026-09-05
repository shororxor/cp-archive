// #java | #sorting #greedy #implementation
// Línuhlýnun
// https://open.kattis.com/problems/linuhlynun

import java.io.*;
import java.util.*;

class Solution {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(System.out);

    class Pair {
        int first, second;
        Pair(int first, int second) {
            this.first = first;
            this.second = second;
        }
    }

    public void run() throws IOException {
        int n = Integer.parseInt(br.readLine());
        Pair[] a = new Pair[n + 1];
        int[] sum = new int[n + 1];
        sum[0] = 0;

        for (int i = 1; i <= n; i++) {
            String[] token = br.readLine().split(" ");
            a[i] = new Pair(Integer.parseInt(token[0]), Integer.parseInt(token[1]));
        }

        Arrays.sort(a, 1, n + 1, (x, y) -> {
            if (x.first == y.first) {
                return Integer.compare(x.second, y.second);
            }
            return Integer.compare(x.first, y.first);
        });

        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + a[i].second;
        }

        int i = 1;
        while (true) {
            if (i == n) break;
            if (sum[i - 1] - sum[0] == sum[n] - sum[i]) {
                break;
            }

            if (sum[i] - sum[0] < sum[n] - sum[i]) {
                i++;
            }
            else break;
        }

        out.printf("%d\n", a[i].first);
    }
}

public class Main {
    static Solution solution = new Solution();
    public static void main(String[] args) throws Exception {
        solution.run();
        solution.out.close();
    }
}
