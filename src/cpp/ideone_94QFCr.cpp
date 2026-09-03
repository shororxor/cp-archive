#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

void init() {
    #ifndef ONLINE_JUDGE
    if (!freopen("input.inp", "r", stdin)) {}
    if (!freopen("output.out", "w", stdout)) {}
    #endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

#define ll long long
#define int ll
#define mask(i) (1LL << (i))
#define bit(x, i)  (((x) >> (i)) & 1)
#define onbit(x, i) ((x) = (x) | mask(i))
#define offbit(x, i) ((x) = (x) & (~mask(i)))
#define pcount(i) __builtin_popcountll(i)
#define bctz(i) __builtin_ctz(i)
#define all(v) v.begin(), v.end()
#define all1(v) v.begin()+1, v.end()
#define sqr(x) ((x) * (x))
#define pii pair<int, int>
#define piii pair<pii, int>
#define FOR(i,l,r) for(auto i=(l);i<=(r);i++)
#define REP(i,l,r) for(auto i=(l);i<(r);i++)
#define FORD(i,l,r) for(auto i=(l);i>=(r);i--)
#define REPD(i,l,r) for(auto i=(l);i>(r);i--)
#define complex complex<long double>

const int neginf = INT_MIN;
const int posinf = 1e9+1;
const int mod = 1000000007;
const double pi = 3.14159265359;

template <class T> bool minimize(T &x,T y) {
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y) {
    if (x<y) x=y; else return 0; return 1;
}
 
/** This is the end of my template **/

struct Euler {
    int n, m = 0;
    vector<vector<int>> tree;
    vector<int> start, end, tour;

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
        FOR(u, 1, n) printf("%d | start = %lld| end = %lld\n", u, start[u], end[u]);
        FOR(t, 1, m) cout << tour[t] << (t == m ? '\n' : ' ');
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

void solve() {
    int n; cin >> n;
    Euler euler(n);

    // build euler tree
    FOR(u, 2, n) {
        int p; cin >> p;
        euler.tree[u].push_back(p);
        euler.tree[p].push_back(u);
    }

    euler.dfs(1, 0);

    // build BIT to count subtree
    BIT fenwick(euler.m);
    FOR(u, 1, n) fenwick.update(euler.start[u], 1);

    FOR(u, 1, n) {
        int ans = fenwick.query(euler.end[u]) - fenwick.query(euler.start[u] - 1);
        printf("%lld ", ans - 1);
    }
}

/** This is the end of my solution **/

#undef int
int main() {
    init();
    solve();
}