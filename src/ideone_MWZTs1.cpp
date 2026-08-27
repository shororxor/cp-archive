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
    vector<int> par, rank, size;
    vector<int> sum, maxVal, minVal; // store additional info
   
    inline void init(int n) {
        par.assign(n + 1, 0);
        rank.assign(n + 1, 0);
        size.assign(n + 1, 0);
        sum.assign(n + 1, 0);
        minVal.assign(n + 1, 0);
        maxVal.assign(n + 1, 0);

        FOR(u, 1, n) {
            par[u] = u;
            rank[u] = 1;
            size[u] = 1;
            sum[u] = u;
            minVal[u] = u;
            maxVal[u] = u;
        }
    }

    inline int root(int u) {
        return par[u] = (u == par[u] ? u : root(par[u]));
    }

    inline bool mergeSize(int u, int v) {
        u = root(u);
        v = root(v);

        if (u == v) return false;
        if (size[u] < size[v]) swap(u, v);

        par[v] = u;
        size[u] += size[v];
        sum[u] += sum[v];
        minVal[u] = min(minVal[u], minVal[v]);
        maxVal[u] = max(maxVal[u], maxVal[v]);

        return true;
    }

    inline bool mergeRank(int u, int v) {
        u = root(u);
        v = root(v);
        
        if (u == v) return false;
        if (rank[u] < rank[v]) swap(u, v);

        par[v] = u;
        sum[u] += sum[v];
        minVal[u] = min(minVal[u], minVal[v]);
        maxVal[u] = max(maxVal[u], maxVal[v]);

        if (rank[u] == rank[v]) rank[u]++;
        return true;
    }

    inline bool same(int u, int v) {
        return root(u) == root(v);
    }

    inline int getSum(int u) {
        return sum[root(u)];
    }

    inline int getMax(int u) {
        return maxVal[root(u)];
    }

    inline int getMin(int u) {
        return minVal[root(u)];
    }
};

inline void solve() {
    DSU dsu;
    dsu.init(4);

    dsu.mergeRank(1, 2);
    dsu.mergeRank(3, 4);
    
    cout << dsu.same(2, 3) << '\n';
    dsu.mergeRank(2, 3);

    cout << dsu.root(2) << '\n';
    cout << dsu.root(3) << '\n';

    cout << dsu.getSum(3) << '\n';
    cout << dsu.getMin(2) << '\n';
    cout << dsu.getMax(4) << '\n';
}

/** This is the end of my solution **/
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
}
