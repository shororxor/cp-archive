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

const int MaxN = 12;
int dp[MaxN + 1][MaxN * MaxN + 1][1 << MaxN | 1];
vector<pair<int,int>> valid_states;
unordered_map<int, vector<int>> compatible_states;

void precompute() {
    FOR(state, 0, (1 << 12) - 1) {
        if ((state & (state << 1)) == 0) {
            int cnt = 0;
            for(int hihi = state; hihi >= 1; hihi ^= hihi & -hihi) cnt++;
            valid_states.push_back({state, cnt});
        }
    }

    for(auto& [s1, cnt1] : valid_states) {
        for(auto& [s2, cnt2] : valid_states) {
            bool valid = true;
            FOR(i, 0, 11) {
                int right = max(i - 1, 0LL);
                int left = min(i + 1, 11LL);
                if (bit(s1, i) & (bit(s2, left) || bit(s2, right) || bit(s2, i))) {
                    valid = false;
                    break;
                }
            }
            if (valid) compatible_states[s1].push_back(s2);
        }
    }
}

void solve() {
    int N, K; cin >> N >> K;
    precompute();

    dp[0][0][0] = 1;

    FOR(i, 1, N) {
        FOR(k, 0, K) {
            for(auto& [state, cnt]: valid_states) {
                if (k < cnt) continue;
                for(int& old_state : compatible_states[state]) {
                    dp[i][k][state] += dp[i - 1][k - cnt][old_state];
                }
            }
        }
    }

    int ans = 0;
    for(auto& [state, cnt] : valid_states) ans += dp[N][K][state];
    printf("%lld\n", ans);
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