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
#define FOR(i,l,r) for(auto i=(l);i<=(r);i++)
#define REP(i,l,r) for(auto i=(l);i<(r);i++)
#define FORD(i,l,r) for(auto i=(l);i>=(r);i--)
#define REPD(i,l,r) for(auto i=(l);i>(r);i--)
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

int K, D;
string digits;
int dp[10001][2][101];

int recursion(int step, int smaller, int sum) {
    if (step + 1 == (int)digits.size()) {
        if (sum % D == 0) return 1;
        else return 0;
    }

    if (dp[step][smaller][sum] != -1) 
        return dp[step][smaller][sum];

    int res = 0;
    int limit = smaller ? 9 : (int)(digits[step + 1] - '0');

    FOR(d, 0, limit) {
        res += recursion(step + 1, smaller || (d < limit), (sum + d) % D);
        res %= mod;
    }

    return dp[step][smaller][sum] = res;
}

int F(string& N) {
    digits = '0' + N;
    memset(dp, -1, sizeof(dp));
    return recursion(0, 0, 0);
}

void solve() {
    string K; cin >> K;
    cin >> D;
    printf("%lld\n", (F(K) - 1) % mod);
}

/** This is the end of my solution **/

#undef int
int main() {
    init();
    solve();
}
