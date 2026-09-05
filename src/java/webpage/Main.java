// #java | #kattis | #basic_programming
// Web Page
// https://open.kattis.com/problems/heimasida

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
    Map<String, String> special = Map.ofEntries(
        Map.entry("Á", "a"), Map.entry("á", "a"), Map.entry("Ð", "d"),
        Map.entry("ð", "d"), Map.entry("É", "e"), Map.entry("é", "e"),
        Map.entry("Í", "i"), Map.entry("í", "i"), Map.entry("Ó", "o"),
        Map.entry("ó", "o"), Map.entry("Ú", "u"), Map.entry("ú", "u"),
        Map.entry("Ý", "y"), Map.entry("ý", "y"), Map.entry("Þ", "th"),
        Map.entry("þ", "th"), Map.entry("Æ", "ae"), Map.entry("æ", "ae"),
        Map.entry("Ö", "o"), Map.entry("ö", "o"));

    public boolean checkAsciiUpper(char c) { return (65 <= c && c <= 90); }

    public boolean checkValid(char c) {
        return (48 <= c && c <= 57) || (65 <= c && c <= 90) ||
            (97 <= c && c <= 122);
    }

    public void run(FastScanner sc, PrintWriter out) {
        String s = sc.nextLine();
        String res = "";

        for (int i = 0; i < s.length(); i++) {
            if (special.containsKey(Character.toString(c))) {
                res += special.get(Character.toString(c));
                continue;
            }
            if (!checkValid(c)) {
                continue;
            }
            if (checkAsciiUpper(c)) {
                res += Character.toString(c + 32);
                continue;
            }
            res += Character.toString(c);
        }

        out.printf("%s.is\n", res);
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
        sol.run();
        return;
    }
}
