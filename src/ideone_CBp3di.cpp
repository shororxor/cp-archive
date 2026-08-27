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
    int val, pref, suff, first, last;
    Node(int val_, int pref_, int suff_, int first_, int last_) {
        val = val_;
        pref = pref_;
        suff = suff_;
        first = first_;
        last = last_;
    }
};  

struct SegTree {
    int n;
    vector<Node> nodes;

    SegTree(int n_ ) : n(n_) {
        nodes.assign(4 * n + 1, {0, 0, 0, 0, 0});
    }

    void update(int i, int l, int r, int u, int v, int c) {
        if (r < u || l > v || l > r || u > v) return;
        if (u == l && r == v) {
            nodes[i].val = 1;
            nodes[i].pref = 1;
            nodes[i].suff = 1;
            nodes[i].first = c;
            nodes[i].last = c;
            return;
        }

        int m = (l + r) >> 1;
        update(i << 1, l, m, u, v, c);
        update(i << 1 | 1, m + 1, r, u, v, c);

        // push up
        nodes[i].val = nodes[i << 1].val + nodes[i << 1 | 1].val;
        nodes[i].first = nodes[i << 1].first;
        nodes[i].last = nodes[i << 1 | 1].last;
        nodes[i].pref = nodes[i << 1].pref;
        nodes[i].suff = nodes[i << 1 | 1].suff;

        if (nodes[i << 1].last <= nodes[i << 1 | 1].first) {
            nodes[i].val += nodes[i << 1].suff * nodes[i << 1 | 1].pref;
            if (nodes[i << 1].pref == (m - l + 1)) {
                nodes[i].pref += nodes[i << 1 | 1].pref;
            }
            if (nodes[i << 1 | 1].suff == (r - (m + 1) + 1)) {
                nodes[i].suff += nodes[i << 1].suff;
            }
        }
    }

    Node query(int i, int l, int r, int u, int v) {
        if (r < u || l > v || l > r || u > v) return { 0, 0, 0, NEGINF, POSINF };
        if (u <= l && r <= v) return nodes[i];

        int m = (l + r) >> 1;
        Node L = query(i << 1, l, m, u, v);
        Node R = query(i << 1 | 1, m + 1, r, u, v);

        // merge result
        Node ans(0, 0, 0, 0, 0);
        ans.val = L.val + R.val;
        ans.first = L.first;
        ans.last = R.last;
        ans.pref = L.pref;
        ans.suff = R.suff;

        if (L.last <= R.first) {
            ans.val += L.suff * R.pref;
            if (L.pref == (m - l + 1)) {
                ans.pref += R.pref;
            }
            if (R.suff == (r - (m + 1) + 1)) {
                ans.suff += L.suff;
            }
        }
        return ans;
    }
};

inline void solve() {
    int n, q; scanf("%lld%lld", &n, &q);
    SegTree tree(n);

    FOR(i, 1, n) {
        int c; scanf("%lld", &c);
        tree.update(1, 1, n, i, i, c);
    }

    FOR(i, 1, q) {
        int t, x, y; scanf("%lld%lld%lld", &t, &x, &y);
        if (t == 1) tree.update(1, 1, n, x, x, y);
        else printf("%lld\n", tree.query(1, 1, n, x, y).val);
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