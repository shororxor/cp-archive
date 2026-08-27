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
const int NEFINF = -1e9;
const int MOD = 1000000007;
const double PI = 3.14159265359;

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

struct SegmentTree {
    int n;
    vector<int> sum, lazy;

    SegmentTree(int n_) : n(n_) {
        sum.assign(4 * n + 1, 0);
        lazy.assign(4 * n + 1, 0);
    }

    void pushDown(int i, int l, int r) {
        if (lazy[i] == 0) return;

        int m = (l + r) >> 1;
        sum[i << 1] += lazy[i] * (m - l + 1);
        sum[i << 1 | 1] += lazy[i] * (r - (m + 1) + 1);

        lazy[i << 1] += lazy[i];
        lazy[i << 1 | 1] += lazy[i];

        lazy[i] = 0;
    }

    void update(int i, int l, int r, int u, int v, int c) {
        if (r < u || l > v || l > r || u > v) return;
        if (u <= l && r <= v) {
            sum[i] += c * (r - l + 1);
            lazy[i] += c;
            return;
        }

        pushDown(i, l, r);
        int m = (l + r) >> 1;
        update(i << 1, l, m, u, v, c);
        update(i << 1 | 1, m + 1, r, u, v, c);

        sum[i] = sum[i << 1] + sum[i << 1 | 1]; // push up
    }

    int query(int i, int l, int r, int u, int v) {
        if (r < u || l > v || l > r || u > v) return 0;
        if (u <= l && r <= v) return sum[i];

        pushDown(i, l, r);
        int m = (l + r) >> 1;
        int L = query(i << 1, l, m, u, v);
        int R = query(i << 1 | 1, m + 1, r, u, v);
        return L + R; 
    }

    void update(int u, int v, int c) {
        this->update(1, 1, n, u, v, c);
    }

    int query(int u, int v) {
        return this->query(1, 1, n, u, v);
    }
};

inline void solve() {
    int n, q; cin >> n >> q;
    SegmentTree tree(n);

    while(q--) {
        int t; cin >> t;
        if (t == 1) {
            int u, v, c;
            cin >> u >> v >> c;
            tree.update(u, v, c);
        }
        else if (t == 2) {
            int u, v; 
            cin >> u >> v;
            cout << tree.query(u, v) << '\n';
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