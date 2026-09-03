#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

#define ll long long
#define mask(i) (1 << (i))
#define bit(x, i)  (((x) >> (i)) & 1)
#define onbit(x, i) ((x) = (x) | mask(i))
#define offbit(x, i) ((x) = (x) & (~mask(i)))
#define pcount(i) __builtin_popcount(i)
#define bctz(i) __builtin_ctz(i)
#define all(v) v.begin(), v.end()
#define all1(v) v.begin()+1, v.end()
#define sz(v) (int)v.size()
#define sqr(x) ((x) * (x))
#define FOR(i,l,r) for(int i=(l);i<=(r);i++)
#define FORD(i,l,r) for(int i=(l);i>=(r);i--)
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
const int MAX = 10000;
const int MODS[] = {(int)1e9 + 2277, (int)1e9 + 5277, (int)1e9 + 8277, (int)1e9 + 9277};
const int BASE = 256;
const int MAXK = 13;
const int NMOD = 1;

int POW[NMOD][MAX + 1];
int LEN[MAXK + 1];
int H[NMOD][MAX + 1];
int RH[NMOD][MAX + 1];
bool dp[MAX + 1][1 << MAXK];

inline int getHash(int j, int L, int R) {
    int res = (H[j][R] - 1LL * H[j][L - 1] * POW[j][R - L + 1]) % MODS[j];
    return res < 0 ? res + MODS[j] : res;
}

inline int getRevHash(int j, int L, int R) {
    int res = (RH[j][R] - 1LL * RH[j][L - 1] * POW[j][R - L + 1]) % MODS[j];
    return res < 0 ? res + MODS[j] : res;
}

inline bool isPalin(int u, int v, int n) {
    FOR(j, 0, NMOD - 1) {
        if (getHash(j,u,v) != getRevHash(j,n-v+1,n-u+1)) return false;
    }
    return true;
}

inline bool compute(int n, int k) {
    int total = (1 << k) - 1;
    memset(dp, 0, sizeof(dp));
    dp[1][0] = 1;
    FOR(i, 1, n) {
        FOR(mask, 0, total) {
            if (!dp[i][mask]) continue;
            dp[i + 1][mask] = (dp[i + 1][mask] || dp[i][mask]);
            for(int hihi = total ^ mask; hihi >= 1; hihi ^= hihi & -hihi) {
                int j = __builtin_ctz(hihi) + 1;
                if (i + LEN[j] - 1 > n + 1) continue;
                if (isPalin(i, i + LEN[j] - 1, n)) {
                    dp[i + LEN[j]][mask | (1 << (j - 1))] = dp[i][mask];
                }
            }
        }
    }
    return dp[n + 1][total];
}

inline void solve() {
    string s; cin >> s;
    string rs = s; reverse(all(rs));
    int n = (int)s.size();

    // process hash
    FOR(j, 0, NMOD - 1) {
        POW[j][0] = 1; H[j][0] = 0; RH[j][0] = 0;
        FOR(i, 1, MAX) POW[j][i] = (1LL * POW[j][i-1] * BASE) % MODS[j];
        FOR(i, 1, n) H[j][i] = (1LL * H[j][i-1] * BASE + s[i-1]) % MODS[j];
        FOR(i, 1, n) RH[j][i] = (1LL * RH[j][i-1] * BASE + rs[i-1]) % MODS[j];
    }

    // dp bitmask
    int T; cin >> T;
    while(T--) {
        int k; cin >> k;
        FOR(i, 1, k) cin >> LEN[i];
        if (compute(n, k)) cout << "YES\n";
        else cout << "NO\n";
    }
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

    solve();
}