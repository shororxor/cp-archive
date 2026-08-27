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

int g[101][101];

int getMex(vector<int>& Q) {
    int res = 0;
    sort(Q.begin(), Q.end());
    for(int& q : Q) if (res == q) ++res;
    return res;
}

int getGrundyValue(int l, int c) {
    vector<int> Q;
    FOR(u, 1, 100) {
        if (l - u >= 0) Q.push_back(g[l - u][c]);
        if (c - u >= 0) Q.push_back(g[l][c - u]);
        if (l - u >= 0 && c - u >= 0) Q.push_back(g[l - u][c - u]);
    }
    return g[l][c] = getMex(Q);
}

void compute() {
    FOR(i, 1, 100) g[i][0] = 999, g[0][i] = 999, g[i][i] = 999;
    FOR(l, 1, 100) FOR(c, 1, 100) if (l != c) g[l][c] = getGrundyValue(l, c);
    // dp bottom-up --> ensure all previous states are alr computed
}

void solve() {
    int n; cin >> n;
    compute();

    int nim = 0;
    FOR(i, 1, n) {
        int l, c; cin >> l >> c;
        nim ^= g[l][c];
    }
    cout << (nim > 0 ? "Y" : "N");
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