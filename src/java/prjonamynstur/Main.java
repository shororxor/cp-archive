// #java | #kattis | #basic_programming
// Prjónamynstur
// https://open.kattis.com/problems/prjonamynstur

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Map;
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
    Map<Character, Integer> yarn = Map.ofEntries(Map.entry('.', 20), Map.entry('O', 10), Map.entry('\\', 25), Map.entry('/', 25), Map.entry('A', 35), Map.entry('^', 5), Map.entry('v', 22));

    public void run(FastScanner sc, PrintWriter out) {
        int n = sc.nextInt();
        int m = sc.nextInt();
        int res = 0;

        for (int i = 1; i <= n; i++) {
            char[] row = ('0' + sc.next()).toCharArray();
            for (int j = 1; j <= m; j++) {
                res += yarn.get(row[j]);
            }
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
