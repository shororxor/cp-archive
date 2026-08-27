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
    const int MAX = 1e5 + 5;
    const int LOG = 17;
    const int ALPHABET_SIZE = 256;

    int N, k, classes;
    int p[MAX + 1];
    int pr[MAX + 1];
    int c[LOG + 1][MAX + 1];
    int cnt[MAX + 1];

    int lcp[MAX + 1];
    int rank[MAX + 1];
    int LOG2[MAX + 1];
    int dp[MAX + 1][LOG + 1];

    int block[26];
    int sum[26];
    int pos[26];
    
    char str[MAX + 2];

    void prepare() {
        LOG2[1] = 0;
        FOR(i, 2, MAX) LOG2[i] = LOG2[i / 2] + 1;
    }

    void debug() {
        FOR(i, 1, N) FOR(j, p[i], N) printf("%c", (j == N ? '\n' : str[j]));
        printf("\n");
    }

    void buildSA() {
        fill(cnt, cnt + MAX + 1, 0);

        k = 0;
        FOR(i, 1, N) cnt[str[i]]++;
        FOR(i, 1, ALPHABET_SIZE) cnt[i] += cnt[i - 1];
        FORD(i, N, 1) p[cnt[str[i]]--] = i;
    
        c[k][p[1]] = classes = 1;
        FOR(i, 2, N) c[k][p[i]] = str[p[i]] == str[p[i - 1]] ? classes : ++classes;

        k = 1;
        for(; (1 << k) <= N; k++) {
            FOR(i, 1, N) pr[i] = (p[i] - mask(k - 1) + N - 1) % N + 1;
            FOR(i, 1, N) cnt[c[k - 1][pr[i]]]++;
            FOR(i, 1, classes) cnt[i] += cnt[i - 1];
            FORD(i, N, 1) p[cnt[c[k - 1][pr[i]]]--] = pr[i];

            c[k][p[1]] = classes = 1;
            FOR(i, 2, N) {
                pii cur = {c[k - 1][p[i]], c[k - 1][(p[i] + mask(k - 1) - 1) % N + 1]};
                pii pre = {c[k - 1][p[i - 1]], c[k - 1][(p[i - 1] + mask(k - 1) - 1) % N + 1]};
                c[k][p[i]] = cur == pre ? classes : ++classes;
            }

            if (classes == N) break;
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
            while(i + k - 1 < N && j + k - 1 < N && str[i + k] == str[j + k]) ++k;
            lcp[rank[i]] = k;
            dp[rank[i]][0] = k;
            if (k) k--;
        }

        FOR(j, 1, LOG2[N]) FOR(i, 1, N - (1 << j))
            dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
    }

    int getLCP(int l, int r) {
        int k = LOG2[--r - l + 1];
        return min(dp[l][k], dp[r - (1 << k) + 1][k]);
    }

    int search(int k) {
        int L = 0, R = 25;
        while(L <= R) {
            int M = (L + R) >> 1;
            if (sum[M] >= k) R = M - 1;
            else L = M + 1; 
        }
        return R + 1;
    }

    bool compute(int sta, int offset, int fin, int inc, int& amount, vector<int>& mark) {
        FOR(i, sta + 1, fin) mark[i] = getLCP(sta, i);

        FOR(i, p[sta] + offset, N - 1) {
            int len = i - p[sta] + 1;
            while(fin > sta && mark[fin] < len) fin--;

            // case when k-th fall into this line and no lcp left
            if (fin == sta + 1 && mark[fin] < len) {
                int len = (N - 1) - i + 1;
                if (amount + len <= inc) {
                    int remain = inc - amount;
                    FOR(j, p[sta], i + remain - 1) printf("%c", str[j]);
                    return true;
                }
                else return false;
            }

            // case when we still have lcp to count
            else {
                amount += fin - sta + 1;
                if (amount >= inc) {
                    FOR(j, p[sta], i) printf("%c", str[j]);
                    return true;
                }
            }
        }
        return false;
    }

    void process(int k) {
        fill(cnt, cnt + MAX, 0);

        int cur = -1;
        FOR(i, 2, N) {
            int c = str[p[i]] - 'a';
            if (c != cur) pos[c] = i, cur = c;
            block[c] += (N - p[i]);
            cnt[c]++;
        }

        FOR(c, 0, 25) sum[c] = c > 0 ? sum[c - 1] + block[c] : block[c];

        int found = search(k);
        int inc = k - sum[found - 1];
        assert(inc > 0);

        int amount = 0;
        int sta = pos[found];
        int fin = sta + cnt[found] - 1;

        int offset = 0;
        bool flag = false;
        FOR(i, sta, fin) {
            vector<int> mark(N + 1, 0);
            if (compute(i, offset, fin, inc, amount, mark)) {
                flag = true; 
                break;
            }
            offset = mark[i + 1];
        }

        if (!flag) printf("No such line.\n");
    }

    void init() {
        scanf("%s", str + 1);
        N = strlen(str + 1);
        str[++N] = '$';
    }
}

void solve() {
    SA::prepare();
    SA::init();
    SA::buildSA();
    SA::buildLCP();

    int k; scanf("%d", &k);
    SA::process(k);
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