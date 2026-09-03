#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

void init() {
    #ifndef ONLINE_JUDGE
    if (!freopen("input.inp", "r", stdin)) {}
    if (!freopen("output.out", "w", stdout)) {}
    #endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

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

const int inf = 1e18+1;
const int mod = 1000000007;
const double pi = 3.14159265359;

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

/** This is the end of my template **/

const int MaxN = 15;
int dp[MaxN + 1][1 << MaxN | 1];
// dp[i][j] is the number of ways for state j ending with element i

void solve() {
    int N, K; cin >> N >> K;
    memset(dp, 0, sizeof(dp));

    int total_state = (1 << N) - 1;
    FOR(pos, 1, N) dp[pos][mask(pos - 1)] = 1;

    FOR(state, 1, total_state) {
        FOR(pos, 1, N) if (bit(state, pos - 1)) {
            int L = max(1LL, pos - K);
            int R = min(pos + K, N);
            int old_state = state ^ mask(pos - 1);
            FOR(old_pos, 1, N) {
                if (bit(state, old_pos - 1) && L <= old_pos && old_pos <= R) {
                    dp[pos][state] += dp[old_pos][old_state];
                }
            }
        }
    }

    int ans = 0;
    FOR(pos, 1, N) ans += dp[pos][total_state];
    printf("%lld\n", ans);
}

/** This is the end of my solution **/

#undef int
int main() {
    init();
    int T; cin >> T;
    while(T--) solve();
}