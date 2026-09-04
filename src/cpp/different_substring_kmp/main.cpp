// #cpp | #kmp #string
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

const int MAX = 100;

int N;
int kmp[MAX + 1], z[MAX + 1];
char str[MAX + 2];

int calKMP(int j) {
    fill(kmp, kmp + N + 1, 0);
    int res = 0;
    int k = kmp[j] = 0;
    FOR(i, j + 1, N) {
        while (k > 0 && str[j + k] != str[i])
            k = kmp[k];
        kmp[i] = str[j + k] == str[i] ? ++k : 0;
        res = max(res, kmp[i]);
    }
    return res;
}

int calKMPRev(int j) {
    fill(kmp, kmp + N + 1, 0);
    int k = kmp[1] = 0;
    int res = 0;
    FOR(i, 2, j) {
        while (k > 0 && str[j - k] != str[j - i + 1])
            k = kmp[k];
        kmp[i] = str[j - k] == str[j - i + 1] ? ++k : 0;
        res = max(res, kmp[i]);
    }
    return res;
}

int calZFunction(int j) {
    fill(z, z + N + 1, 0);
    int res = 0;

    for (int i = j + 1, l = j, r = j; i <= N; i++) {
        if (i <= r)
            z[i] = min(z[i - l + 1], r - i + 1);
        while (i + z[i] - 1 < N && str[j + z[i]] == str[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r) {
            r = i - z[i] + 1;
            l = i;
        }
        res = max(res, z[i]);
    }
    return res;
}

int calZFunctionRev(int j) {
    fill(z, z + N + 1, 0);
    int res = 0;
    for (int i = 2, l = 1, r = 1; i <= j; i++) {
        if (i <= r)
            z[i] = min(z[i - l + 1], r - i + 1);
        while (i + z[i] - 1 < j && str[j - z[i]] == str[j - (i + z[i]) + 1])
            ++z[i];
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
        res = max(res, z[i]);
    }
    return res;
}

void solve() {
    scanf("%s", str + 1);
    N = strlen(str + 1);

    int ans = 0;
    FOR(i, 1, N) ans += i - calKMPRev(i);
    cout << ans << '\n';

    ans = 0;
    FORD(i, N, 1) ans += (N - i + 1) - calZFunction(i);
    cout << ans << '\n';
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
