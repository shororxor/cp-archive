#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

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

const int posinf = 1e9;
const int neginf = -1e9;
const int mod = 1000000007;
const double pi = 3.14159265359;

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

/** This is the end of my template **/

const int MaxN = 1e4;
int dp[MaxN + 1][1 << 4 | 1];
int cost[MaxN + 1][5];

bool check(int state) {
    if (state == 3  || state == 6  || state == 7  || state == 11 || 
        state == 12 || state == 13 || state == 14 || state == 15) return false;
    return true;
}

void solve() {
    int total_state = mask(4) - 1;
    int N; cin >> N;

    FOR(i, 1, N) {
        cin >> cost[i][1] >> cost[i][2]
            >> cost[i][3] >> cost[i][4];
    }

    FOR(i, 1, N) FOR(state, 0, total_state) dp[i][state] = neginf;

    FOR(i, 1, N) {
        FOR(state, 0, total_state) {
            // no two squares lying next to each other
            if (!check(state)) continue;

            // get the all bit 1 value
            int value = 0;
            for(int hihi = state; hihi >= 1; hihi ^= hihi & -hihi) {
                int j = __builtin_ctz(hihi) + 1;
                value += cost[i][j];
            }

            // get all state the not intersect
            FOR(old_state, 0, total_state) if (check(old_state) && (old_state & state) == 0){
                maximize(dp[i][state], dp[i - 1][old_state] + value);
            }
        }
    }

    int ans = neginf;
    FOR(state, 0, total_state) {
        if (!check(state)) continue;
        maximize(ans, dp[N][state]);
    }

    printf("%lld\n", (ans == 0 ? -1LL : ans));
}

/** This is the end of my solution **/

#undef int
int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
}