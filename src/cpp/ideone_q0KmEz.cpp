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
#define FORD(i,l,r) for(int i=(l);i>=(r);i--)
#define REP(i, r) for(int i=0;i<(r);i++)
#define BITSET(size, x) std::bitset<size + 1>(x).to_string().c_str()
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int,int>
#define complex complex<long double>
#define ite std::vector<int>::iterator
#define div div__

template <class T> bool minimize(T& x,T y) {
    if (x > y) x = y; else return 0; return 1;
}
 
template <class T> bool maximize(T& x,T y) {
    if (x < y) x = y; else return 0; return 1;
}

const int MAX = 500;
int A[MAX + 1][MAX + 1];
int sum[MAX + 1][MAX + 1];
int g[MAX + 1][MAX + 1];

int getSumRow(int x, int y) {
    return sum[x][y] - sum[x - 1][y];
}

int getSumCol(int x, int y) {
    return sum[x][y] - sum[x][y - 1];
}

int getMex(vector<int>& Q) {
    int res = 0;
    sort(Q.begin(), Q.end());
    for(int& q : Q) if (q == res) ++res;
    return res;
}

void solve() {
    int n; cin >> n;
    FOR(i, 1, n) FOR(j, 1, n) cin >> A[i][j];
    FOR(i, 1, n) FOR(j, 1, n) sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + A[i][j];

    g[0][0] = 0;
    FOR(x, 1, n) FOR(y, 1, n) {
        vector<int> Q;
        if (getSumRow(x, y) % 2 == 0) Q.push_back(g[x - 1][y]);
        if (getSumCol(x, y) % 2 == 0) Q.push_back(g[x][y - 1]);
        g[x][y] = getMex(Q);
    }

    cout << (g[n][n] > 0 ? "YES" : "NO") << '\n';
    memset(sum, 0, sizeof(sum));
    memset(g, 0, sizeof(g));
}

signed main() {
    #ifndef ONLINE_JUDGE
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T; cin >> T; while(T--) solve();
    return 0;
}
