// #java | #kattis | #basic_programming
// Sort of Sort
// https://open.kattis.com/problems/sortofsort

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

class FastScanner {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer("");

    String next() {
        while (!st.hasMoreTokens()) try {
                st = new StringTokenizer(br.readLine());
            }
            catch (IOException e) {
            }
        return st.nextToken();
    }

    String nextLine() {
        try {
            return br.readLine();
        }
        catch (IOException e) {
            return null;
        }
    }

    int nextInt() {
        return Integer.parseInt(next());
    }

    long nextLong() {
        return Long.parseLong(next());
    }

    char nextChar() {
        return next().charAt(0);
    }
}

class Solution {
    public void run(FastScanner sc, PrintWriter out) {
        int n = sc.nextInt();
        int prev = Integer.MIN_VALUE;
        for (int i = 1; i <= n; i++) {
            int cur = sc.nextInt();
            if (cur >= prev) {
                out.printf("%d ", cur);
                prev = cur;
            }
        }
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
