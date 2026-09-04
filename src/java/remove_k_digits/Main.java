// #java | #leetcode | #monotonic_stack
// Remove K Digits
// https://leetcode.com/problems/remove-k-digits/description/

import java.io.*;
import java.util.*;

class Solution {
    public String removeKdigits(String num, int k) {
        Stack<Integer> st = new Stack<>();
        char[] str = num.toCharArray();

        int cnt = 0;
        for (int i = 0; i < str.length; i++) {
            int digit = str[i] - '0';
            while (!st.empty() && cnt < k && digit < st.peek()) {
                st.pop();
                cnt++;
            }
            st.push(digit);
        }

        int r = k - cnt;
        while (r-- > 0 && !st.empty()) {
            st.pop();
        }

        StringBuilder ans = new StringBuilder();
        while (!st.empty()) {
            ans.append((char)(st.peek() + '0'));
            st.pop();
        }

        String rev = ans.reverse().toString();

        int i = 0;
        while (i < rev.length() && rev.charAt(i) == '0')
            i++;
        return rev == "" || i == rev.length() ? "0" : rev.substring(i);
    }
}

public class Main {
    static Solution solution = new Solution();

    public static void main(String[] args) throws Exception {
        BufferedReader br =
            new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);

        String num = br.readLine();
        int k = Integer.parseInt(br.readLine());
        out.println(solution.removeKdigits(num, k));
        out.close();
    }
}
