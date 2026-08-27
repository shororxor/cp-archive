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

struct Data {
    int u, v, c;
    Data(int u = 0, int v = 0, int c = 0) {
        this->u = u;
        this->v = v;
        this->c = c;
    }

    bool operator<(const Data& other) const {
        return this->c < other.c;
    }
};

struct DSU {
    vector<int> par, rank;

    inline void init(int n) {
        par.resize(n + 1);
        rank.resize(n + 1);
        FOR(u, 1, n) {
            par[u] = u;
            rank[u] = 1;
        }
    }

    inline int root(int u) {
        if (u != par[u]) par[u] = root(par[u]);
        return par[u];
    }

    inline bool merge(int u, int v) {
        u = root(u);
        v = root(v);

        if (u == v) return false;
        if (rank[u] < rank[v]) swap(u, v);
        par[v] = u;
        if (rank[u] == rank[v]) rank[u]++;
        return true;
    }
};

vector<Data> edges;

inline void solve() {
    int n, m; cin >> n >> m;
    FOR(i, 1, m) {
        int u, v, c;
        cin >> u >> v >> c;
        edges.emplace_back(u, v, c);
    }

    sort(edges.begin(), edges.end());
    DSU dsu; dsu.init(n);

    int ans = 0;
    FOR(i, 0, m-1) {
        if (dsu.merge(edges[i].u, edges[i].v)) {
            ans += edges[i].c;
        }
    }
    cout << ans << '\n';
}

/** This is the end of my solution **/
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
}

