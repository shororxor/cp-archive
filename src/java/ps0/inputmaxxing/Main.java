// #java | #kattis | #basic_programming
// Inputmaxxing
// https://open.kattis.com/problems/inputmaxxing

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

class FastScanner {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer("");

    String next() {
        while (!st.hasMoreTokens())
            try {
                st = new StringTokenizer(br.readLine());
            } catch (IOException e) {
            }
        return st.nextToken();
    }

    String nextLine() {
        try {
            return br.readLine();
        } catch (IOException e) {
            return null;
        }
    }

    int nextInt() { return Integer.parseInt(next()); }

    long nextLong() { return Long.parseLong(next()); }

    char nextChar() { return next().charAt(0); }
}

class Solution {
    public void run(FastScanner sc, PrintWriter out) {
        long n = sc.nextLong();
        long res = n;
        for (long i = 1; i <= n; i++) {
            res = Math.max(res, sc.nextLong());
        }
        out.printf("%d", res);
    }
}

public class Main {
    static Solution sol = new Solution();

    public static void main(String[] args) throws IOException {
        FastScanner sc = new FastScanner();
        PrintWriter out = new PrintWriter(System.out);
        sol.run(sc, out);
        out.close();
        return;
    }
}
