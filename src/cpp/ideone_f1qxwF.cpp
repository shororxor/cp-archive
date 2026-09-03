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

const int MAX = 500;
int a[MAX + 1];
int sum[MAX + 1];

int n, q, C;

void add(int &a, int b) {
    a += b;
    while(a >= MOD) a -= MOD;
}

void sub(int &a, int b) {
    a -= b;
    while(a < 0) a += MOD; 
}

void calSum() {
    sum[0] = 0;
    FOR(i, 1, n) {
        sum[i] = sum[i - 1];
        add(sum[i], a[i]);
    }
}

int pw(int a, int k) {
    int res = 1;
    while (k > 0) {
        if (k & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        k >>= 1;
    }
    return res;
} 

int compute(int l, int r, int k) {
    int ans = 0;
    FOR(u, l, r) FOR(v, u, r) {
        int s = sum[v];
        sub(s, sum[u - 1]);
        add(s, C);
        add(ans, pw(s, k));
    }
    return ans;
}

inline void solve() {
    scanf("%d%d%d", &n, &q, &C);
    FOR(i, 1, n) scanf("%d", &a[i]);
    calSum();

    FOR(i, 1, q) {
        int t, l, r; scanf("%d%d%d", &t, &l, &r);
        if (t == 1 || t == 2) {
            int c; scanf("%d", &c);
            FOR(i, l, r) {
                if (t == 1) a[i] = 1LL * a[i] * c % MOD;
                else add(a[i], c);
            }
            calSum();
        }
        else {
            FOR(k, 0, 4) printf("%d ", compute(l, r, k));
            printf("\n");
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