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

struct Node {
    int node, sum, pref, suff;
};

struct SegTree {
    int n;
    vector<int> sum, pref, suff, node;

    SegTree(int n_) : n(n_) {
        sum.assign(4 * n + 1, 0);
        pref.assign(4 * n + 1, 0);
        suff.assign(4 * n + 1, 0);
        node.assign(4 * n + 1, 0);
    }

    void update(int i, int l, int r, int u, int v, int c) {
        if (r < u || l > v || l > r || u > v) return;
        if (l == u && r == v) {
            node[i] = c;
            sum[i] = c;
            suff[i] = c;
            pref[i] = c;
            return;
        }

        int m = (l + r) >> 1;
        update(i << 1, l, m, u, v, c);
        update(i << 1 | 1, m + 1, r, u, v, c);

        // pushup operation
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
        node[i] = max({node[i << 1], node[i << 1 | 1], suff[i << 1] + pref[i << 1 | 1]});
        pref[i] = max(pref[i << 1], sum[i << 1] + pref[i << 1 | 1]);
        suff[i] = max(suff[i << 1 | 1], sum[i << 1 | 1] + suff[i << 1]);
    }

    Node query(int i, int l, int r, int u, int v) {
        if (r < u || l > v || l > r || u > v) return { NEGINF, 0, NEGINF, NEGINF };
        if (u <= l && r <= v) return { node[i], sum[i], pref[i], suff[i] };

        int m = (l + r) >> 1;
        Node L = query(i << 1, l, m, u, v);
        Node R = query(i << 1 | 1, m + 1, r, u, v);

        // note here about the branching case
        int node = max({L.node, R.node, L.suff + R.pref});
        int sum = L.sum + R.sum;
        int pref = max(L.pref, L.sum + R.pref);
        int suff = max(R.suff, R.sum + L.suff);
        return {node, sum, pref, suff};
    }
};

inline void solve() {
    int n; scanf("%lld", &n);
    SegTree tree(n);

    FOR(i, 1, n) {
        int x; scanf("%lld", &x);
        tree.update(1, 1, n, i, i, x);
    }

    int q; scanf("%lld", &q);
    FOR(i, 1, q) {
        int x, y; scanf("%lld%lld", &x, &y);
        printf("%lld\n", tree.query(1, 1, n, x, y).node);
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