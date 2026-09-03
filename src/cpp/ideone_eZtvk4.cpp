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

struct Rec {
    int x, y, a;
    bool operator<(const Rec& other) const {
        return this->x < other.x;
    }
};

const int MaxN = 1e6;
int dp[MaxN + 1];
Rec a[MaxN + 1];

inline double intersect(int i, int j) {
    return (double)(dp[j] - dp[i]) / (a[j].x - a[i].x);
}

struct CHT {
    deque<int> dq;

    CHT() { dq.push_front(0); }

    inline bool valid (int i, int j, int k) {
        return intersect(k, j) < intersect(j, i);
    }

    inline void update(int i) {
        while (sz(dq) >= 2 && !valid(dq[0], dq[1], i)) {
            dq.pop_front();
        }
        dq.push_front(i);
    }

    inline int query(int x) {
        int L = 0, R = sz(dq) - 1;
        int ans = R;
        while(L <= R) {
            int M = (L + R) >> 1;
            if (intersect(dq[M], dq[M + 1]) <= x) {
                ans = M;
                L = M + 1;
            }
            else R = M - 1;
        }
        return ans;
    }
};

inline void solve() {
    int n; cin >> n;
    FOR(i, 1, n) cin >> a[i].x >> a[i].y >> a[i].a;
    sort(a + 1, a + n + 1);

    CHT cht;
    FOR(i, 1, n) {
        int j = cht.query(a[i].y);
        dp[i] = max(dp[i - 1], a[i].x * a[i].y - a[i].a + (-a[j].x * a[i].y + dp[j]));
        cht.update(i);
    }

    cout << dp[n] << '\n';
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