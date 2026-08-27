#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

#define ll long long
#define int ll
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
#define ite std::vector<int>::iterator

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

const int MAX = 1e5 + 5;

int par[MAX];
int dep[MAX];
int sub[MAX];

int pos[MAX];
int ord[MAX];
int top[MAX];

int val[MAX];

int cnt;
vector<int> edge[MAX];

struct HLD {
    void dfs(int u, int p) {
        sub[u] = 1;
        auto it = find(edge[u].begin(), edge[u].end(), p);
        if (it != edge[u].end()) edge[u].erase(it);

        for(int& v : edge[u]) {
            par[v] = u;
            dep[v] = dep[u] + 1;
            dfs(v, u);
            sub[u] = sub[u] + sub[v];
            if (sub[v] > sub[edge[u][0]]) swap(v, edge[u][0]);
        }
    }

    void euler(int u) {
        pos[u] = ++cnt;
        ord[cnt] = u;
        for(int& v : edge[u]) {
            top[v] = (v == edge[u][0]) ? top[u] : v;
            euler(v);
        }
    }

    static int lca(int u, int v) {
        while(top[u] != top[v]) {
            if (pos[top[u]] > pos[top[v]]) u = par[top[u]];
            else v = par[top[v]];
        }
        if (dep[u] < dep[v]) return u;
        else return v;
    }

    void run(int root) {
        cnt = 0;
        top[root] = root;
        dfs(root, 0);
        euler(root);
    }
};

struct SegTree {
    int n;
    vector<int> node;

    SegTree(int n_) : n(n_) {
        node.assign(4 * n + 1, 0);
    }

    void build(int i, int l, int r) {
        if (l == r) {
            node[i] = val[ord[l]];
            return;
        }

        int m = (l + r) >> 1;
        build(i << 1, l, m);
        build(i << 1 | 1, m + 1, r);
        node[i] = node[i << 1] ^ node[i << 1 | 1];
    }

    void update(int i, int l, int r, int u, int v, int c) {
        if (r < u || l > v || l > r || u > v) return;
        if (u <= l && r <= v) {
            node[i] = c;
            return;
        }

        int m = (l + r) >> 1;
        update(i << 1, l, m, u, v, c);
        update(i << 1 | 1, m + 1, r, u, v, c);
        node[i] = node[i << 1] ^ node[i << 1 | 1];
    }

    int get(int i, int l, int r, int u, int v) {
        if (r < u || l > v || l > r || u > v) return 0;
        if (u <= l && r <= v) return node[i];

        int m = (l + r) >> 1;
        int L = get(i << 1, l, m, u, v);
        int R = get(i << 1 | 1, m + 1, r, u, v);
        return L ^ R;
    }

    int query(int u, int v) {
        int lca = HLD::lca(u, v);
        int ans = 0;
        while(top[u] != top[lca]) {
            ans ^= get(1, 1, n, pos[top[u]], pos[u]);
            u = par[top[u]];
        }

        while(top[v] != top[lca]) {
            ans ^= get(1, 1, n, pos[top[v]], pos[v]);
            v = par[top[v]];
        }

        if (dep[u] < dep[v]) ans ^= get(1, 1,  n, pos[u], pos[v]);
        else ans ^= get(1, 1, n, pos[v], pos[u]);
        return ans;
    }
};

inline void solve() {
    int n, q; cin >> n >> q;
    FOR(i, 1, n) cin >> val[i];
    FOR(i, 1, n - 1) {
        int u, v; cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    HLD hld; hld.run(1);
    SegTree tree(n); tree.build(1, 1, n);

    while(q--) {
        int t, x, y; 
        cin >> t >> x >> y;
        if (t == 1) tree.update(1, 1, n, pos[x], pos[x], y);
        else printf("%lld\n", tree.query(x, y));
    }
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