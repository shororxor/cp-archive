#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

#define ll long long
#define int ll
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
#define REP(i,l,r) for(int i=(l);i<(r);i++)
#define FORD(i,l,r) for(int i=(l);i>=(r);i--)
#define REPD(i,l,r) for(int i=(l);i>(r);i--)
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

const int MAXN = 2e5;
const int BLOCKSIZE = 800;
int a[MAXN + 1];
int lazy[MAXN / BLOCKSIZE + 1][101];
int NUMBLOCKS;

inline void propagate(int id) {
    int L = id * BLOCKSIZE;
    int R = (id + 1) * BLOCKSIZE - 1;

    FOR(i, L, R) a[i] = lazy[id][a[i]];
    FOR(i, 1, 100) lazy[id][i] = i;
}

inline void manualUpdate(int L, int R, int x, int y) {
    int blockID = L / BLOCKSIZE;
    propagate(blockID);
    FOR(i, L, R) if (a[i] == x) a[i] = y;
}

inline void updateBlock(int id, int x, int y) {
    FOR(i, 1, 100) if (lazy[id][i] == x) lazy[id][i] = y;
}

inline void update(int L, int R, int x, int y) {
    int blockL = L / BLOCKSIZE;
    int blockR = R / BLOCKSIZE;

    if (blockL == blockR) {
        manualUpdate(L, R, x, y);
        return;
    }

    FOR(id, blockL + 1, blockR - 1) updateBlock(id, x, y);
    manualUpdate(L, (blockL + 1) * BLOCKSIZE - 1, x, y);
    manualUpdate(blockR * BLOCKSIZE, R, x, y);
}

inline void process(int n) {
    NUMBLOCKS = (n + BLOCKSIZE - 1) / BLOCKSIZE;
    FOR(id, 0, NUMBLOCKS - 1) FOR(j, 1, 100) lazy[id][j] = j;
}

inline void solve() {
    int n; cin >> n;
    FOR(i, 0, n - 1) cin >> a[i];
    process(n);

    int q; cin >> q;
    int L, R, x, y;
    while(q--) {
        cin >> L >> R >> x >> y;
        L--; R--;
        update(L, R, x, y);
    }

    FOR(id, 0, NUMBLOCKS - 1) propagate(id);
    FOR(i, 0, n - 1) cout << a[i] << ' ';
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