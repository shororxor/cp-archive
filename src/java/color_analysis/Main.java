// #java | #kattis | #basic_programming
// Colour Analysis
// https://open.kattis.com/problems/litagreining

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
        int R = sc.nextInt();
        int G = sc.nextInt();
        int B = sc.nextInt();

        if (R > G && R > B) out.printf("%s", "raudur");
        else if (G > R && G > B) out.printf("%s", "graenn");
        else if (B > R && B > G) out.printf("%s", "blar");
        else if (R == G && B < R && B < G) out.printf("%s", "gulur");
        else if (R == B && G < R && G < B) out.printf("%s", "fjolubleikur");
        else if (B == G && R < B && R < G) out.printf("%s", "blagraenn");
        else if (R == 0 && B == 0 && G == 0) out.printf("%s", "svartur");
        else if (R == 255 && B == 255 && G == 255) out.printf("%s", "hvitur");
        else if (R == B && B == G && R != 0 && R != 255) out.printf("%s", "grar");
        else out.printf("%s", "othekkt");
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
