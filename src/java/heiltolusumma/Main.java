// #java | #kattis | #basic_programmig
// Heiltölusumma
// https://open.kattis.com/problems/heiltolusumma

import java.io.*;
import java.util.*;

class Solution {
    public void run() throws IOException {
        BufferedReader br =
            new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        long n = Long.parseLong(br.readLine());
        out.printf("%d\n",
                   (n > 0 ? n * (n + 1) / 2 : -(-n * (-n + 1) / 2 - 1)));
        out.close();
    }
}

public class Main {
    static Solution solution = new Solution();
    public static void main(String[] args) throws Exception { solution.run(); }
}
