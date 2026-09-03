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

struct Data {
    int type; int* ptr; int val;
    
    Data(int type = 0, int* ptr = nullptr, int val = 0) {
        this->type = type;
        this->ptr = ptr;
        this->val = val;
    }
};

struct DSU {
    vector<pair<int,int>> par;
    vector<int> size;
    vector<int> valid;
    stack<Data> history;

    inline void init(int n) {
        par.resize(n + 1);
        valid.resize(n + 1);
        size.resize(n + 1);
        FOR(u, 1, n) {
            size[u] = 1;
            par[u] = {u, 0};
            valid[u] = true;
        }
        while(!history.empty()) history.pop();
    }

    inline pair<int,int> root(int u) {
        if (u != par[u].first) {
            int color = root(par[u].first).second;
            par[u].second ^= color;
        }
        return par[u];
    }

    inline bool merge(int u, int v) {
        auto [pu, x] = root(u);
        auto [pv, y] = root(v);

        if (pu == pv && x == y) {
            if (size[u] < size[v]) swap(u, v);
            history.emplace(1, &par[v].first, par[v].first);
            history.emplace(1, &par[v].second, par[v].second);
            history.emplace(1, &size[u], size[u]);
            par[v] = {par[u].first, x ^ y ^ 1};
            size[u] += size[v]; 
            
            history.emplace(2, &valid[u], valid[u]);
            valid[u] = false;
            return false;
        }
        
        if (size[u] < size[v]) swap(u, v);
        history.emplace(1, &par[v].first, par[v].first);
        history.emplace(1, &par[v].second, par[v].second);
        history.emplace(1, &size[u], size[u]);
        par[v] = {par[u].first, x ^ y ^ 1};
        size[u] += size[v];

        int tmp = valid[u] & valid[v];
        if (valid[u] != tmp) {
            history.emplace(2, &valid[u], valid[u]);
            valid[u] = tmp;
        }
        return true;
    }

    inline void undo(int t) {
        FORD(i, t, 1) {
            if (history.empty()) return;

            Data d = history.top(); history.pop();
            int type = d.type;
            int* ptr = d.ptr;
            int val = d.val;

            if (type == 1) {
                *ptr = val;
                
                FORD(i, 2, 1) {
                    d = history.top(); history.pop();
                    type = d.type; ptr = d.ptr; val = d.val;
                }
            }
            else if (type == 2) {
                *ptr = val;
                
                FORD(i, 3, 1) {
                    d = history.top(); history.pop();
                    type = d.type; ptr = d.ptr; val = d.val;
                }
            }
        }
    }

    inline bool same(int u, int v) {
        return root(u).first == root(v).first;
    }
};

inline void solve() {
    int n, q; cin >> n >> q;
    DSU dsu; dsu.init(n);

    while(q--) {
        int u, v; cin >> u >> v;
        if (dsu.same(u, v)) {
            dsu.undo(1);
            if (dsu.valid[u]) printf("YES\n");
            else printf("NO\n");
        }
        else {
            dsu.merge(u, v);
            if (dsu.valid[u]) printf("YES\n");
            else printf("NO\n");
        }
    }
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