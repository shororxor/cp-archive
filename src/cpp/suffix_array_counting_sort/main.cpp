// #cpp | #suffix_array #sorting #string
// Suffix array counting sort

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

namespace SuffixArray {
const int MAX = 100;
const int LOG = 16;
const int ALPHABET_SIZE = 256;

int classes, N, k;
int p[MAX + 1], pr[MAX + 1], c[LOG + 1][MAX + 1], cnt[MAX + 1];
int rank[MAX + 1], lcp[MAX + 1], LOG2[MAX + 1], dp[MAX + 1][LOG + 1];
char str[MAX + 2];

void debug() {
    FOR(i, 1, N) printf("p[%d] = %d | c[%d] = %d\n", i, p[i], p[i], c[k][p[i]]);
    printf("\n");
}

void output() {
    FOR(i, 1, N) FOR(j, p[i], N) printf("%c", (j == N ? '\n' : str[j]));
}

void process() {
    k = 0;
    FOR(i, 1, N) cnt[str[i]]++;
    FOR(i, 1, ALPHABET_SIZE) cnt[i] += cnt[i - 1];
    FORD(i, N, 1) p[cnt[str[i]]--] = i;

    c[0][p[1]] = classes = 1;
    FOR(i, 2, N) c[0][p[i]] = str[p[i]] == str[p[i - 1]] ? classes : ++classes;

    k = 1;
    for (; (1 << k) <= N; k++) {
        if (classes == N)
            break;
        FOR(i, 1, N) pr[i] = (p[i] - mask(k - 1) + N - 1) % N + 1;
        fill(cnt, cnt + classes + 1, 0);

        FOR(i, 1, N) cnt[c[k - 1][pr[i]]]++;
        FOR(i, 1, classes) cnt[i] += cnt[i - 1];
        FORD(i, N, 1) p[cnt[c[k - 1][pr[i]]]--] = pr[i];

        c[k][p[1]] = classes = 1;
        FOR(i, 2, N) {
            pii pre = {c[k - 1][p[i - 1]],
                       c[k - 1][(p[i - 1] + mask(k - 1) - 1) % N + 1]};
            pii cur = {c[k - 1][p[i]],
                       c[k - 1][(p[i] + mask(k - 1) - 1) % N + 1]};
            c[k][p[i]] = pre == cur ? classes : ++classes;
        }
    }

    SuffixArray::output();
}

void init() {
    scanf("%s", str + 1);
    N = strlen(str + 1);
    str[++N] = '$';

    LOG2[1] = 0;
    FOR(i, 2, N) LOG2[i] = LOG2[i / 2] + 1;
}

void smallestCyclicShift() { printf("Smallest Cylic Shift = %d\n", p[2]); }

bool greater(int start, char T[]) {
    int i = 0, lenT = strlen(T + 1);
    while (start + i - 1 < N && i < lenT && str[start + i] == T[1 + i])
        i++;
    return i == lenT - 1 ? false : str[start + i] > T[1 + i];
}

bool lesser(int start, char T[]) {
    int i = 0, lenT = strlen(T + 1);
    while (start + i - 1 < N && i < lenT && str[start + i] == T[i + 1])
        i++;
    return str[start + i] < T[1 + i];
}

void findSubstring(char T[]) {
    int L = 1, R = N, first = -1, second = -1;
    while (L <= R) {
        int M = (L + R) >> 1;
        if (lesser(p[M], T))
            L = M + 1;
        else
            R = M - 1;
    }
    first = L;

    R = N;
    while (L <= R) {
        int M = (L + R) >> 1;
        if (greater(p[M], T))
            R = M - 1;
        else
            L = M + 1;
    }
    second = R;
    printf("Number of occurrence = %d\n", second - first + 1);
}

int compareTwoSubstrings(int i, int j, int l) {
    int k = (int)log2(l);
    pii A = {c[k][i], c[k][(i + l - (1 << k) + N - 1) % N + 1]};
    pii B = {c[k][j], c[k][(j + l - (1 << k) + N - 1) % N + 1]};
    return A == B ? 0 : A < B ? -1 : 1;
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
            k++;
        lcp[rank[i]] = k;
        dp[rank[i]][0] = k;
        if (k)
            k--;
    }

    FOR(j, 1, LOG2[N])
    FOR(i, 1, N - (1 << j))
    dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
}

int longestCommonPrefix(int i, int j) {
    int l = rank[i], r = rank[j];
    if (l > r)
        swap(l, r);
    int k = LOG2[--r - l + 1];
    return min(dp[l][k], dp[r - (1 << k) + 1][k]);
}

int numStrings() {
    int ans = 0;
    FOR(i, 1, N) {
        ans += N - p[i];
        if (i > 1)
            ans -= lcp[i - 1];
    }
    return ans;
}
} // namespace SuffixArray

int lenT;
char T[SuffixArray::MAX + 2];

void solve() {
    SuffixArray::init();
    SuffixArray::process();
    SuffixArray::smallestCyclicShift();
    scanf("%s", T + 1);
    T[strlen(T + 1) + 1] = '$';
    SuffixArray::findSubstring(T);
    printf("Compare Two String: %d\n",
           SuffixArray::compareTwoSubstrings(8, 11, 6));
    SuffixArray::buildLCP();
    printf("Longest Common Prefix = %d\n",
           SuffixArray::longestCommonPrefix(8, 18));
    printf("Number of Substrings = %d\n", SuffixArray::numStrings());
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
