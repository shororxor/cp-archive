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

const int MaxN = 1e4;
const int MaxK = 8;
int h[MaxN + 1], c[MaxN + 1];
int dp[MaxN][1 << MaxK];

inline void solve() {
    int n, k; cin >> n >> k;
    FOR(i, 1, n) cin >> c[i] >> h[i];

    memset(dp, 0, sizeof(dp));
    FOR(i, 1, n) dp[i][1 << (c[i] - 1)] = 1;

    FOR(i, 1, n) {
        FOR(mask, 0, (1 << k) - 1) {
            if (mask & (1 << (c[i] - 1))) {
                FOR(j, i + 1, n) {
                    if (h[j] < h[i]) continue;
                    int new_mask = mask | (1 << (c[j] - 1));
                    dp[j][new_mask] = (dp[j][new_mask] + dp[i][mask]) % MOD;
                }
            }
        }
    }

    int ans = 0;
    FOR(i, 1, n) ans = (ans + dp[i][(1 << k) - 1]) % MOD;
    printf("%d", ans);
}

/** This is the end of my solution **/

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
}
