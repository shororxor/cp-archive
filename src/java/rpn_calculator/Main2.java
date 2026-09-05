// #java | #kattis | #stack #linkedlist
// RPN Calculator
// https://open.kattis.com/problems/rpn

import java.io.*;
import java.math.BigInteger;
import java.util.*;

class Solution {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(System.out);

    public void run() throws IOException {
        Deque<BigInteger> st = new ArrayDeque<>();
        boolean running = true;

        while (running) {
            String cmd = br.readLine().trim();

            switch (cmd) {
            case "dup":
                st.push(st.peek());
                break;

            case "pop":
                st.pop();
                break;

            case "swap": {
                BigInteger a = st.pop();
                BigInteger b = st.pop();

                st.push(a);
                st.push(b);
                break;
            }

            case "print": {
                out.println(st.peek());
                break;
            }

            case "quit": {
                running = false;
                break;
            }

            case "+": {
                BigInteger right = st.pop();
                BigInteger left = st.pop();
                st.push(left.add(right));
                break;
            }

            case "-": {
                BigInteger right = st.pop();
                BigInteger left = st.pop();
                st.push(left.subtract(right));
                break;
            }

            case "*": {
                BigInteger right = st.pop();
                BigInteger left = st.pop();
                st.push(left.multiply(right));
                break;
            }

            case "/": {
                BigInteger right = st.pop();
                BigInteger left = st.pop();
                st.push(left.divide(right));
                break;
            }

            case "^": {
                BigInteger right = st.pop();
                BigInteger left = st.pop();
                st.push(left.pow(right.intValueExact()));
                break;
            }

            default:
                st.push(new BigInteger(cmd));
                break;
            }
        }
    }
}

public class Main2 {
    public static void main(String[] args) throws Exception {
        Solution solution = new Solution();
        solution.run();
        solution.out.close();
    }
}
