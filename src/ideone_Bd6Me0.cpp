#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

#define ll long long
#define int ll
#define mask(i) (1LL << (i))
#define bit(x, i)  (((x) >> (i)) & 1)
#define onbit(x, i) ((x) = (x) | mask(i))
#define offbit(x, i) ((x) = (x) & (~mask(i)))
#define pcount(i) __builtin_popcount(i)
#define bctz(i) __builtin_ctz(i)
#define all(v) v.begin(), v.end()
#define all1(v) v.begin()+1, v.end()
#define sz(v) (int)v.size();
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

const int posinf = 1e9;
const int neginf = -1e9;
const int mod = 1000000007;
const double pi = 3.14159265359;

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

/** This is the end of my template **/

struct Euler {
    int n, m = 0;
    vector<vector<int>> tree;
    vector<int> start, end;
 
    Euler(int n_) : n(n_) {
        tree.assign(n + 1, vector<int>());
        start.assign(n + 1, 0);
        end.assign(n + 1, 0);
    }
 
    inline void dfs(int u, int p) {
        m++;
        start[u] = m;
        for(int& v : tree[u]) {
            if (v != p) {
                dfs(v, u);
            }
        }
        end[u] = m;
    }
 
    inline void debug() {
        FOR(u, 1, n) 
        printf("%lld | start = %lld| end = %lld\n", u, start[u], end[u]);
    }
};

struct BIT {
    int n;
    vector<int> tree;
 
    BIT(int n_) : n(n_), tree(n + 1, 0) {}
 
    void update(int id, int x) {
        while(id <= n) {
            tree[id] += x;
            id += id & (-id);
        }
    }
 
    int query(int id) {
        int ans = 0;
        while(id >= 1) {
            ans += tree[id];
            id -= id & (-id);
        }
        return ans;
    }
};

const int MaxN = 2e5;
int value[MaxN + 1];

void solve() {
    int N, Q; cin >> N >> Q;
    FOR(i, 1, N) cin >> value[i];

    // build euler tree
    Euler euler(N);
    FOR(i, 1, N - 1) {
        int u, v; cin >> u >> v;
        euler.tree[u].push_back(v);
        euler.tree[v].push_back(u);
    }

    euler.dfs(1, 0);
 
    // process
    BIT fenwick(euler.m);
    FOR(u, 1, N) fenwick.update(euler.start[u], value[u]);


    // query
    int operation;
    while(Q--) {
        cin >> operation;
        if (operation == 1) {
            int u, x; cin >> u >> x;
            fenwick.update(euler.start[u], x - value[u]);
            value[u] = x;
        }
        else if (operation == 2) {
            int u; cin >> u;
            int ans = fenwick.query(euler.end[u]) - fenwick.query(euler.start[u] - 1);
            printf("%lld\n", ans);
        }
    }
}

/** This is the end of my solution **/

#undef int
int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
}