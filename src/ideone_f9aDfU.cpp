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
#define div div__

template <class T> bool minimize(T& x,T y) {
    if (x > y) x = y; else return 0; return 1;
}
 
template <class T> bool maximize(T& x,T y) {
    if (x < y) x = y; else return 0; return 1;
}

const int MAX = 1e6;

int g[MAX + 1];
vector<int> div[MAX + 1];

void sieve() {
    for(int a = 1; a * a <= MAX; a++) {
        for(int b = a; a * b <= MAX; b++) {
            if (a > 1) div[a * b].push_back(a);
            if (a != b) div[a * b].push_back(b);
        }
    }
}

int getGrundyValue(int x) {
    vector<bool> seen(100, false);
    for (int y : div[x]) {
        if (y & 1) seen[g[x / y]] = true;
        else seen[0] = true;
    }
    int res = 0;
    while(seen[res]) ++res;
    return g[x] = res;
}

void compute() {
    fill(g, g + MAX + 1, 0);
    FOR(i, 2, MAX) g[i] = getGrundyValue(i);
}

void solve() {
    int n; cin >> n;
    int nim = 0;
    FOR(i, 1, n) {
        int h; cin >> h;
        nim ^= g[h];
    }

    cout << (nim > 0 ? 1 : 2) << '\n';
}

signed main() {
    #ifndef ONLINE_JUDGE
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    sieve(); compute();
    int T; cin >> T; while(T--) solve();
    return 0;
}