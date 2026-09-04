// #cpp | #spoj | #binary_lifting #prefix_suffix #lcp #string #suffix_array
// LCS - Longest Common Substring
// https://www.spoj.com/problems/LCS/

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
#define REP(i, r) for (int i = 0; i < (r); i++)
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

namespace SA {
const int MAX = 250000 << 1;
const int LOG = 18;
const int ALPHABET_SIZE = 256;

int lenStr1, N, k, classes;
int p[MAX + 1], pr[MAX + 1], c[LOG][MAX + 1], cnt[MAX + 1];
int lcp[MAX + 1], rank[MAX + 1];

char str[MAX + 2];

void output() {
    FOR(i, 1, N) FOR(j, p[i], N) printf("%c", (j == N ? '\n' : str[j]));
    printf("\n");
}

void process() {
    fill(cnt, cnt + MAX + 1, 0);

    k = 0;
    FOR(i, 1, N) cnt[str[i]]++;
    FOR(i, 1, ALPHABET_SIZE) cnt[i] += cnt[i - 1];
    FORD(i, N, 1) p[cnt[str[i]]--] = i;

    c[k][p[1]] = classes = 1;
    FOR(i, 2, N) c[k][p[i]] = str[p[i]] == str[p[i - 1]] ? classes : ++classes;

    k = 1;
    for (; (1 << k) <= N; k++) {
        FOR(i, 1, N) pr[i] = (p[i] - mask(k - 1) + N - 1) % N + 1;
        FOR(i, 1, N) cnt[c[k - 1][pr[i]]]++;
        FOR(i, 1, classes) cnt[i] += cnt[i - 1];
        FORD(i, N, 1) p[cnt[c[k - 1][pr[i]]]--] = pr[i];

        c[k][p[1]] = classes = 1;
        FOR(i, 2, N) {
            pii cur = {c[k - 1][p[i]],
                       c[k - 1][(p[i] + mask(k - 1) - 1) % N + 1]};
            pii pre = {c[k - 1][p[i - 1]],
                       c[k - 1][(p[i - 1] + mask(k - 1) - 1) % N + 1]};
            c[k][p[i]] = cur == pre ? classes : ++classes;
        }

        if (classes == N)
            break;
        fill(cnt, cnt + classes + 1, 0);
    }
}

void buildLCP() {
    FOR(i, 1, N) rank[p[i]] = i;
    k = 0;

    FOR(i, 1, N) {
        if (rank[i] == N) {
            k = 0;
            continue;
        }

        int j = p[rank[i] + 1];
        while (i + k - 1 < N && j + k - 1 < N && str[i + k] == str[j + k])
            ++k;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }

    int ans = 0;
    FOR(i, 2, N - 1) {
        if (lcp[i] > ans && ((p[i] < lenStr1 && p[i + 1] > lenStr1) ||
                             (p[i] > lenStr1 && p[i + 1] < lenStr1))) {
            ans = lcp[i];
        }
    }

    printf("%d\n", ans);
}

void init() {
    scanf("%s", str + 1);
    lenStr1 = strlen(str + 1);
    scanf("%s", str + lenStr1 + 1);
    N = strlen(str + 1);
    str[++N] = '$';
}
} // namespace SA

void solve() {
    SA::init();
    SA::process();
    SA::buildLCP();
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
