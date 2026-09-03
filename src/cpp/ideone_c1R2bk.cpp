#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;
 
void init() {
    #ifndef ONLINE_JUDGE
    if (!freopen("input.inp", "r", stdin)) {}
    if (!freopen("output.out", "w", stdout)) {}
    #endif
 
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
 
#define ll long long
#define int ll
#define mask(i) (1LL << (i))
#define bit(x, i)  (((x) >> (i)) & 1)
#define onbit(x, i) ((x) = (x) | mask(i))
#define offbit(x, i) ((x) = (x) & (~mask(i)))
#define pcount(i) __builtin_popcountll(i)
#define bctz(i) __builtin_ctz(i)
#define all(v) v.begin(), v.end()
#define all1(v) v.begin()+1, v.end()
#define sqr(x) ((x) * (x))
#define FOR(i,l,r) for(int i=(l);i<=(r);i++)
#define REP(i,l,r) for(int i=(l);i<(r);i++)
#define FORD(i,l,r) for(int i=(l);i>=(r);i--)
#define REPD(i,l,r) for(int i=(l);i>(r);i--)
#define complex complex<long double>
#define pii pair<int, int>
#define piii pair<pii, int>
#define vi vector<int>
#define vii vector<vi>
#define viii vector<vii>

const int neginf = -1e9-1;
const int posinf = 1e9+1;;
const int mod = 1000000007;
const double pi = 3.14159265359;
 
template <class T> bool minimize(T &x,T y) {
    if (x>y) x=y; else return 0; return 1;
}
 
template <class T> bool maximize(T &x,T y) {
    if (x<y) x=y; else return 0; return 1;
}
 
/** This is the end of my template **/

vector<int> digits;
const int MaxN = 3e6;
int dp[7][2][MaxN][5];
bool isPrime[MaxN + 1];

void sieve() {
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;

    for(int i=2; i*i <= MaxN; i++) {
        if (!isPrime[i]) continue;
        for(int j=i*i; j <= MaxN; j += i) {
            isPrime[j] = false;
        }
    }
}

int recursion(int step, int smaller, int num, int sum) {
    if (step + 1 == (int)digits.size()) {
        if (isPrime[num] && sum == 0) return 1;
        else return 0;
    }

    if (dp[step][smaller][num][sum] != -1) 
        return dp[step][smaller][num][sum];

    int limit = smaller ? 9 : digits[step + 1];
    int res = 0;

    FOR(d, 0, limit) {
        int new_step = step + 1;
        int new_smaller = smaller || (d < limit);
        int new_sum = (sum + d) % 5;
        res += recursion(new_step, new_smaller, num*10+d, new_sum);
    }

    return dp[step][smaller][num][sum] = res;
}

int F(int N) {
    digits.clear();
    digits.push_back(0);
    while(N > 0) {
        digits.push_back(N % 10);
        N /= 10;
    }
    reverse(all1(digits));
    memset(dp, -1, sizeof(dp));
    return recursion(0, 0, 0, 0);
}

void solve() {
    int L, R; cin >> L >> R;
    printf("%lld\n", F(R) - F(L-1));
}

/** This is the end of my solution **/
 
#undef int
int main(void) {
    init();
    sieve();
    solve();
    return 0;
}