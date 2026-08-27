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
const int NMOD = 1;
const int BASE = 256;
const int MAX = 100;

int HS1[NMOD][MAX + 1];
int HS2[NMOD][MAX + 1];
int POW[NMOD][MAX + 1];

int n, m;

inline void buildHash(const string& s, const string& t) {
    FOR(j, 0, NMOD - 1) {
        POW[j][0] = 1;
        FOR(i, 1, n) POW[j][i] = (1LL * POW[j][i - 1] * BASE) % MODS[j];
    }

    FOR(j, 0, NMOD - 1) {
        HS1[j][0] = 0;
        FOR(i, 1, n) HS1[j][i] = (1LL * HS1[j][i - 1] * BASE + s[i - 1]) % MODS[j];

        HS2[j][0] = 0;
        FOR(i, 1, m) HS2[j][i] = (1LL * HS2[j][i - 1] * BASE + t[i - 1]) % MODS[j];
    }
}

inline int getHash(const int (&hs)[NMOD][MAX + 1], int j, int l, int r) {
    int res = (hs[j][r] - 1LL * hs[j][l - 1] * POW[j][r - l + 1]) % MODS[j];
    return res < 0 ? res + MODS[j] : res;
}

inline bool compareHash(int l, int r) {
    FOR(j, 0, NMOD - 1) {
        if (getHash(HS1, j, l, r) != getHash(HS2, j, 1, m)) {
            return false;
        }
    }
    return true;
}

inline void solve() {
    string s, t;
    cin >> s >> t;
    n = (int)s.size();
    m = (int)t.size();

    buildHash(s, t);
    for(int i = 1; i <= n - m + 1; i++) {
        if (compareHash(i, i + m - 1)) {
            printf("found at %d\n", i - 1);
        }
    }
}

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