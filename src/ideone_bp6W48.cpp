#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

#define ll long long
// #define int ll
#define mask(i) (1 << (i))
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

const int MaxN = 2000;
int a[MaxN + 1];
int dp[MaxN + 2][1 << 11];
bool ok[1 << 11];

inline bool check(int x) {
    if (x & (1 << 1) || x & (1 << 8) || x & (1 << 9)) return false;
    return true;
}

inline void solve() {
    int n; cin >> n;
    FOR(i, 1, n) cin >> a[i];
    sort(a + 1, a + n + 1);
    FOR(mask, 0, (1 << 11) - 1) ok[mask] = check(mask);

    memset(dp, 0, sizeof(dp));
    FOR(i, 0, n - 1) {
        FOR(mask, 0, (1 << 11) - 1) {
            if (ok[mask]) {
                maximize(dp[i + 1][mask], dp[i][mask]);

                int new_mask = mask;
                int d = a[i + 1] - a[i];
                for (int hihi = mask; hihi >= 1; hihi ^= hihi & -hihi) {
                    int j = __builtin_ctz(hihi);
                    new_mask |= (1 << min(10, d + j));
                }
                
                if(ok[new_mask]) maximize(dp[i + 1][new_mask], dp[i][mask] + 1);
            }
        }
    }

    int ans = 0;
    FOR(mask, 0, (1 << 11) - 1) if (ok[mask]) maximize(ans, dp[n][mask]);
    cout << n - ans << '\n';
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