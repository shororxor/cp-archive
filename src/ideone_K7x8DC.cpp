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
    vector<int> rank, valid;
    vector<pair<int,int>> par;
 
    inline void init(int n) {
        rank.resize(n + 1);
        par.resize(n + 1);
        valid.resize(n + 1);
        FOR(u, 1, n) {
            rank[u] = 0;
            par[u] = {u, 0};
            valid[u] = true;
        }
    }
 
    inline pair<int,int> root(int u) {
        if (u != par[u].first) {
            int color = par[u].second;
            par[u] = root(par[u].first);
            par[u].second ^= color;
        }
        return par[u];
    }
 
    inline void merge(int u, int v) {
        auto [pu, x] = root(u);
        auto [pv, y] = root(v);
 
        if (pu == pv && x == y) valid[pu] = false;
        else {
            if (rank[pu] < rank[pv]) swap(pu, pv);
            par[pv] = {pu, x ^ y ^ 1};
            valid[pu] &= valid[pv];
            if (rank[pu] == rank[pv]) rank[pu]++;
        }
    }
 
    inline bool check(int u) {
        return valid[root(u).first];
    }
};
 
inline void solve() {
    int n; cin >> n;
    DSU dsu; dsu.init(n);
 
    int q; cin >> q;
    while(q--) {
        int t; cin >> t;
        if (t == 1) {
            int u, v; cin >> u >> v;
            dsu.merge(u, v);
        }
        else if (t == 2) {
            int u; cin >> u;
            printf("Is Bipartite = %d\n", (int)dsu.check(u));
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
