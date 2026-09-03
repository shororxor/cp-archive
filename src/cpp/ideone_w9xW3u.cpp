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
const int NEGINF = -1e9;
const int MOD = 1000000007;
const double PI = 3.14159265359;

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

const int MAX = 100;
int tree[2 * MAX];

int n;

inline void update(int p, int val) {
    for(tree[p += n] = val; p > 1; p >>= 1) {
        tree[p >> 1] = tree[p] + tree[p ^ 1];
    }
}

inline int query(int l, int r) {
    int res = 0;
    for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
    if (l == r) { res += tree[l]; break; }
    if (l & 1) res += tree[l++];
    if (!(r & 1)) res += tree[r--];
  }
  return res;
}

inline void solve() {
    scanf("%d", &n);
    FOR(i, 0, n - 1) scanf("%d", tree + n + i);
    FORD(i, n - 1, 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
    cout << query(3, 10);
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