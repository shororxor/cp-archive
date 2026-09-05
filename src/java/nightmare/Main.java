// #java | #kattis | #basic_programming
// Uh-Oh, It Is Nighttime!
// https://open.kattis.com/problems/oothaderkominnott

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
        int i = sc.nextInt();
        int l, w, h;

        if (i == 1) {
            l = sc.nextInt();
            w = l;
            h = 3;
        }
        else if (i == 2) {
            l = sc.nextInt();
            w = sc.nextInt();
            h = 3;
        }
        else {
            l = sc.nextInt();
            w = sc.nextInt();
            h = sc.nextInt();
        }

        int res = ((l - 2) * h + (w - 2) * h) * 2 + (l - 2) * (w - 2) + 4 * h;
        out.printf("%d\n", res);
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
