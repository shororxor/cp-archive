#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

#define ll long long
#define mask(i) (1 << (i))
#define bit(x, i)  (((x) >> (i)) & 1)
#define onbit(x, i) ((x) = (x) | mask(i))
#define offbit(x, i) ((x) = (x) & (~mask(i)))
#define pcount(i) __builtin_popcount(i)
#define bctz(i) __builtin_ctz(i)
#define all(v) v.begin(), v.end()
#define all1(v) v.begin()+1, v.end()
#define sz(v) (int)v.size()
#define sqr(x) ((x) * (x))
#define FOR(i,l,r) for(int i=(l);i<=(r);i++)
#define FORD(i,l,r) for(int i=(l);i>=(r);i--)
#define REP(i, r) for(int i=0;i<(r);i++)
#define BITSET(size, x) std::bitset<size + 1>(x).to_string().c_str()
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int,int>
#define complex complex<long double>
#define ite std::vector<int>::iterator
#define next __next

template <class T> bool minimize(T& x,T y) {
    if (x > y) x = y; else return 0; return 1;
}
 
template <class T> bool maximize(T& x,T y) {
    if (x < y) x = y; else return 0; return 1;
}

namespace SA {
    const int MAX = 1e5 + 10;
    const int LOG = 16;
    const int MAXK = 10;
    const int ALPHABET_SIZE = 256;

    int N, M, k, total, min_length, classes;
    pii p[MAX + 1]; 
    int pr[MAX + 1], c[LOG + 1][MAX + 1], cnt[MAX + 1];
    int lcp[MAX + 1], rank[MAX + 1];
    pii segment[MAXK + 1];

    int sum[MAX + 1], dp[MAX + 1][LOG + 1], LOG2[MAX + 1];
    char str[MAX + 2];

    void prepare() {
        LOG2[1] = 0;
        FOR(i, 2, MAX) LOG2[i] = LOG2[i / 2] + 1;
    }

    int typeString(int i) {
        assert(i >= 1 && i <= N);
        if (i == N) return M + 1;
        int L = 1;
        int R = M;

        while(L <= R) {
            int M = (L + R) >> 1;
            if (segment[M].second >= i) R = M - 1;
            else L = M + 1;
        }

        return R + 1;
    }

    int getSum(int l, int r) {
        return sum[r] - sum[l - 1];
    }

    int getMin(int l, int r) {
        int k = LOG2[r - l + 1];
        return min(dp[l][k], dp[r - mask(k) + 1][k]);
    }

    void debug() {
        FOR(i, 1, N) {
            FOR(j, p[i].first, N) printf("%c", (j == N ? ' ' : str[j]));
            printf("%d\n", p[i].second);
        }
    }

    void process() {
        fill(cnt, cnt + MAX + 1, 0);

        k = 0;
        FOR(i, 1, N) cnt[str[i]]++;
        FOR(i, 1, ALPHABET_SIZE) cnt[i] += cnt[i - 1];
        FORD(i, N, 1) p[cnt[str[i]]--].first = i;

        c[k][p[1].first] = classes = 1;
        FOR(i, 2, N) c[k][p[i].first] = str[p[i].first] == str[p[i - 1].first] ? classes : ++classes;

        k = 1;
        for(; (1 << k) <= N; k++) {
            FOR(i, 1, N) pr[i] = (p[i].first - mask(k - 1) + N - 1) % N + 1;
            FOR(i, 1, N) cnt[c[k - 1][pr[i]]]++;
            FOR(i, 1, classes) cnt[i] += cnt[i - 1];
            FORD(i, N, 1) p[cnt[c[k - 1][pr[i]]]--].first = pr[i];

            c[k][p[1].first] = 1;
            FOR(i, 1, N) {
                pii cur = {c[k - 1][p[i].first], c[k - 1][(p[i].first + mask(k - 1) - 1) % N + 1]};
                pii pre = {c[k - 1][p[i - 1].first], c[k - 1][(p[i - 1].first + mask(k - 1) - 1) % N + 1]};
                c[k][p[i].first] = cur == pre ? classes : ++classes;
            }

            if (classes == N) break;
            fill(cnt, cnt + classes + 1, 0);
        }

        FOR(i, 1, N) {
            p[i].second = typeString(p[i].first);
            sum[i] = sum[i - 1] + p[i].second;
        }
    }

    void buildLCP() {
        FOR(i, 1, N) rank[p[i].first] = i;
        k = 0;
        FOR(i, 1, N) {
            if (rank[i] == N) {
                k = 0;
                continue;
            }

            int j = p[rank[i] + 1].first;
            while(i + k - 1 < N && j + k - 1 < N && str[i + k] == str[j + k]) ++k;
            lcp[rank[i]] = k;
            dp[rank[i]][0] = k;
            if (k) k--;
        }

        FOR(j, 1, LOG2[N]) FOR(i, 1, N - (1 << j))
            dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
    }

    void output() {
        int ans = 0;
        FOR(i, 1, N - M + 1) {
            if (getSum(i, i + M - 1) == total) {
                maximize(ans, min(min_length, getMin(i, i + M - 2)));
            }
        }
        printf("%d\n", ans);
    }

    void init() {
        scanf("%d", &M);
        N = 0;
        min_length = 1e9;
        FOR(i, 1, M) {
            scanf("%s", str + N + 1);
            segment[i].first = N + 1;
            N = strlen(str + 1);
            segment[i].second = N;
            minimize(min_length, segment[i].second - segment[i].first + 1);
        }
        if (M == 1) {
            printf("%d\n", N);
            return;
        }
        str[++N] = '$';
        total = (M * (M + 1)) >> 1;

        process();
        buildLCP();
        output();
    }
}

void solve() {
    SA::init();
}

signed main() {
    #ifndef ONLINE_JUDGE
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    SA::prepare();
    int T; scanf("%d", &T); while(T--) solve();
    return 0;
}