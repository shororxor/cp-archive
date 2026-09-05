// #java | #kattis | #basic_programming
// Raðgreining 1
// https://open.kattis.com/problems/radgreining1

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
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
        FastScanner sc = new FastScanner();
        PrintWriter out = new PrintWriter(System.out);

        int n = sc.nextInt();
        int m = sc.nextInt();

        char[] res = new char[n + 1];
        Arrays.fill(res, '?');

        for (int i = 1; i <= m; i++) {
            int start = sc.nextInt();
            char[] seq = sc.next().toCharArray();
            for (int j = 0; j < seq.length; j++) {
                if (res[start + j] != '?' && res[start + j] != seq[j]) {
                    out.printf("Villa");
                    out.close();
                    return;
                }
                res[start + j] = seq[j];
            }
        }

        out.printf("%s\n", new String(res, 1, res.length - 1));
        out.close();
        return;
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
