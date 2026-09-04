// #cpp | #codeforces | #kmp #string #hashing
// E. Test
// https://codeforces.com/problemset/problem/25/E

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
#define REP(i, r) for (int i = 0; i < r; i++)
#define BITSET(size, x) std::bitset<size + 1>(x).to_string().c_str()
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int, int>
#define complex complex<long double>
#define ite std::vector<int>::iterator

template <class T> bool minimize(T &x, T y) {
    if (x > y)
        x = y;
    else
        return 0;
    return 1;
}

template <class T> bool maximize(T &x, T y) {
    if (x < y)
        x = y;
    else
        return 0;
    return 1;
}

const int MAX = 1e5;

int lenS1, lenS2, lenS3;
char newStr[2 * MAX + 2];
char s[3][MAX + 2];
int kmp[MAX + 2];

int match(char s1[MAX + 2], char s2[MAX + 2], int n, int m) {
    int k = kmp[1] = 0;
    FOR(i, 2, m) {
        while (k > 0 && s2[k + 1] != s2[i])
            k = kmp[k];
        kmp[i] = s2[k + 1] == s2[i] ? ++k : 0;
    }

    k = 0;
    FOR(i, 1, n) {
        while (k > 0 && s2[k + 1] != s1[i])
            k = kmp[k];
        if (s2[k + 1] == s1[i])
            k++;
        if (k == m)
            return m;
    }

    while (k > m || k > n)
        k = kmp[k];
    return k;
}

int compute(vector<int> &order) {
    int length = lenS1 + lenS2 + lenS3;

    int n = strlen(s[order[0]] + 1);
    int m = strlen(s[order[1]] + 1);
    int h = strlen(s[order[2]] + 1);

    int k = match(s[order[0]], s[order[1]], n, m);
    if (k == m) {
        length -= m;
        length -= match(s[order[0]], s[order[2]], n, h);
        return length;
    } else {
        length -= k;
        FOR(i, 1, n) newStr[i] = s[order[0]][i];
        FOR(i, k + 1, m) newStr[n + i - k] = s[order[1]][i];

        length -= match(newStr, s[order[2]], n + m - k, h);
        return length;
    }
}

void solve() {
    scanf("%s%s%s", s[0] + 1, s[1] + 1, s[2] + 1);
    lenS1 = strlen(s[0] + 1);
    lenS2 = strlen(s[1] + 1);
    lenS3 = strlen(s[2] + 1);

    int ans = lenS1 + lenS2 + lenS3;
    vector<int> order = {0, 1, 2};

    do {
        minimize(ans, compute(order));
    } while (next_permutation(order.begin(), order.end()));

    printf("%d\n", ans);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
    return 0;
}
