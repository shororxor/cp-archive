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
int dp[MaxN + 1][1 << 10 | 1];
int A[MaxN + 1][11];
int check[1 << 10 | 1];

bool OK(int state) {
    FOR(i, 2, 10) if (bit(state, i - 1) && bit(state, i - 2)) return false;
    return true;
}

void solve() {
    int total_state = mask(10) - 1;
    int N; cin >> N;

    // precompute valid states    
    FOR(state, 1, total_state) check[state] = OK(state);
    FOR(i, 1, N) {
        cin >> A[i][1] >> A[i][2]
            >> A[i][3] >> A[i][4]
            >> A[i][5] >> A[i][6]
            >> A[i][7] >> A[i][8]
            >> A[i][9] >> A[i][10];
    }

    FOR(i, 1, N) FOR(state, 0, total_state) dp[i][state] = neginf;

    FOR(i, 1, N) {
        FOR(state, 0, total_state) {
            // no two squares lying next to each other
            if (!check[state]) continue;

            // get the all bit 1 value
            int value = 0;
            for(int hihi = state; hihi >= 1; hihi ^= hihi & -hihi) {
                int j = __builtin_ctz(hihi) + 1;
                value += A[i][j];
            }

            // get the subset of all bit 0 = reverse + duyet subset
            int reverse_state = (~state) & ((1 << 10) - 1);

            // dp sos
            for(int subset = reverse_state; subset > 0; subset = (subset - 1) & reverse_state) {
                if (!check[subset] || dp[i - 1][subset] <= neginf) continue;
                maximize(dp[i][state], dp[i - 1][subset] + value);
            }

            maximize(dp[i][state], dp[i - 1][0] + value);
        }
    }

    int ans = neginf;
    FOR(state, 0, total_state) {
        if (!check[state]) continue;
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