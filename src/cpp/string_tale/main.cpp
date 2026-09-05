// #cpp | #tmus | #kmp #string #zfunction
// 1423. String Tale
// https://acm.timus.ru/problem.aspx?space=1&num=1423

#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

#define ll long long
#define mask(i) (1 << (i))
#define bit(x, i) (((x) >> (i)) & 1)
#define onbit(x, i) ((x) = (x) | mask(i))
#define offbit(x, i) ((x) = (x) & (~mask(i)))
#define pcount(i) __builtin_popcount(i)
#define bctz(i) __builtin_ctz(i)
#define all(v) v.begin(), v.end()
#define all1(v) v.begin() + 1, v.end()
#define sz(v) (int)v.size()
#define sqr(x) ((x) * (x))
#define FOR(i, l, r) for (int i = (l); i <= (r); i++)
#define FORD(i, l, r) for (int i = (l); i >= (r); i--)
#define BITSET(size, x) std::bitset<size + 1>(x).to_string().c_str()
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int, int>
#define complex complex<long double>
#define ite std::vector<int>::iterator
#define next __next

template <class T> bool minimize(T &x, T y) {
    if (x > y) x = y;
    else return 0;
    return 1;
}

template <class T> bool maximize(T &x, T y) {
    if (x < y) x = y;
    else return 0;
    return 1;
}

const int MAX = 250005;

int lenStr;
int z[2 * MAX];
char str[2 * MAX];

int compute(const string &s1, const string &s2) {
    fill(z, z + lenStr + 1, 0);
    lenStr = 0;
    for (auto &c : s1) str[++lenStr] = c;

    str[++lenStr] = '#';
    for (auto &c : s2) str[++lenStr] = c;

    int ans = lenStr;
    z[1] = 0;
    for (int i = 2, l = 1, r = 1; i <= lenStr; i++) {
        if (i <= r) z[i] = min(z[i - l + 1], r - i + 1);
        while (i + z[i] <= lenStr && str[z[i] + 1] == str[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
        if (i + z[i] - 1 == lenStr) minimize(ans, i);
    }

    return z[ans];
}

void solve() {
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;

    int match1 = compute(s1, s2);
    int match2 = compute(s2, s1);
    if (match1 + match2 == n) cout << (match1 == n ? 0 : match2) << '\n';
    else cout << -1 << '\n';
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
    return 0;
}
