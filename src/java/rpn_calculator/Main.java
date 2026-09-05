// #java | #kattis | #stack #linkedlist
// RPN Calculator
// https://open.kattis.com/problems/rpn

import java.io.*;
import java.math.BigInteger;
import java.util.*;

class Solution {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(System.out);

    class Node {
        BigInteger val;
        Node next;
        Node prev;
        Node(BigInteger val) { this.val = val; }
        BigInteger getVal() { return this.val; }
    }

    public void run() throws IOException {
        Node prev_last = new Node(new BigInteger(br.readLine()));
        Node last = new Node(new BigInteger(br.readLine()));
        prev_last.next = last;
        last.prev = prev_last;

        while (true) {
            String cmd = br.readLine().trim();
            if (cmd.equals("dup")) {
                Node cur = new Node(last.getVal());
                last.next = cur;
                cur.prev = last;
                prev_last = last;
                last = cur;
            } else if (cmd.equals("print")) {
                out.printf("%d\n", last.getVal());
            } else if (cmd.equals("pop")) {
                last = prev_last;
                if (prev_last.prev != null) {
                    prev_last = prev_last.prev;
                } else {
                    prev_last = null;
                }
            } else if (cmd.equals("swap")) {
                if (prev_last.prev != null) {
                    prev_last.prev.next = last;
                    last.prev = prev_last.prev;
                    last.next = prev_last;
                    prev_last.prev = last;
                    prev_last.next = null;
                    Node tmp = last;
                    last = prev_last;
                    prev_last = tmp;
                }
                last.next = prev_last;
                prev_last.prev = last;
                prev_last.next = null;

                Node tmp = last;
                last = prev_last;
                prev_last = tmp;
            } else if (cmd.equals("quit")) {
                break;
            } else if (cmd.equals("+")) {
                BigInteger left = prev_last.getVal();
                BigInteger right = last.getVal();
                BigInteger res = left.add(right);

                Node cur = new Node(res);
                if (prev_last.prev != null) {
                    prev_last.prev.next = cur;
                    cur.prev = prev_last.prev;

                    prev_last = prev_last.prev;
                    last = cur;
                } else {
                    prev_last = null;
                    last = cur;
                }
            } else if (cmd.equals("-")) {
                BigInteger left = prev_last.getVal();
                BigInteger right = last.getVal();
                BigInteger res = left.subtract(right);

                Node cur = new Node(res);
                if (prev_last.prev != null) {
                    prev_last.prev.next = cur;
                    cur.prev = prev_last.prev;

                    prev_last = prev_last.prev;
                    last = cur;
                } else {
                    prev_last = null;
                    last = cur;
                }
            } else if (cmd.equals("/")) {
                BigInteger left = prev_last.getVal();
                BigInteger right = last.getVal();
                BigInteger res = left.divide(right);

                Node cur = new Node(res);
                if (prev_last.prev != null) {
                    prev_last.prev.next = cur;
                    cur.prev = prev_last.prev;

                    prev_last = prev_last.prev;
                    last = cur;
                } else {
                    prev_last = null;
                    last = cur;
                }
            } else if (cmd.equals("*")) {
                BigInteger left = prev_last.getVal();
                BigInteger right = last.getVal();
                BigInteger res = left.multiply(right);

                Node cur = new Node(res);
                if (prev_last.prev != null) {
                    prev_last.prev.next = cur;
                    cur.prev = prev_last.prev;

                    prev_last = prev_last.prev;
                    last = cur;
                } else {
                    prev_last = null;
                    last = cur;
                }
            } else if (cmd.equals("^")) {
                BigInteger left = prev_last.getVal();
                BigInteger right = last.getVal();
                BigInteger res = left.pow(right.intValueExact());

                Node cur = new Node(res);
                if (prev_last.prev != null) {
                    prev_last.prev.next = cur;
                    cur.prev = prev_last.prev;

                    prev_last = prev_last.prev;
                    last = cur;
                } else {
                    prev_last = null;
                    last = cur;
                }
            } else {
                BigInteger x = new BigInteger(cmd);
                Node cur = new Node(x);
                last.next = cur;
                cur.prev = last;
                prev_last = last;
                last = cur;
            }
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
