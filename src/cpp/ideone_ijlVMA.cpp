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
#define BITSET(size, x) std::bitset<size + 1>(x).to_string().c_str()
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

const int MODS[] = {(int)1e9 + 2277, (int)1e9 + 5277, (int)1e9 + 8277, (int)1e9 + 9277};
const int NMOD = 2;
const int BASE = 256;
const int MAX = 1e5;

int HS[NMOD][MAX + 1];
int POW[NMOD][MAX + 1];

inline void calHash(string& s, int len) {
    FOR(j, 0, NMOD - 1) FOR(i, 1, len)
        HS[j][i] = (1LL * HS[j][i - 1] * BASE + s[i - 1]) % MODS[j];
}

inline int getHash(int j, int l, int r) {
    int res = (HS[j][r] - 1LL * HS[j][l - 1] * POW[j][r - l + 1]) % MODS[j];
    return res < 0 ? res + MODS[j] : res;
}

inline void prepare() {
    FOR(j, 0, NMOD - 1) {
        POW[j][0] = 1;
        FOR(i, 1, MAX) POW[j][i] = (1LL * POW[j][i - 1] * BASE) % MODS[j];
    }
}

inline void solve() {
    FOR(j, 0, NMOD - 1) fill(HS[j], HS[j] + MAX + 1, 0);
    int n, k; cin >> n >> k;
    string s; cin >> s;
    calHash(s, (int)s.size());

    s = '0' + s;
    int ans =  0;
    map<int,int> used;
    FOR(i, 1, n - k + 1) {
        bool update = 0;
        FOR(j, 0, NMOD - 1) {
            int hash = getHash(j, i, i + k - 1);
            if (!used[hash] && !update) {
                ans++;
                update = 1;
            }
            used[hash] = 1;
        }
    }
    cout << ans << '\n';
}

signed main() {
    #ifndef ONLINE_JUDGE
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    prepare();
    int T; cin >> T;
    while(T--) solve();
}