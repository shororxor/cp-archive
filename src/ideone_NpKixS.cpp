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
#define REP(i,l,r) for(int i=(l);i<(r);i++)
#define FORD(i,l,r) for(int i=(l);i>=(r);i--)
#define REPD(i,l,r) for(int i=(l);i>(r);i--)
#define BITSET(size, x) std::bitset<size>(x).to_string().c_str()
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int,int>
#define complex complex<long double>

const int POSINF = 1e9;
const int NEFINF = -1e9;
// const int MOD = 1000000007;
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
    vector<unordered_map<int,int>> color;

    inline void init(int n) {
        par.resize(n + 1);
        size.resize(n + 1);
        color.resize(n + 1);
        FOR(u, 1, n) {
            par[u] = u;
            size[u] = 1;
        }
    }

    inline int root(int u) {
        return par[u] = (u == par[u] ? u : root(par[u]));
    }

    inline bool merge(int u, int v) {
        u = root(u);
        v = root(v);
        if (u == v) return false;

        if (size[u] < size[v]) swap(u, v);
        par[v] = u;
        size[u] += size[v];
        for(auto& c : color[v]) color[u][c.first] += c.second;
        color[v].clear();
        return true;
    }

    inline int query(int u, int c) {
        u = root(u);
        return color[u].count(c) ? color[u][c] : 0;
    }
};

inline void solve() {
    int n; cin >> n;
    DSU dsu; dsu.init(n);
    FOR(u, 1, n) {
        int c; cin >> c;
        dsu.color[u][c] += 1;
    }

    int q; cin >> q;
    while(q--) {
        int type; cin >> type;
        if (type == 1) {
            int u, v; cin >> u >> v;
            dsu.merge(u, v);
        }
        else if (type == 2) {
            int u, c; cin >> u >> c;
            cout << dsu.query(u, c) << '\n';
        }
    }
}

/** This is the end of my solution **/
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
}
