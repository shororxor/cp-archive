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

const int MaxN = 100;
vector<pair<int,int>> edges[MaxN + 1];
bool visited[MaxN + 1];
int dist[MaxN + 1];

inline bool prim(int n) {
    int start = 0, cnt = 0;
    dist[start] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({dist[start], start});

    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // choose to go this path
        if (!visited[u]) {
            visited[u] = true;
            cnt++;
            
            for (auto[v, w] : edges[u]) {
                if (!visited[v] && dist[v] > w) {
                    dist[v] = w;
                    pq.push({w, v});
                }
            }
        }
    }

    return cnt == n;
}

inline void solve() {
    int n, m; cin >> n >> m;
    FOR(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back({v, w});
        edges[v].push_back({u, w});
    }

    fill(visited, visited + n, false);
    fill(dist, dist + n, POSINF);

    if (prim(n)) {
        int ans = 0;
        FOR(i, 0, n - 1) ans += dist[i];
        cout << ans << '\n';
    }
    else cout << "Graph is not connected\n";
}

/** This is the end of my solution **/
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
}

