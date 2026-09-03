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
const int MaxLog = 16;

int LOG2[MaxN + 1];
int a[MaxN + 1];
int dp[MaxN + 1][MaxLog + 1];

void prepare() {
    LOG2[1] = 0;
    FOR(i, 2, MaxN) LOG2[i] = LOG2[i / 2] + 1;
}

int querySum(int L, int R) {
    int sum = 0;
    while(L <= R) {
        int k = LOG2[R - L + 1];
        sum += dp[L][k];
        L += (1 << k);
    }
    return sum;
}

int bruteforce(int R, int num_segments, int M) {
    int cur_segments = 0;
    int L = 0;
    int lb = 1;
    int rb = R;
    int len = 0;

    while(cur_segments < num_segments) {
        while(lb <= rb) {
            int mb = (lb + rb) >> 1;
            if (querySum(R - mb + 1, R) <= M) {
                lb = mb + 1;
                len = mb;
            }
            else rb = mb - 1;
        }
        cur_segments++;
        L = R - len + 1;
        R = L - 1;
        lb = 1;
        rb = R;
        len = 0;
    }

    return L;
}

void solve() {
    int N, Q, M;
    cin >> N >> Q >> M;
    FOR(i, 1, N) {
        cin >> a[i];
        dp[i][0] = a[i];
    }

    // process
    FOR(j, 1, LOG2[N]) {
        FOR(i, 1, N) {
            dp[i][j] = dp[i][j - 1] + dp[i + (1 << (j - 1))][j - 1];
        }
    }

    // query
    while(Q--) {
        int u, v;
        cin >> u >> v;
        printf("%lld\n", bruteforce(u, v, M));
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