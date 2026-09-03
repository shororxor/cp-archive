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
#define BITSET(size, x) std::bitset<size>(x).to_string().c_str()
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

/** This is the end of my template **/


struct DSU {
    vector<int> par, size;
    stack<pair<int*, int>> history;

    inline void init(int n) {
        par.resize(n + 1);
        size.resize(n + 1);

        FOR(u, 1, n) {
            par[u] = u;
            size[u] = 1;
        }
        while(!history.empty()) history.pop();
    }

    inline int root(int u) {
        if (u == par[u]) return par[u];
        return root(par[u]);
    }

    inline int snapshot() {
        return (int)history.size();
    }

    inline bool same(int u, int v) {
        return root(u) == root(v);
    }

    inline bool merge(int u, int v) {
        u = root(u);
        v = root(v);

        if (u == v) return false;
        if (size[u] < size[v]) swap(u, v);
        
        history.emplace(&par[v], par[v]);
        history.emplace(&size[u], size[u]);

        par[v] = u;
        size[u] += size[v];
        return true;
    }

    inline void rollback(int snapshot) {
        while((int)history.size() > snapshot) {
            *history.top().first = history.top().second;
            history.pop();
        }
    }
};

struct Query {
    int t, u, v;
    Query(int t = 0, int u = 0, int v = 0) {
        this->t = t;
        this->u = u;
        this->v = v;
    }
};

struct QueryTree {
    DSU dsu;
    vector<vector<Query>> tree;
    
    inline void init(int n, int q) {
        dsu.init(n);
        tree.resize(4 * q + 1);
    }

    inline void update(Query query, int id, int l, int r, int u, int v) {
        if (v < l || u > r || r < l || v < u) return;
        if (u <= l && r <= v) {
            tree[id].push_back(query);
            return;
        }
        int m = (l + r) >> 1;
        update(query, id << 1, l, m, u, v);
        update(query, id << 1 | 1, m + 1, r, u, v);
    }

    inline void traverse(int id, int l, int r, vector<bool>& ans) {
        int snapshot = dsu.snapshot();

        for(Query& q : tree[id]) {
            if (q.t == 1) dsu.merge(q.u, q.v);
        }

        if (l == r) {
            for(Query& q : tree[id]) {
                if (q.t == 2) ans.push_back(dsu.same(q.u, q.v));
            }
        }
        else {
            int m = (l + r) >> 1;
            traverse(id << 1, l, m, ans);
            traverse(id << 1 | 1, m + 1, r, ans);
        }

        dsu.rollback(snapshot);
    }
};

inline void solve() {
    int n, q; cin >> n >> q;
    map<pair<int,int>, int> time;
    QueryTree qt; qt.init(n, q);

    FOR(i, 1, q) {
        int t, u, v; cin >> t >> u >> v;
        if (u > v) swap(u, v);
        if (t == 1) time[{u, v}] = i;
        if (t == 2) {
            qt.update(Query(1, u, v), 1, 1, q, time[{u, v}], i);
            time[{u, v}] = -1;
        }

        // query ask if (u, v) is connected or not
        if (t == 3) {
            qt.update(Query(2, u, v), 1, 1, q, i, i);
        }
    }

    // udpate edges that is not removed
    for(auto [e, t] : time) {
        if (t != -1) qt.update(Query(1, e.first, e.second), 1, 1, q, t, q);
    }

    vector<bool> ans;
    qt.traverse(1, 1, q, ans);
    for(bool x : ans) cout << (x ? "YES\n" : "NO\n");
}

/** This is the end of my solution **/
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