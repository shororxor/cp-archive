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
#define BITSET(size, x) std::bitset<size + 1>(x).to_string().c_str()
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int,int>
#define complex complex<long double>

const int POSINF = 1e9;
const int NEGINF = -1e9;
const int MOD = 1000000007;
const double PI = 3.14159265359;

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

const int MAX = 500;
int a[MAX + 1];
int sum[MAX + 1];
int dp[5][5];

int n, q, C;

void add(int &a, int b) {
    a += b;
    while(a >= MOD) a -= MOD;
}

void mul(int &a, int b) {
    a = 1LL * a * b % MOD;
}

struct SegmentTree {
    int n;
    vector<int> sum;
    vector<pii> lazy;

    SegmentTree(int n_) : n(n_) {
        sum.assign(4 * n + 1, 0);
        lazy.assign(4 * n + 1, {0, 0});
    }

    void pushDown(int i, int l, int r) {
        if (lazy[i].first == 0 && lazy[i].second == 0) return;
        int m = (l + r) >> 1;

        if (lazy[i].first != 0) {
            mul(sum[i << 1], lazy[i].first);
            mul(sum[i << 1 | 1], lazy[i].first);
            add(lazy[i << 1].first, lazy[i].first);
            add(lazy[i << 1 | 1].first, lazy[i].first);
        }

        if (lazy[i].second != 0) {
            add(sum[i << 1], lazy[i].second * (m - l + 1));
            add(sum[i << 1 | 1], lazy[i].second * (r - (m + 1) + 1));
            add(lazy[i << 1].second, lazy[i].second);
            add(lazy[i << 1 | 1].second, lazy[i].second);
        }

        lazy[i] = {0, 0};
    }

    void update(int i, int l, int r, int u, int v, int c, int t) {
        if (r < u || l > v || l > r || u > v) return;
        if (u <= l && r <= v) {
            if (t == 1) {
                mul(sum[i], c);
                add(lazy[i].first, c);
            }
            else {
                add(sum[i], c * (r - l + 1));
                add(lazy[i].second, c);
            }
            return;
        }

        pushDown(i, l, r);
        int m = (l + r) >> 1;
        update(i << 1, l, m, u, v, c, t);
        update(i << 1 | 1, m + 1, r, u, v, c, t);
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }

    int query(int i, int l, int r, int u, int v) {
        if (r < u || l > v || l > r || u > v) return 0;
        if (u <= l && r <= v) return sum[i];

        pushDown(i, l, r);
        int m = (l + r) >> 1;
        int L = query(i << 1, l, m, u, v);
        int R = query(i << 1 | 1, m + 1, r, u, v);
        return R + L;
    }

    void update(int u, int v, int c, int t) {
        this->update(1, 1, n, u, v, c, t);
    }

    int query(int u, int v) {
        return this->query(1, 1, n, u, v);
    }
};

int pw(int a, int k) {
    int res = 1;
    a %= MOD;
    while(k) {
        if (k & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        k >>= 1;
    }
    return res;
}

int compute(SegmentTree* tree, int l, int r, int k) {
    int ans = 0;
    FOR(u, l, r) FOR(v, u, r) {
        FOR(p, 0, k) ans += dp[p][k] * pw(C, p) * pw(tree->query(u, v), k - p);
    }
    return ans;
}

inline void prepare() {
    FOR(n, 0, 4) {
        FOR(k, 0, n) {
            if (k == 0 || k == n) {
                dp[k][n] = 1;
                continue;
            }
            dp[k][n] = dp[k - 1][n - 1] + dp[k][n - 1];
        }
    }
}

inline void solve() {
    prepare();
    scanf("%d%d%d", &n, &q, &C);
    SegmentTree tree(n);

    FOR(i, 1, n) {
        scanf("%d", &a[i]);
        tree.update(i, i, a[i], 2);
    }

    FOR(i, 1, q) {
        int t, l, r; scanf("%d%d%d", &t, &l, &r);
        if (t == 1 || t == 2) {
            int c; scanf("%d", &c);
            FOR(i, l, r) {
                if (t == 1) tree.update(l, r, c, 1);
                else tree.update(l, r, c, 2);
            }
        }
        else {
            int n = r - l + 1;
            printf("%d ", n * (n + 1) / 2);
            FOR(k, 1, 4) printf("%d ", compute(&tree, l, r, k));
            printf("\n");
        }
    }
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
}