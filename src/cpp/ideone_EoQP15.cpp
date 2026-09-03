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

int dp[51][51][1 << 4];

void solve() {
    int n, m, k; cin >> n >> m >> k;

    dp[n + 1][1][0] = 1;
    FORD(i, n, 1) {
        FORD(j, m, 1) {
            FORD(state, (1 << 4) - 1, 0) {
                dp[i][j][state] = 0;
                FOR(c, 0, 3) {
                    if (j < m) {
                        dp[i][j][state] = (dp[i][j][state] + dp[i][j + 1][state | (1 << c)]) % mod;
                    }
                    else if (j == m && __builtin_popcount(state | (1 << c)) >= k) {
                        dp[i][j][state] = (dp[i][j][state] + dp[i + 1][1][0]) % mod;
                    }
                }
            }
        }
    }

    cout << dp[1][1][0] << '\n';
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