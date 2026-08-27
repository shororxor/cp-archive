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

const string FIRST_ = "RUBEN";
const string SECOND_ = "ALBERT";
const int MAXDIM = 30;

bool seen[1000];
int g[MAXDIM + 1][MAXDIM + 1][MAXDIM + 1];
string FIRST, SECOND;

int getGrundyValue(int x, int y, int z) {
    fill(seen, seen + 1000, 0);
    vector<int> Q;
    FOR(i, 1, x) FOR(j, 1, y) FOR(k, 1, z) {
        int nim = 0;
        if (i - 1 >= 1 && j - 1 >= 1 && k - 1 >= 1) nim ^= g[i - 1][j - 1][k - 1];
        if (i - 1 >= 1 && j - 1 >= 1 && z - k >= 1) nim ^= g[i - 1][j - 1][z - k];
        if (i - 1 >= 1 && y - j >= 1 && k - 1 >= 1) nim ^= g[i - 1][y - j][k - 1];
        if (i - 1 >= 1 && y - j >= 1 && z - k >= 1) nim ^= g[i - 1][y - j][z - k];
        if (x - i >= 1 && j - 1 >= 1 && k - 1 >= 1) nim ^= g[x - i][j - 1][k - 1];
        if (x - i >= 1 && j - 1 >= 1 && z - k >= 1) nim ^= g[x - i][j - 1][z - k];
        if (x - i >= 1 && y - j >= 1 && k - 1 >= 1) nim ^= g[x - i][y - j][k - 1];
        if (x - i >= 1 && y - j >= 1 && z - k >= 1) nim ^= g[x - i][y - j][z - k];       
        seen[nim] = 1;
    }

    int res = 0;
    while (seen[res]) ++res;
    return g[x][y][z] = res;
}

void compute() {
    g[0][0][0] = 0;
    FOR(i, 1, MAXDIM) FOR(j, 1, MAXDIM) g[1][i][j] = g[i][1][j] = g[i][j][1] = 300;
    FOR(x, 1, MAXDIM) FOR(y, 1, MAXDIM) FOR(z, 1, MAXDIM) g[x][y][z] = getGrundyValue(x, y, z);
}

void solve() {
    string name; cin >> name;
    if (name == FIRST_) FIRST = FIRST_, SECOND = SECOND_;
    else FIRST = SECOND_, SECOND = FIRST_;

    compute();
    int n, x, y, z, nim = 0; cin >> n;
    FOR(i, 1, n) {
        cin >> x >> y >> z;
        nim ^= g[x][y][z];
    }
    cout << (nim > 0 ? FIRST : SECOND);
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
    return 0;
}