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
const int MOD = 1000000007;
const double PI = 3.14159265359;

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

/** This is the end of my template **/
#define data pair<ll, pair<int,int>>

const int N = 1500;
const int M = 17;

int d[N + 1][N + 1];
int f[M + 1];
int dp[M + 1][M + 1][1 << M];

inline void precompute(int m) {
    memset(dp, 0x3f, sizeof(dp));

    FOR(start, 1, m) {
        dp[start][start][1 << (start - 1)] = 0;
        FOR(mask, 1, (1 << m) - 1) {
            if (!(mask & (1 << (start - 1)))) continue;
            for(int hihi = mask; hihi >= 1; hihi ^= hihi & -hihi) {
                int i = __builtin_ctz(hihi) + 1;
                FOR(j, 1, m) {
                    int new_mask = mask | (1 << (j - 1));
                    minimize(dp[start][j][new_mask], dp[start][i][mask] + d[f[i]][f[j]]);
                }
            }
        }
    }
}

inline void solve() {
    int n, m, q; cin >> n >> m >> q;
    FOR(i, 1, m) cin >> f[i];
    FOR(i, 1, n) FOR(j, 1, n) cin >> d[i][j];
    precompute(m);

    int u, v;
    while(q--) {
        cin >> u >> v;
        int ans = POSINF;
        FOR(start, 1, m) FOR(end, 1, m) minimize(ans, d[u][f[start]] + dp[start][end][(1 << m) - 1] + d[f[end]][v]);
        cout << ans << ' ';     
    }
}

/** This is the end of my solution **/
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
}
