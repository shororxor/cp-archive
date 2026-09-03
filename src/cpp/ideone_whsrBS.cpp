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

const int MAX = 1e6;
const int MAXLOG = 18;

int prefix[2 * MAX + 1];
int dp[2* MAX + 1][MAXLOG + 1];
int LOG2[MAX + 1];
int last[2 * MAX];

int N, K;
pair<int,int> segments[MAX + 1];

inline void prepare() {
    LOG2[1] = 0;
    FOR(i, 2, MAX) LOG2[i] = LOG2[i / 2] + 1;
}

inline int compute(int sta, int fin) {
    int result = 0;
    for (int i = MAXLOG; i >= 0; i--) {
        if (dp[sta][i] < fin) {
            result += (1 << i);
            sta = dp[sta][i] + 1;
        }
    }
    return (dp[sta][0] >= fin) ? result + 1 : POSINF;

}

inline void solve() {
    cin >> N >> K;
    FOR(k, 1, K) {
        cin >> segments[k].first >> segments[k].second;
        if (segments[k].second < segments[k].first) segments[k].second += N;
    }

    // preprocess
    sort(segments + 1, segments + K + 1);
    FOR(i, 1, K) maximize(last[segments[i].first], segments[i].second);
    FOR(i, 1, 2*N) {
        maximize(last[i], last[i - 1]);
        dp[i][0] = last[i];
    }

    // binary lifting
    FOR(j, 1, MAXLOG) {
        FOR(i, 1, 2 * N) {
            dp[i][j] = dp[dp[i][j - 1] + 1][j - 1];
        }
    }

    // query
    int ans = POSINF;
    FOR(i, 1, 2*N) minimize(ans, compute(i, i + N - 1));
    if (ans == POSINF) cout << "impossible";
    else cout << ans;
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

    prepare();
    solve();
}