// #java | #kattis | #basic_programming
// "lv"-able
// https://open.kattis.com/problems/lvable

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
        char[] s = ('0' + sc.next()).toCharArray();
        boolean l_appear = false;
        boolean v_appear = false;
        char prev = '?';

        for (int i = 1; i <= n; i++) {
            char cur = s[i];
            if (prev == 'l' && cur == 'v') {
                out.printf("%d", 0);
                return;
            }
            if (cur == 'l') l_appear = true;
            if (cur == 'v') v_appear = true;

            prev = cur;
        }
        out.printf("%d", ((l_appear || v_appear) ? 1 : 2));
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
