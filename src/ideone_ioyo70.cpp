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
    vector<int> rank;
    vector<pair<int,int>> par;

    inline void init(int n) {
        rank.resize(n + 1);
        par.resize(n + 1);
        FOR(u, 1, n) {
            par[u] = {u, 0};
            rank[u] = 1;
        }
    }
    
    inline pair<int,int> root(int u) {
        if (u != par[u].first) {
            int len = par[u].second;
            par[u] = root(par[u].first);
            par[u].second += len;
        }
        return par[u];
    }

    inline void merge(int u, int v) {
        u = root(u).first;
        v = root(v).first;
        
        if (u != v) {
            if (rank[u] < rank[v]) swap(u, v);
            par[v] = {u, 1};
            if (rank[u] == rank[v]) rank[u]++;
        }
    }
};

inline void solve() {
    DSU dsu; dsu.init(4);
    dsu.merge(1, 2);
    dsu.merge(3, 4);
    
    printf("node = %d | par = %d | dis = %d\n", 4, dsu.par[4].first, dsu.par[4].second);
    dsu.merge(1, 3);
    printf("node = %d | par = %d | dis = %d\n", 3, dsu.par[3].first, dsu.par[3].second);
    printf("node = %d | par = %d | dis = %d\n", 4, dsu.par[4].first, dsu.par[4].second);
    
    dsu.root(4);
    printf("node = %d | par = %d | dis = %d\n", 3, dsu.par[3].first, dsu.par[3].second);
    printf("node = %d | par = %d | dis = %d\n", 4, dsu.par[4].first, dsu.par[4].second);
}

/** This is the end of my solution **/
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
}
