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

const int MAX = 1e5;
int a[MAX + 1];

struct SegTree {
    int n;
    vector<multiset<int>> node;

    SegTree(int n_) : n(n_) {
        node.resize(4 * n + 1);
    }

    void build(int i, int l, int r) {
        if (l == r) {
            node[i].insert(a[l]);
            return;
        }

        int m = (l + r) >> 1;
        build(i << 1, l, m);
        build(i << 1 | 1, m + 1, r);
        node[i] = node[i << 1];
        for(auto& x : node[i << 1 | 1]) node[i].insert(x);
    }

    void update(int i, int l, int r, int u, int v, int old, int val) {
        if (r < u || l > v || l > r || u > v) return;
        if (u == l && r == v) {
            node[i].clear();
            node[i].insert(val);
            return;
        }

        int m = (l + r) >> 1;
        update(i << 1, l, m, u, v, old, val);
        update(i << 1 | 1, m + 1, r, u, v, old, val);
        node[i].erase(node[i].find(old));
        node[i].insert(val);
    }

    int query(int i, int l, int r, int u, int v, int k) {
        if (r < u || l > v || l > r || u > v) return POSINF;
        if (u <= l && r <= v) {
            auto it = node[i].lower_bound(k);
            if (it == node[i].end())  return POSINF;
            return *it;
        }

        int m = (l + r) >> 1;
        int L = query(i << 1, l, m, u, v, k);
        int R = query(i << 1 | 1, m + 1, r, u, v, k);
        return min(L, R);
    }
};

inline void solve() {
    int n, q; scanf("%d%d", &n, &q);
    SegTree tree(n);

    FOR(i, 1, n) scanf("%d", &a[i]);
    tree.build(1, 1, n);

    while (q--) {
        int t; scanf("%d", &t);
        if (t == 1) {
            int i, v; scanf("%d%d", &i, &v);
            tree.update(1, 1, n, i, i, a[i], v);
            a[i] = v;
        }
        else {
            int l, r, k; scanf("%d%d%d", &l, &r, &k);
            int ans = tree.query(1, 1, n, l, r, k);
            if (ans >= POSINF) printf("-1\n");
            else printf("%d\n", ans);
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