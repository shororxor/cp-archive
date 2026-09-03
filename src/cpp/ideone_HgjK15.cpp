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
#define REP(i, r) for(int i=0;i<(r);i++)
#define BITSET(size, x) std::bitset<size + 1>(x).to_string().c_str()
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int,int>
#define complex complex<long double>
#define ite std::vector<int>::iterator

template <class T> bool minimize(T& x,T y) {
    if (x > y) x = y; else return 0; return 1;
}
 
template <class T> bool maximize(T& x,T y) {
    if (x < y) x = y; else return 0; return 1;
}

int dx[4] = {-2, -2, 1, -1};
int dy[4] = {1, -1, -2, -2};

const int MAXDIM = 15;
int g[MAXDIM + 1][MAXDIM + 1];

int getGrundyVal(int i, int j) {
    if (g[i][j] != -1) return g[i][j];

    vector<int> seen(300, false);
    for (int k = 0; k < 4; ++k) {
        int x = i + dx[k];
        int y = j + dy[k];
        if (1 <= x && x <= 15 && 1 <= y && y <= 15)
            seen[getGrundyVal(x, y)] = true;
    }

    int res = 0;
    while(seen[res]) ++res;
    return g[i][j] = res;
}

void compute() {
    memset(g, -1, sizeof(g));
    FOR(x, 1, 15) FOR(y, 1, 15) g[x][y] = getGrundyVal(x, y);
}

void solve() {
    int k; cin >> k;
    int nim = 0;
    FOR(i, 1, k) {
        int x, y; cin >> x >> y;
        nim ^= g[x][y];
    }
    cout << (nim > 0 ? "First" : "Second") << '\n';
}

signed main() {
    #ifndef ONLINE_JUDGE
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    compute();
    int T; cin >> T; while(T--) solve();
    return 0;
}