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

int N, K;
vector<int> digits;
int dp[31][2][31][31];

int R(int step, int smaller, int num, int ldzero) {
    if (step + 1 == (int)digits.size()) {
        if (num == K) return 1;
        else return 0;
    }

    if (dp[step][smaller][num][ldzero] != -1)
        return dp[step][smaller][num][ldzero];

    int res = 0;
    int limit = smaller ? 1 : digits[step + 1];

    FOR(d, 0, limit) {
        int new_smaller = smaller || (d < limit);
        if (d == 0 && ldzero + 1 == step + 1) res += R(step + 1, new_smaller, num, ldzero + 1);
        else res += R(step + 1, new_smaller, num + (d == 0), ldzero);
    }

    return dp[step][smaller][num][ldzero] = res;
}

vector<int> getBinary(int N) {
    vector<int> ans = {0};
    while(N > 0) {
        ans.push_back(N % 2);
        N /= 2;
    }
    reverse(all1(ans));
    return ans;
}

int F(int N) {
    if (N <= 0) return 0;
    digits = getBinary(N);
    memset(dp, -1, sizeof(dp));
    return R(0, 0, 0, 0);
}

void solve() {
    while(cin >> N >> K) {
        printf("%lld\n", F(N) + (K == 1 ? 1 : 0));
    }
}

/** This is the end of my solution **/

#undef int
int main() {
    init();
    solve();
}
