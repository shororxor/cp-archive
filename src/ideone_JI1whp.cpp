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

const int MaxN = 100000;
int color[MaxN + 1];
int dp[MaxN + 1][1 << 5];
vector<int> edges[MaxN + 1]; 

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    FOR(i, 1, n) cin >> color[i];
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    FOR(u, 1, n) dp[u][mask(color[u] - 1)] = 1;

    int sum = 0;
    FOR(state, 0, (1 << k) - 1) {
        if (__builtin_popcount(state) == 1) continue;
        FOR(u, 1, n) {
            if (!bit(state, color[u] - 1)) continue;
            int old_state = state ^ mask(color[u] - 1);
            for(int& v : edges[u]) if (bit(old_state, color[v] - 1)) {
                dp[u][state] += dp[v][old_state];
            }
            sum += dp[u][state];
        }
    }

    cout << sum << '\n';
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