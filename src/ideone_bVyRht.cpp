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
pair<int,int> segments[MAX + 1];

int N, K;

inline int search(int pos) {
    int L = 1;
    int R = K;

    while(L <= R) {
        int M = (L + R) >> 1;
        if (segments[M].first <= pos) {
            L = M + 1;
        }   
        else R = M - 1;
    }
    return L - 1;
}

inline void prepare() {
    LOG2[1] = 0;
    FOR(i, 2, MAX) LOG2[i] = LOG2[i / 2] + 1;
}

inline void solve() {
    cin >> N >> K;
    FOR(k, 1, K) {
        cin >> segments[k].first >> segments[k].second;
        if (segments[k].second < segments[k].first) segments[k].second += N;
    }

    // preprocess
    sort(segments + 1, segments + K + 1);
    FOR(i, 1, K) prefix[i] = max(prefix[i - 1], segments[i].second);

    // binary lifting
    FOR(i, 1, 2*N) {
        int max_reach = prefix[search(i)];
        dp[i][0] = max_reach < i ? -1 : max_reach;
    }

    FOR(j, 1, MAXLOG) {
        FOR(i, 1, 2 * N) {
            if (dp[i][j - 1] == -1) dp[i][j] = -1;
            else dp[i][j] = dp[dp[i][j - 1] + 1][j - 1];
        }
    }

    // query
    int ans = POSINF;
    FOR(i, 1, 2*N) {
        int sta = i;
        int fin = i + N - 1;
        int num = 0;
        FORD(j, MAXLOG, 0) {
            if (dp[sta][j] == -1) continue;
            if (dp[sta][j] < fin) {
                sta = dp[sta][j] + 1;
                num += (1 << j);
            }
        }
        if (dp[sta][0] >= fin) minimize(ans, num + 1);
    }
    if (ans == POSINF) cout << "impossible";
    else cout << ans << '\n';
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