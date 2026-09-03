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

const int MaxN = 9e3;
const int W = 10;
int dp[MaxN + 1][1 << W | 1];
int A[MaxN + 1][11];

void solve() {
    int total_state = mask(W) - 1;
    int N; cin >> N;

    // input
    FOR(i, 1, N) {
        cin >> A[i][1] >> A[i][2]
            >> A[i][3] >> A[i][4]
            >> A[i][5] >> A[i][6]
            >> A[i][7] >> A[i][8]
            >> A[i][9] >> A[i][10];
    }

    // precompute valid states
    vector<int> valid_states;
    for (int state = 0; state < (1 << W); ++state) {
        if ((state & (state << 1)) == 0)
            valid_states.push_back(state);
    }

    // precompute compatible states
    unordered_map<int, vector<int>> compatible;
    for (int s1 : valid_states) {
        for (int s2 : valid_states) {
            if ((s1 & s2) == 0)
                compatible[s1].push_back(s2);
        }
    }

    // dp bitmask
    FOR(i, 1, N) FOR(state, 0, total_state) dp[i][state] = neginf;
    FOR(i, 1, N) {
        for (int state : valid_states) {
            // get the all bit 1 value
            int value = 0;
            for(int hihi = state; hihi >= 1; hihi ^= hihi & -hihi) {
                int j = __builtin_ctz(hihi) + 1;
                value += A[i][j];
            }

            // loop through all valid old states
            for (int old_state : compatible[state]) {
                dp[i][state] = max(dp[i][state], dp[i - 1][old_state] + value);
            }
        }
    }

    int ans = neginf;
    for (int s : valid_states) maximize(ans, dp[N][s]);
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