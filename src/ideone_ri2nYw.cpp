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

const int MaxN = 1e5;
const int MaxLog = 17;

int LOG2[MaxN + 1];
int a[MaxN + 1];
int pre[MaxN + 1];
int dp[MaxN + 1][MaxLog + 1];

void prepare() {
    LOG2[1] = 0;
    FOR(i, 2, MaxN) LOG2[i] = LOG2[i / 2] + 1;
}

int querySum(int L, int R) {
    return pre[R] - pre[L - 1];
}

int BS(int R, int M) {
    int lb = 1;
    int rb = R;
    int len = 0;

    while(lb <= rb) {
        int mb = (lb + rb) >> 1;
        if (querySum(R - mb + 1, R) <= M) {
            lb = mb + 1;
            len = mb;
        }
        else rb = mb - 1;
    }

    return R - len + 1;
}

void solve() {
    int N, Q, M;
    cin >> N >> Q >> M;
    FOR(i, 1, N) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
        dp[i][0] = BS(i, M);
    }

    // process
    FOR(j, 1, LOG2[N]) {
        FOR(i, 1 + (1 << j) - 1, N) {
            dp[i][j] = dp[dp[i][j-1]-1][j-1];
        }
    }

    // query
    int u, v;
    FOR(i, 1, Q) {
        cin >> u >> v;
        FORD(j, LOG2[N], 0) {
            if (v & (1 << j)) {
                u = dp[u][j] - 1;
                if (u <= 0) break;
            }
        }
        cout << max(1LL, u + 1) << '\n';
    }
}

/** This is the end of my solution **/
 
#undef int
int main(void) {
    init();
    prepare();
    solve();
    return 0;
}