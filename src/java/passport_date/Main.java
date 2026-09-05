// #java | #kattis | #basic_programming
// Passport Dates
// https://open.kattis.com/problems/vegabrefadagsetningar

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

    Map<String, String> months = Map.ofEntries(
        Map.entry("JAN", "01"), Map.entry("FEB", "02"), Map.entry("MAR", "03"),
        Map.entry("APR", "04"), Map.entry("MAY", "05"), Map.entry("JUN", "06"),
        Map.entry("JUL", "07"), Map.entry("AUG", "08"), Map.entry("SEP", "09"),
        Map.entry("OCT", "10"), Map.entry("NOV", "11"), Map.entry("DEC", "12"));

    public void run(FastScanner sc, PrintWriter out) {
        FastScanner sc = new FastScanner();
        PrintWriter out = new PrintWriter(System.out);

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
