#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

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

const int POSINF = 1e18;
const int NEFINF = -1e18;
const int MOD = 1000000007;
const double PI = 3.14159265359;

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

/** This is the end of my template **/

const int MaxN = 1e5;
int dp[MaxN + 2][1 << 6];
int a[MaxN + 1];
int s[7];

inline void solve() {
    int N, M, P, C;
    cin >> N >> M >> P >> C;

    FOR(i, 1, N) cin >> a[i];
    FOR(i, 1, M) cin >> s[i];
    sort(a + 1, a + N + 1); // greedy

    // base case    
    FOR(i, 0, N + 1) fill(dp[i], dp[i] + (1 << 6), NEFINF);
    dp[N + 1][(1 << M) - 1] = 0;

    FORD(i, N, 1) {
        FOR(mask, 0, (1 << M) - 1) {
            dp[i][mask] = dp[i + 1][mask];
            FOR(j, 1, M) {
                if (i + s[j] > N + 1) continue;
                int profit = P - (a[i + s[j] - 1] - a[i]) * (a[i + s[j] - 1] - a[i]) * C;
                maximize(dp[i][mask], dp[i + s[j]][mask | mask(j - 1)] + profit);
            }
        }
    }

    cout << dp[1][0] << '\n';
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