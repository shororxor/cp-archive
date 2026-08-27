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
const int MAX = 2e6;
const int MAXWORDS = 1e5;

int HS[NMOD][MAX];
int POW[NMOD][MAX];
int sta[MAXWORDS + 1];
int fin[MAXWORDS + 1];
int marked[MAXWORDS + 1];

int numWords = 1;
string words[MAXWORDS + 1];

inline void buildHash(string& s, int start, int len) {
    FOR(j, 0, NMOD - 1) {
        HS[j][start] = 0;
        FOR(i, 1, len) HS[j][start + i] = (1LL * HS[j][start + i - 1] * BASE + s[i - 1]) % MODS[j];
    }
}

inline int getHash(int j, int l, int r) {
    int res = (HS[j][r] - 1LL * HS[j][l - 1] * POW[j][r - l + 1]) % MODS[j];
    return res < 0 ? res + MODS[j] : res;
}

inline bool compareHash(int i, int k) {
    int t = fin[i] - (sta[i] + k) + 1;
    if (t > fin[i + 1] - sta[i + 1]) return false;
    FOR(j, 0, NMOD - 1) {
        if (getHash(j, sta[i] + k, fin[i]) != getHash(j, sta[i + 1] + 1, sta[i + 1] + t)) {
            return false;
        }
    }
    return true;
}

inline void checkHash() {
    FOR(i, 1, numWords - 1) {
        int len = fin[i] - sta[i];
        bool skip = false;
        FOR(k, 1, len) if (compareHash(i, k) && !skip) {
            marked[i + 1] = fin[i] - (sta[i] + k) + 1;
            skip = true;
        }
    }
}

inline void output() {
    FOR(i, 1, numWords) {
        int len = fin[i] - sta[i];
        FOR(j, marked[i], len - 1) {
            cout << words[i][j];
        }
    }
}

inline void solve() {
    FOR(j, 0, NMOD - 1) {
        POW[j][0] = 1;
        FOR(i, 1, MAX - 1) POW[j][i] = (1LL * POW[j][i - 1] * BASE) % MODS[j]; 
    }

    sta[0] = -1;
    fin[0] = -1;

    cin >> numWords;
    FOR(i, 1, numWords) {
        cin >> words[i];
        int len = (int)words[i].size();
        sta[i] = fin[i - 1] + 1;
        fin[i] = sta[i] + len;
        buildHash(words[i], sta[i], len);
    }

    checkHash();
    output();
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