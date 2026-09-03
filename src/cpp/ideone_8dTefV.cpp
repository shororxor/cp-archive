#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

#define ll long long
// #define int ll
#define mask(i) (1 << (i))
#define bit(x, i)  (((x) >> (i)) & 1)
#define onbit(x, i) ((x) = (x) | mask(i))
#define offbit(x, i) ((x) = (x) & (~mask(i)))
#define pcount(i) __builtin_popcount(i)
#define bctz(i) __builtin_ctz(i)
#define all(v) v.begin(), v.end()
#define all1(v) v.begin()+1, v.end()
#define sz(v) (int)v.size(); 
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

const int MaxN = 100;
int a[MaxN + 1], pre[MaxN + 1];
int L[MaxN + 1], R[MaxN + 1];

void solve() {
    int n, x; cin >> n >> x;
    FOR(i, 1, n) {
        cin >> a[i];
        a[i] = a[i] - x; // convert to array b
        pre[i] = pre[i - 1] + a[i];
    }

    // prefix min
    L[1] = pre[1];
    FOR(i, 2, n) L[i] = min(L[i - 1], pre[i]);

    // suffix max
    R[n] = pre[n];
    FORD(i, n - 1, 1) R[i] = max(pre[i], R[i + 1]);

    // two pointer
    int ans = -1;
    int i = 1, j = 1;
    while(i <= n && j <= n) {
        if (L[i] < R[j]) {
            maximize(ans, j - i + 1);
            j++;
        }
        else i++;
    }
    cout << ans << '\n';
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