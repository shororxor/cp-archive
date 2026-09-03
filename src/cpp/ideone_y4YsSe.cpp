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

const int MaxN = 18;
int dp[1 << MaxN | 1];
int a[MaxN + 1], cnt[MaxN + 1], sum[MaxN + 1];
int cost[MaxN + 1][MaxN + 1];
vector<int> pos[MaxN + 1];

int getSum(int n) {
    return n * (n + 1) / 2;
}

void solve() {
    memset(cnt, 0, sizeof(cnt));
    memset(sum, 0, sizeof(sum));
    memset(cost, 0, sizeof(cost));
    FOR(i, 1, MaxN) pos[i].clear();

    int M, N; cin >> M >> N;
    int N_ = 0;
    FOR(i, 1, M) {
        cin >> a[i];
        cnt[a[i]] += 1; // save the number of element a[i]
        sum[a[i]] += i; // save the sum of position of element a[i]
        pos[a[i]].push_back(i);
        N_ = max(N_, a[i]);
    }
    N = N_ + 1;

    // preprocess cost
    FOR(i, 1, N) {
        FOR(j, 1, N) {
            for(int& pi : pos[i]) {
                int index = upper_bound(all(pos[j]), pi) - pos[j].begin();
                cost[i][j] += max(0LL, (int)pos[j].size() - index);
            }
        }
    }

    int total_state = mask(N - 1) - 1;
    memset(dp, posinf, sizeof(dp));
    dp[0] = 0;

    FOR(state, 1, total_state) {
        for(int hihi = state; hihi >= 1; hihi ^= hihi & -hihi) {
            int i = __builtin_ctz(hihi) + 1;
            int old_state = state ^ (mask(i - 1));
            int s = sum[i];
            int p = 0;
            for(int haha = old_state; haha >= 1; haha ^= haha & -haha) {
                int j = __builtin_ctz(haha) + 1;
                s += cost[i][j];
                p += cnt[j];
            }

            int final_cost = s - cnt[i] * p - getSum(cnt[i]);
            minimize(dp[state], dp[old_state] + final_cost);
        }
    }

    printf("%lld\n", dp[total_state]);
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

    int T; cin >> T;
    while(T--) solve();
}