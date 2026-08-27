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

const int MaxN = 2e5;
const int LOG = 18;
int LOG2[MaxN + 1];
int a[MaxN + 1], pre[MaxN + 1];
int dp[MaxN + 1][LOG + 1];
unordered_map<int, vector<int>> idx;

int n, q, x;

inline void prepare() {
    LOG2[1] = 0;
    FOR(i, 2, MaxN) LOG2[i] = LOG2[i / 2] + 1;
}

inline void process() {
    // preprocess
    FOR(i, 0, MaxN) fill(dp[i], dp[i] + LOG + 1, POSINF);
    FOR(i, 0, n - 1) {
        if ((int)idx[pre[i]].size() > 1) {
            int j = upper_bound(all(idx[pre[i]]), i) - idx[pre[i]].begin();
            if (j < (int)idx[pre[i]].size()) {
                dp[i + 1][0] = idx[pre[i]][j];
            }
        }
    }

    FORD(i, n - 1, 1) minimize(dp[i][0], dp[i + 1][0]);

    // RMQ
    FOR(j, 1, LOG2[n]) {
        FOR(i, 1, n - (1 << j) + 1) if(dp[i][j - 1] != POSINF) {
            dp[i][j] = dp[dp[i][j - 1] + 1][j - 1];
        }
    }
}


inline void query () {
    while(q--) {
        int L, R; cin >> L >> R;
        int num = 0;
        FORD(j, LOG2[n], 0) {
            if (dp[L][j] <= R) {
                L = dp[L][j] + 1;
                num += (1 << j);
            }
            if (L > R) break;
        }
        cout << num << '\n';
    }
}

inline void solve() {
    cin >> n >> q >> x;
    idx[0].push_back(0);
    FOR(i, 1, n) {
        cin >> a[i];
        a[i] = a[i] - x;
        pre[i] = pre[i - 1] + a[i];
        idx[pre[i]].push_back(i);
    }

    process();
    query();
}

/** This is the end of my solution **/

signed main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    prepare();
    solve();
}