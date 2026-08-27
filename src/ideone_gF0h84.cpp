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

const int MAX = 100;

int sta[MAX];
int fin[MAX];
int ord[MAX];
int top[MAX];
int sub[MAX];

int cnt;
vector<int> edge[MAX];

void dfs(int u, int p) {
    sub[u] = 1;
    auto it = find(edge[u].begin(), edge[u].end(), p);
    if (it != edge[u].end()) edge[u].erase(it);

    for(int& v : edge[u]) {
        dfs(v, u);
        sub[u] += sub[v];
        if (sub[v] > sub[edge[u][0]]) swap(v, edge[u][0]);
    }
}

void euler(int u) {
    sta[u] = ++cnt;
    ord[cnt] = u;

    for(int& v : edge[u]) {
        top[v] = (v == edge[u][0]) ? top[u] : v;
        euler(v);
    }

    fin[u] = cnt;
}

void hld(int root) {
    cnt = 0;
    dfs(root, -1);
    euler(root);
}

inline void solve() {
    int n; cin >> n;
    FOR(i, 1, n - 1) {
        int u, v; cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    hld(1);
    FOR(u, 1, n) 
    printf("u = %d | sta[%d] = %d | fin[%d] = %d\n", u, u, sta[u], u, fin[u]);
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