// #cpp | #leetcode | #monotonic_stack
// Remove K Digits
// https://leetcode.com/problems/remove-k-digits/description/

#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

class Solution {
  public:
    string removeKdigits(string num, int k) {
        stack<int> st;
        int cnt = 0;

        for (int i = 0; i < (int)num.size(); i++) {
            int digit = num[i] - '0';
            while (!st.empty() && digit < st.top() && cnt < k) {
                st.pop();
                cnt++;
            }
            st.push(digit);
        }

        int r = k - cnt;
        while (r-- > 0 && !st.empty()) {
            st.pop();
        }

        string ans;
        while (!st.empty()) {
            ans.push_back(st.top() + '0');
            st.pop();
        }
        string rev(ans.rbegin(), ans.rend());

        int i = 0;
        while (rev[i] == '0')
            i++;
        return rev == "" || i == (int)rev.size() ? "0" : rev.substr(i);
    }
};

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Solution solution;
    string num;
    int k;
    cin >> num >> k;
    cout << solution.removeKdigits(num, k);
    return 0;
}
