// #java | #kattis | #sorting #priority_queue #min_heap #interactive
// Bank Closing
// https://open.kattis.com/problems/bankclosing

import java.io.*;
import java.math.BigInteger;
import java.util.*;

class Solution {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(System.out);

    class Node {
        int value;
        int index;
        Node(int value, int index) {
            this.value = value;
            this.index = index;
        }
    }

    public void run() throws IOException {
        String[] token = br.readLine().split(" ");
        int n = Integer.parseInt(token[0]);
        int k = Integer.parseInt(token[1]);

        token = br.readLine().split(" ");
        PriorityQueue<Node> minHeap = new PriorityQueue<>((a, b) -> Integer.compare(a.value, b.value));

        for (int i = 0; i < k; i++) {
            minHeap.add(new Node(Integer.parseInt(token[i]), i + 1));
        }

        Node u = minHeap.poll();
        int curIndex = u.index;
        System.out.println(curIndex);
        System.out.flush();

        while (true) {
            String input = br.readLine();
            if (input.equals("DONE")) {
                if (minHeap.isEmpty()) {
                    out.println("DONE");
                    break;
                }
            }
            else {
                int val = Integer.parseInt(input);
                minHeap.add(new Node(val, curIndex));
            }

            u = minHeap.poll();
            curIndex = u.index;
            System.out.println(curIndex);
            System.out.flush();
        }
    }
}

public class Main {
    static Solution solution = new Solution();
    public static void main(String[] args) throws Exception {
        solution.run();
        solution.out.close();
    }
}
