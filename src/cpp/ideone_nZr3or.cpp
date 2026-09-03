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

const int MaxN = 40;
int a[MaxN + 1];

vector<int> getSubsetSum(int L, int R) {
    int len = R - L + 1;
    vector<int> res;

    FOR(mask, 0, (1 << len) - 1) {
        int sum = 0;
        FOR(i, 0, len - 1) if(bit(mask, i)) sum += a[L + i];
        res.push_back(sum);
    }
    sort(all(res));
    return res;
}


inline void solve() {
    int n, x; cin >> n >> x;
    FOR(i, 1, n) cin >> a[i];
    
    vector<int> L = getSubsetSum(1, n/2);
    vector<int> R = getSubsetSum(n/2 + 1, n);

    int ans = 0;
    for(int& i : L) {
        int low = lower_bound(all(R), x - i) - R.begin();
        int high = upper_bound(all(R), x - i) - R.begin();
        ans += high - low;
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