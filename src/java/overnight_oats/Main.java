// #java | #kattis | #deque
// Overnight Oats
// https://open.kattis.com/problems/overnightoats

import java.io.*;
import java.util.*;

class Solution {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(System.out);

    public void run() throws IOException {
        int n = Integer.parseInt(br.readLine());
        int x = Integer.parseInt(br.readLine());

        Deque<Integer> dq = new ArrayDeque<>();
        boolean failed = false;

        for (int i = 1; i <= n; i++) {
            String op = br.readLine();
            if (op.equals("PASS")) {
                continue;
            }
            if (op.equals("ADD")) {
                dq.addLast(i + x);
            }
            if (op.equals("EAT")) {
                if (dq.isEmpty()) {
                    failed = true;
                    break;
                }
                int cup = dq.removeFirst();
                if (cup < i) {
                    failed = true;
                    break;
                }
            }
        }

        out.printf("%s\n", failed ? "ono.." : "yay!");
    }
}

public class Main {
    static Solution solution = new Solution();
    public static void main(String[] args) throws Exception {
        solution.run();
        solution.out.close();
    }
}
