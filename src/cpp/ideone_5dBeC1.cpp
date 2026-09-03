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

const int MAX = 101;

int cap[MAX][MAX];
int flow[MAX][MAX];
int par[MAX];
vector<int> graph[MAX];


inline int bfs(int s, int t) {
    memset(par, -1, sizeof(par));
    par[s] = -2;
    queue<pair<int,int>> q;
    q.push({s, POSINF});

    while(!q.empty()) {
        int u = q.front().first;
        int f = q.front().second;
        q.pop();

        for(int& v : graph[u]) {
            if (par[v] == -1 && cap[u][v] > flow[u][v]) {
                par[v] = u;
                f = min(f, cap[u][v] - flow[u][v]);
                if (v == t) return f;
                q.push({v, f});
            }
        }
    }
    return 0;
}

inline int edmondsKarp(int s, int t) {
    int sumflow = 0;
    int curflow = 0;

    while((curflow = bfs(s, t)) != 0) {
        sumflow += curflow;
        int p, u = t;
        while(u != s) {
            p = par[u];
            flow[p][u] += curflow;
            flow[u][p] -= curflow;
            u = p;
        }
    }

    return sumflow;
}

inline void solve() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(v);
        graph[v].push_back(u);
        cap[u][v] = w;
    }

    cout << edmondsKarp(s, t) << '\n';
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