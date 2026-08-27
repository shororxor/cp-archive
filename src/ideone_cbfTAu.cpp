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
#define ite std::vector<int>::iterator

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


const int MAX = 30000;
int a[MAX + 1];

void merge(ite i, ite n, ite j, ite m, ite k) {
    while(i < n && j < m) {
        *k++ = min(*i, *j);
        if (*i <= *j) i++;
        else j++;
    }

    while(i < n) *k++ = *i++;
    while(j < m) *k++ = *j++;
}

struct SegTree {
    int n;
    vector<vector<int>> node;

    SegTree(int n_) : n(n_) {
        node.assign(4 * n + 1, vector<int>());
    }

    void build(int i, int l, int r) {
        if (l == r) {
            node[i].push_back(a[l]);
            return;
        }

        int m = (l + r) >> 1;
        build(i << 1, l, m);
        build(i << 1 | 1, m + 1, r);
        node[i].resize(r - l + 1);
        merge(node[i << 1].begin(), node[i << 1].end(), 
              node[i << 1 | 1].begin(), node[i << 1 | 1].end(), node[i].begin());
    }

    int query(int i, int l, int r, int u, int v, int k) {
        if (r < u || l > v || l > r || u > v) return 0;
        if (u <= l && r <= v) {
            ite idx = upper_bound(node[i].begin(), node[i].end(), k);
            return node[i].end() - idx;
        }

        int m = (l + r) >> 1;
        int L = query(i << 1, l, m, u, v, k);
        int R = query(i << 1 | 1, m + 1, r, u, v, k);
        return L + R;
    }
};

inline void solve() {
    int n; cin >> n;
    FOR(i, 1, n) cin >> a[i];

    SegTree tree(n);
    tree.build(1, 1, n);

    int q; cin >> q;
    while(q--) {
        int l, r, k;
        cin >> l >> r >> k;
        printf("%d\n", tree.query(1, 1, n, l, r, k));
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