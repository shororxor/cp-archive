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

int n, m;
int dp[11][1001][1 << 10];

inline void solve() {
    cin >> n >> m;

    dp[0][0][0] = 1;
    for(int j = 0; j <= m - 1; j++) {
        for(int i = 0; i <= n - 1; i++) {
            for(int state = 0; state < (1 << n); state++) {
                if (!(state & (1 << i))) {
                    dp[i + 1][j][state ^ (1 << i)] += dp[i][j][state] % MOD;
                    if (i <= n - 2 && !(state & (1 << (i + 1)))) {
                        dp[i + 1][j][state ^ (1 << (i + 1))] += dp[i][j][state] % MOD;
                    }
                }
                else {
                    dp[i + 1][j][state ^ (1 << i)] += dp[i][j][state] % MOD;
                }
            }
            if (i == n - 1) {
                for (int mask = 0; mask < (1 << n); mask++) {
                    dp[0][j + 1][mask] = dp[n][j][mask];
                }
            }
        }
    }
    cout << dp[0][m][0];
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