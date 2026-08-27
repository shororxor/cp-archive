#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

#define ll long long
#define int ll
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

int LEN(int l, int r) { return r - l + 1; }
int SUM(int l, int r) { return (l + r) * (r - l + 1) / 2; }

int add(int &a, int b) {
    a = (a + b) % MOD;
    return a % MOD;
}

struct SegTree {
    int n;
    vector<int> sum;
    vector<pair<int,int>> lazy;

    SegTree(int n_) : n(n_) {
        sum.assign(4 * n + 1, 0);
        lazy.assign(4 * n + 1, {0, 0});
    }

    void pushDown(int i, int l, int r, int m) {
        if (lazy[i].first == 0 && lazy[i].second == 0) return;

        int &A = lazy[i].first;
        int &B = lazy[i].second;

        sum[i << 1] = (sum[i << 1] + A * SUM(l, m) % MOD) % MOD;
        sum[i << 1] = (sum[i << 1] + B * LEN(l, m) % MOD) % MOD;

        sum[i << 1 | 1] = (sum[i << 1 | 1] + A * SUM(m + 1, r) % MOD) % MOD;
        sum[i << 1 | 1] = (sum[i << 1 | 1] + B * LEN(m + 1, r) % MOD) % MOD;

        FOR(j, i << 1, i << 1 | 1) {
            add(lazy[j].first, A);
            add(lazy[j].second, B);
        }

        A = 0; B = 0;
    }

    void udpate(int i, int l, int r, int u, int v, int A, int B) {
        if (r < u || l > v || l > r || u > v) return;
        if (u <= l && r <= v) {
            sum[i] = (sum[i] + A * SUM(l, r) % MOD) % MOD;
            sum[i] = (sum[i] + B * LEN(l, r) % MOD) % MOD;

            add(lazy[i].first, A);
            add(lazy[i].second, B);
            return;
        }

        int m = (l + r) >> 1;
        this->pushDown(i, l, r, m);
        udpate(i << 1, l, m, u, v, A, B);
        udpate(i << 1 | 1, m + 1, r, u, v, A, B);
        sum[i] = (sum[i << 1] + sum[i << 1 | 1]) % MOD;
    }

    int query(int i, int l, int r, int u, int v) {
        if (r < u || l > v || l > r || u > v) return 0;
        if (u <= l && r <= v) return sum[i];

        int m = (l + r) >> 1;
        this->pushDown(i, l, r, m);
        int L = query(i << 1, l, m, u, v);
        int R = query(i << 1 | 1, m + 1, r, u, v);
        return (L + R) % MOD;
    }
};

inline void solve() {
    int n, q; cin >> n >> q;
    SegTree tree(n);

    while(q--) {
        int t, l, r; cin >> t >> l >> r;
        if (t == 1) {
            int A, B; cin >> A >> B;
            tree.udpate(1, 1, n, l, r, A, B - l * A);
        }
        else {
            printf("%lld\n", tree.query(1, 1, n, l, r));
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