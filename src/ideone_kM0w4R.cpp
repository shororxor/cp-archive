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

struct Query {
    int l, r, k, id, ans;
};

bool comp1(const Query& q1, const Query& q2) {
    return q1.k < q2.k;
}

bool comp2(const Query& q1, const Query& q2) {
    return q1.id < q2.id;
}

const int MAX = 30000;
int a[MAX + 1];
pair<int,int> b[MAX + 1];
Query q[200001];

struct SegTree {
    int n;
    vector<int> node;

    SegTree(int n_) : n(n_) {
        node.assign(4 * n + 1, 0);
    }

    void update(int i, int l, int r, int u, int v, int c) {
        if (r < u || l > v || l > r || u > v) return;
        if (u == l && r == v) {
            node[i] = c;
            return;
        }

        int m = (l + r) >> 1;
        update(i << 1, l, m, u, v, c);
        update(i << 1 | 1, m + 1, r, u, v, c);
        node[i] = node[i << 1] + node[i << 1 | 1];
    }

    int query(int i, int l, int r, int u, int v) {
        if (r < u || l > v || l > r || u > v) return 0;
        if (u <= l && r <= v) return node[i];

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
    int n; cin >> n;
    SegTree tree(n);

    FOR(i, 1, n) {
        cin >> a[i];
        b[i] = {a[i], i};
        tree.update(i, i, 1);
    }
    sort(b + 1, b + n + 1);

    int m; cin >> m;
    FOR(i, 1, m) {
        cin >> q[i].l >> q[i].r >> q[i].k;
        q[i].id = i;
    }
    sort(q + 1, q + m + 1, comp1);

    int j = 1;
    FOR(i, 1, m) {
        for( ; j <= n && b[j].first <= q[i].k; j++) {
            tree.update(b[j].second, b[j].second, 0);
        }
        q[i].ans = tree.query(q[i].l, q[i].r);
    }

    sort(q + 1, q + m + 1, comp2);
    FOR(i, 1, m) cout << q[i].ans << '\n';
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