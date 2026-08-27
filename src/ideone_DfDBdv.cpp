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

const int posinf = 1e9+1;
const int neginf = -1e9+1;
const int mod = 1000000007;
const double pi = 3.14159265359;

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

/** This is the end of my template **/

const int MaxN = 20;
int dp[MaxN + 1][1 << MaxN | 1];
int cost[MaxN << 1 | 1][MaxN << 1 | 1];

// dp[i][j] means choosing position i as end such that i + N <= 2*N
// to achieve the state j

void floyd(int N) {
    FOR(k, 0, N << 1) {
        FOR(i, 0, N << 1) {
            FOR(j, 0, N << 1) {
                minimize(cost[i][j], cost[i][k] + cost[k][j]);
            }
        }
    }
}

void solve() {
    int N; cin >> N;
    FOR(i, 0, N << 1) FOR(j, 0, N << 1) cin >> cost[i][j];
    floyd(N);

    int total_state = mask(N << 1) - 1;
    memset(dp, posinf, sizeof(dp));
    FOR(pos, 1, N) dp[pos][mask(pos - 1)] = cost[0][pos];

    FOR(state, 1, total_state) {
        for(int hihi = state; hihi >= 1; hihi ^= hihi & -hihi) {
            int pos = __builtin_ctz(hihi) + 1;
            if ((pos <= N && !bit(state, pos + N - 1)) || (pos > N && bit(state, pos - N - 1)))  {
                int old_state = state ^ (mask(pos - 1));
                for(int haha = old_state; haha >= 1; haha ^= haha & -haha) {
                    int old_pos = __builtin_ctz(haha) + 1;                    
                    if (old_pos > N && bit(old_state, old_pos - N - 1)) {
                        minimize(dp[pos][state], dp[old_pos][old_state] + cost[old_pos][pos]);
                    }
                    else if (old_pos <= N && !bit(old_state, old_pos + N - 1)) {
                        minimize(dp[pos][state], dp[old_pos][old_state] + cost[old_pos][pos]);
                    }
                }
            }
        }
    }

    int ans = posinf;
    FOR(pos, N + 1, N << 1) minimize(ans, dp[pos][total_state] + cost[pos][0]);
    printf("%lld\n", ans);
}

/** This is the end of my solution **/

#undef int
int main() {
    init();
    solve();
}